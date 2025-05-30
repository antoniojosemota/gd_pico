#include <string.h>
#include <stdio.h>
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "wifi_udp.h"

#define WIFI_SSID "OP"
#define WIFI_PASSWORD "onepiece"

int wifi_init(void) {
    if (cyw43_arch_init()) return -1;
    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000))
        return -1;

    return 0;
}

struct udp_pcb *udp_setup(ip_addr_t *dest) {
    struct udp_pcb *pcb = udp_new();
    if (!pcb) return NULL;

    ipaddr_aton("192.168.137.95", dest);
    return pcb;
}

void send_udp_packet(struct udp_pcb *pcb, ip_addr_t *addr, u16_t port, const char *message) {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, strlen(message), PBUF_RAM);
    if (!p) return;

    memcpy(p->payload, message, strlen(message));
    udp_sendto(pcb, p, addr, port);
    pbuf_free(p);
}
