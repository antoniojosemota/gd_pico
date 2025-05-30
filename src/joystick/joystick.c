#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/adc.h"
#include "joystick.h"

#define EX 26
#define EY 27

void joystick_init(void) {
    adc_init();
    gpio_init(EX);
    gpio_init(EY);
}

void get_joystick_direction(char *dirX, char *dirY) {
    adc_select_input(0);
    uint x = adc_read();
    adc_select_input(1);
    uint y = adc_read();

    if (x > 3000) snprintf(dirX, 32, "Cima");
    else if (x < 1500) snprintf(dirX, 32, "Baixo");
    else snprintf(dirX, 32, "Centro");

    if (y > 3000) snprintf(dirY, 32, "Direita");
    else if (y < 1500) snprintf(dirY, 32, "Esquerda");
    else snprintf(dirY, 32, "Centro");
}
