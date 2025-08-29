#ifndef BATTERY_H
#define BATTERY_H

typedef struct {
    double voltage;
    double temperature;
} Battery;


extern Battery* batteries;        
extern pthread_mutex_t mutex;  

//Simulation 1: rand()
//Simulation 0: Hardware Abstraction Layer API
#define SIMULATION 1

void* battery_thread(void* arg);

double adc_read_voltage(int channel);
double i2c_read_temperature(int sensor_id);

#endif

