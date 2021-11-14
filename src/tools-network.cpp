#include "tools-network.h"

#include <tools-log.h>

#include "esp_system.h"

/*
The following MAC addresses are derived from the BASE MAC in the EFUSE BLK0.
 #ESP_MAC_WIFI_STA
 #ESP_MAC_WIFI_SOFTAP
 #ESP_MAC_BT
 #ESP_MAC_ETH

For 2 universal MAC addresses, the BT and Wifi are both enabled. Ethernet is disabled. Here:
#ESP_MAC_WIFI_STA=ESP_MAC_WIFI_SOFTAP=BASE MAC.
#ESP_MAC_BT=BASE MAC+1

For 4 Universal MAC addresses, the BT, Wifi and ethernet are all enabled. Here:
#ESP_MAC_WIFI_STA=BASE MAC.
#ESP_MAC_WIFI_SOFTAP=BASE MAC+1
#ESP_MAC_BT=BASE MAC+2
#ESP_MAC_ETH=BASE MAC+3
*/

void printBaseMAC()
{
	uint8_t mac[6];
	esp_efuse_mac_get_default(mac);
	DBG("Device Base MAC: %02x-%02x-%02x-%02x-%02x-%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
};

void printWiFiMAC()
{
	uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);
	DBG("Device WiFi MAC: %02x-%02x-%02x-%02x-%02x-%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	// WiFi.macAddress(mac); // Does not return right mac address before connect
};
