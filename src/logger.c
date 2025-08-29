#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "battery.h"
#include "balance.h"
#include "alert.h"
#include "led.h"
#include "config.h"

extern pthread_mutex_t mutex;

void* logger_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        printf("=== Battery Status ===\n");
        for (int i = 0; i < NUM_CELLS; i++) {
            printf("Cell %d: V=%.3f, T=%.1f | Overheat=%d | LED=%s\n",
                   i+1,
                   batteries[i].voltage,
                   batteries[i].temperature,
                   overheat_flags[i],
                   led_states[i] ? "ON" : "OFF");
        }
        printf("----------------------\n");

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}
