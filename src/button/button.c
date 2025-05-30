#include "pico/stdlib.h"
#include "button.h"

#define BTN_A_PIN 5
#define BTN_B_PIN 6

void buttons_init(void) {
    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);

    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_B_PIN);
}

void read_buttons(int *a, int *b) {
    *a = gpio_get(BTN_A_PIN) ? 1 : 0;
    *b = gpio_get(BTN_B_PIN) ? 1 : 0;
    sleep_ms(10); // debounce simples
}
