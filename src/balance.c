#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "battery.h"
#include "balance.h"
#include "config.h"

extern Battery* batteries;
extern int balancing_cell;
extern pthread_mutex_t mutex;

void* balance_thread(void* arg) {
    while(1) {
        double max_v = 0, min_v = 5.0;
        int max_idx = 0;

        pthread_mutex_lock(&mutex);

        for(int i = 0; i < NUM_CELLS; i++){
            if (batteries[i].voltage > max_v) {
                max_v = batteries[i].voltage;
                max_idx = i;
            }
            if (batteries[i].voltage < min_v){
                min_v = batteries[i].voltage;
            }
        }

        if (max_v - min_v > BALANCE_THRESHOLD) {
            balancing_cell = max_idx;
        } else {
            balancing_cell = -1;
        }

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}
