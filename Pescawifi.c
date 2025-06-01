#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "button.h"
#include "wifi_udp.h"
#include "mpu6050.h"

#define DEST_PORT 5000
int16_t ax, ay, az;

int main() {
    stdio_init_all();
    sleep_ms(5000);

    buttons_init();
    joystick_init();
    mpu6050_init();

    if (wifi_init() < 0) {
        printf("Falha na inicialização do Wi-Fi\n");
        return -1;
    }

    printf("Wi-Fi conectado!\n");

    ip_addr_t dest_addr;
    struct udp_pcb *pcb = udp_setup(&dest_addr);
    if (!pcb) {
        printf("Erro criando PCB UDP\n");
        return -1;
    }

    char dirX[32], dirY[32], buffer[128];
    int valueA, valueB;

    while (true) {
        mpu6050_read_raw(&ax, &ay, &az);
        get_joystick_direction(dirX, dirY);
        read_buttons(&valueA, &valueB);
        float inclination = mpu6050_get_inclination(ax, ay, az);
        snprintf(buffer, sizeof(buffer), "ButtonA = %d, ButtonB = %d, Analog_Y = %s, Analog_X = %s, Climb = %.2f", valueA, valueB, dirX, dirY, inclination);
        send_udp_packet(pcb, &dest_addr, DEST_PORT, buffer);
        printf("Sent %s\n", buffer);
        sleep_ms(10);
    }
    return 0;
}
