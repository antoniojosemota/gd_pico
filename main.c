#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"

#define WIFI_SSID "LabirasNote"
#define WIFI_PASSWORD "marcelino"
#define DEST_IP "192.168.137.120" // IP da máquina que roda o Godot
#define DEST_PORT 5000

void send_udp_packet(struct udp_pcb *pcb, ip_addr_t *addr, u16_t port, const char *message) {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, strlen(message), PBUF_RAM);
    if (!p) return;

    memcpy(p->payload, message, strlen(message));
    udp_sendto(pcb, p, addr, port);
    pbuf_free(p);
}

int main() {
    stdio_init_all();
    sleep_ms(5000); // Espera o USB conectar
    if (cyw43_arch_init()) {
        printf("WiFi init failed\n");
        return -1;
    }
    cyw43_arch_enable_sta_mode();

    printf("Conectando ao WiFi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Falha na conexão WiFi\n");
        return -1;
    }
    printf("Conectado!\n");

    struct udp_pcb *pcb = udp_new();
    if (!pcb) {
        printf("Erro criando PCB UDP\n");
        return -1;
    }

    ip_addr_t dest_addr;
    ipaddr_aton(DEST_IP, &dest_addr);

    int count = 0;
    while (true) {
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "packet %d", count++);
        send_udp_packet(pcb, &dest_addr, DEST_PORT, buffer);
        printf("Sent %s\n", buffer);
        sleep_ms(1000);
    }

    return 0;
}
