#ifndef LED_H
#define LED_H
#include "config.h"

extern int led_states[NUM_CELLS]; // 0=OFF, 1=ON

void led_on(int cell_id);
void led_off(int cell_id);

#endif
