#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "battery.h"
#include "alert.h"
#include "led.h"
#include "config.h"

extern Battery* batteries;
extern int overheat_flags[NUM_CELLS];
extern pthread_mutex_t mutex;


void* alert_thread(void* arg) {
    while(1){
        int led_on = 0;

        pthread_mutex_lock(&mutex);
        for (int i = 0; i < NUM_CELLS; i++) {
            if (batteries[i].temperature > TEMP_THRESHOLD) {
                overheat_flags[i] = 1;

                printf("\033[31mALERT: Cell %d OVERHEAT %.2f°C\033[0m\n", i+1, batteries[i].temperature);
                led_on = 1;
                fflush(stdout);

            }
        }
       
        for(int i = 0; i < NUM_CELLS; i++)
            led_states[i] = led_on;
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}
