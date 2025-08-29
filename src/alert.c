#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "battery.h"
#include "alert.h"
#include "led.h"

extern pthread_mutex_t mutex;

void* alert_thread(void* arg) {
    while(1){
        int led_on=0;

        pthread_mutex_lock(&mutex);
        for(int i=0;i<NUM_CELLS;i++){
            if(batteries[i].temperature>TEMP_THRESHOLD){
                printf("Warning: Cell %d temperature too high! %.1f°C\n", i+1, batteries[i].temperature);
                led_on=1;
            }
        }
        pthread_mutex_unlock(&mutex);

        led_control(led_on);
        usleep(1000000);
    }
}
