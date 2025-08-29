#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>

#include "battery.h"
#include "balance.h"
#include "alert.h"
#include "led.h"
#include "config.h"
#include "logger.h"

pthread_mutex_t mutex;
Battery* batteries;
int overheat_flags[NUM_CELLS] = {0};
int led_states[NUM_CELLS] = {0};
int balancing_cell = -1;

int main() {
    srand(time(NULL));
    batteries = (Battery*) malloc (sizeof(Battery)* NUM_CELLS);
    if(!batteries){ perror("malloc failed"); return 1; }

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_CELLS], balance_t, alert_t, logger_t;
    int idx[NUM_CELLS];

    // Battery Thread
    for(int i = 0;i < NUM_CELLS; i++){
        idx[i] = i;
        pthread_create(&threads[i], NULL, battery_thread, &idx[i]);
    }

    // Balance Thread
    pthread_create(&balance_t, NULL, balance_thread, NULL);
    
    // Alert Thread
    pthread_create(&alert_t, NULL, alert_thread, NULL);

    //Logger Thread
    pthread_create(&logger_t, NULL, logger_thread, NULL);

    struct sched_param param;
    param.sched_priority = 80; 
    pthread_setschedparam(balance_t, SCHED_FIFO, &param);

    param.sched_priority = 60;
    pthread_setschedparam(alert_t, SCHED_FIFO, &param);

    param.sched_priority = 30;
    for(int i = 0; i < NUM_CELLS; i++)
        pthread_setschedparam(threads[i], SCHED_FIFO, &param);

  
    for(int i = 0 ;i < NUM_CELLS; i++) pthread_join(threads[i], NULL);
    pthread_join(balance_t, NULL);
    pthread_join(alert_t, NULL);
    pthread_join(logger_t, NULL);

    pthread_mutex_destroy(&mutex);
    free(batteries);

    return 0;
}
