#ifndef BALANCE_H
#define BALANCE_H


extern int balancing_cell;
extern pthread_mutex_t mutex;

void* balance_thread(void* arg);

#endif
