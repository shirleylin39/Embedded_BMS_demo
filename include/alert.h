#ifndef ALERT_H
#define ALERT_H
#include "config.h"

extern int overheat_flags[NUM_CELLS];
extern pthread_mutex_t mutex;

void* alert_thread(void* arg);

#endif
