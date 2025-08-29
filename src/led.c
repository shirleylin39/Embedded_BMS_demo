#include <stdio.h>
#include "led.h"
#include "config.h"
#include "battery.h"
#include "alert.h"
#include "led.h"


void led_on(int cell_id) {
    if(cell_id >=0 && cell_id < NUM_CELLS)
        led_states[cell_id] = 1;
}

void led_off(int cell_id) {
    if(cell_id >=0 && cell_id < NUM_CELLS)
        led_states[cell_id] = 0;
}

