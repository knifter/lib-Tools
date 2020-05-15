#include "tools-network.h"

#include <Arduino.h>
#include <WiFi.h>

void printMAC()
{
	uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);
	// WiFi.macAddress(mac); // Does not return right mac address before connect
	Serial.print(mac[5],HEX);
	Serial.print(":");
	Serial.print(mac[4],HEX);
	Serial.print(":");
	Serial.print(mac[3],HEX);
	Serial.print(":");
	Serial.print(mac[2],HEX);
	Serial.print(":");
	Serial.print(mac[1],HEX);
	Serial.print(":");
	Serial.print(mac[0],HEX);
};
