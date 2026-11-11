#ifndef __UTIL_H
#define __UTIL_H

#include <IPAddress.h>

void printBaseMAC();
void printWiFiMAC();

// Send one ICMP ping, block until reply or timeout. Returns true if the host replied.
bool pingHost(const IPAddress& adr, uint32_t timeout_ms = 1000);

#endif // __UTIL_H