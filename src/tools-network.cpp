#include "tools-network.h"

#include <tools-log.h>

#include "esp_system.h"
#include "esp_mac.h"
#include "ping/ping_sock.h"

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

// ESP-IDF ping runs in its own task and reports through callbacks
static SemaphoreHandle_t ping_done = NULL;
static volatile bool ping_replied = false;

static void ping_on_success(esp_ping_handle_t, void*)
{
	ping_replied = true;
};

static void ping_on_end(esp_ping_handle_t, void*)
{
	xSemaphoreGive(ping_done);
};

bool pingHost(const IPAddress& adr, uint32_t timeout_ms)
{
	if(ping_done == NULL)
	{
		ping_done = xSemaphoreCreateBinary();
		if(ping_done == NULL)
			return false;
	};
	xSemaphoreTake(ping_done, 0);	// drop a stale signal from an earlier aborted ping
	ping_replied = false;

	esp_ping_config_t ping_config = ESP_PING_DEFAULT_CONFIG();
	IP_ADDR4(&ping_config.target_addr, adr[0], adr[1], adr[2], adr[3]);
	ping_config.count = 1;
	ping_config.timeout_ms = timeout_ms;

	esp_ping_callbacks_t cbs = {};
	cbs.on_ping_success = ping_on_success;
	cbs.on_ping_end = ping_on_end;

	esp_ping_handle_t ping;
	if(esp_ping_new_session(&ping_config, &cbs, &ping) != ESP_OK)
		return false;
	esp_ping_start(ping);

	// on_ping_end fires after the reply or the timeout; the extra second is only a safety net
	if(xSemaphoreTake(ping_done, pdMS_TO_TICKS(timeout_ms + 1000)) != pdTRUE)
	{
		esp_ping_stop(ping);
	};
	esp_ping_delete_session(ping);

	return ping_replied;
};
