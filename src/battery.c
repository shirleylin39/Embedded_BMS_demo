#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "battery.h"

extern Battery* batteries;
extern pthread_mutex_t mutex;

//Simulation functions
static double sim_voltage() {
    return 3.5 + ((rand() % 70) / 1000.0);
}

static double sim_temperature() {
    return 25 + ((rand() % 3000) / 100.0);
}

//For hardware API
double adc_read_voltage(int channel) {
    return 3.7 + channel * 0.01;
}

double i2c_read_temperature(int sensor_id) {
    return 30.0 + sensor_id;
}

//Battery monitoring thread
void* battery_thread(void* arg) {
    int idx = *(int*)arg;
    while(1) {
        pthread_mutex_lock(&mutex);

#if SIMULATION
        batteries[idx].voltage = sim_voltage();
        batteries[idx].temperature = sim_temperature();
#else
        batteries[idx].voltage = adc_read_voltage(idx);
        batteries[idx].temperature = i2c_read_temperature(idx);
#endif
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}
