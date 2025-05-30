#ifndef WIFI_UDP_H
#define WIFI_UDP_H

#include "lwip/udp.h"
#include "lwip/ip_addr.h"

int wifi_init(void);
struct udp_pcb *udp_setup(ip_addr_t *dest);
void send_udp_packet(struct udp_pcb *pcb, ip_addr_t *addr, u16_t port, const char *message);

#endif
