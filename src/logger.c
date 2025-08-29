#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "battery.h"
#include "balance.h"
#include "alert.h"
#include "led.h"
#include "config.h"


extern Battery* batteries;
extern int led_states[NUM_CELLS];
extern int overheat_flags[NUM_CELLS];
extern int balancing_cell;
extern pthread_mutex_t mutex;

void* logger_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        printf("=== Battery Status ===\n");
        for (int i = 0; i < NUM_CELLS; i++) {
            printf("Cell %d: V=%.3f, T=%.1f\n",
                   i+1,
                   batteries[i].voltage,
                   batteries[i].temperature);
            }

        if (balancing_cell >= 0)
            printf("\033[33mBalance target: Cell %d\033[0m\n", balancing_cell+1);
        else
            printf("Balance target: None\n");
        

        printf("----------------------\n");

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}
