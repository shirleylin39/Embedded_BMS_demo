#include <stdio.h>
#include "led.h"

void led_control(int on) {
    if (on) printf("LED ON\n");
    else printf("LED OFF\n");
}
