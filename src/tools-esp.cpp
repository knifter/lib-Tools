#include "tools-esp.h"

#include <stdio.h>

const char* esp_reset_reason_str(esp_reset_reason_t reason)
{
	switch(reason)
	{
		case ESP_RST_UNKNOWN:		return "unknown";
		case ESP_RST_POWERON:		return "power-on";
		case ESP_RST_EXT:			return "external pin";
		case ESP_RST_SW:			return "software";
		case ESP_RST_PANIC:			return "panic";
		case ESP_RST_INT_WDT:		return "int watchdog";
		case ESP_RST_TASK_WDT:		return "task watchdog";
		case ESP_RST_WDT:			return "other watchdog";
		case ESP_RST_DEEPSLEEP:		return "deep sleep wake";
		case ESP_RST_BROWNOUT:		return "brownout";
		case ESP_RST_SDIO:			return "SDIO";
		case ESP_RST_USB:			return "USB";
		case ESP_RST_JTAG:			return "JTAG";
		case ESP_RST_EFUSE:			return "efuse error";
		case ESP_RST_PWR_GLITCH:	return "power glitch";
		case ESP_RST_CPU_LOCKUP:	return "CPU lockup";
		default:					return "(unknown)";
	};
};

const char* esp_wakeup_cause_str(esp_sleep_wakeup_cause_t cause)
{
	switch(cause)
	{
		case ESP_SLEEP_WAKEUP_UNDEFINED:		return "none";
		case ESP_SLEEP_WAKEUP_ALL:				return "all";				// "Not a wakeup cause, used to disable all wakeup sources".
		case ESP_SLEEP_WAKEUP_EXT0:				return "ext0";
		case ESP_SLEEP_WAKEUP_EXT1:				return "ext1";
		case ESP_SLEEP_WAKEUP_TIMER:			return "timer";
		case ESP_SLEEP_WAKEUP_TOUCHPAD:			return "touchpad";
		case ESP_SLEEP_WAKEUP_ULP:				return "ULP";
		case ESP_SLEEP_WAKEUP_GPIO:				return "GPIO";
		case ESP_SLEEP_WAKEUP_UART:				return "UART";
		case ESP_SLEEP_WAKEUP_UART1:			return "UART1";
		case ESP_SLEEP_WAKEUP_UART2:			return "UART2";
		case ESP_SLEEP_WAKEUP_WIFI:				return "WiFi";
		case ESP_SLEEP_WAKEUP_COCPU:			return "co-processor";
		case ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG:	return "co-proc crash";
		case ESP_SLEEP_WAKEUP_BT:				return "BT";
		case ESP_SLEEP_WAKEUP_VAD:				return "VAD";
		case ESP_SLEEP_WAKEUP_VBAT_UNDER_VOLT:	return "VBAT low";
		case ESP_SLEEP_WAKEUP_USB:				return "USB";
		default:								return "(unknown)";
	};
};

const char* esp_boot_reason_str()
{
	esp_reset_reason_t reason = esp_reset_reason();
	if(reason != ESP_RST_DEEPSLEEP)
		return esp_reset_reason_str(reason);

	// Only after a deep sleep reset does the wakeup cause mean anything
	static char buf[24];
	snprintf(buf, sizeof(buf), "wake:%s", esp_wakeup_cause_str(esp_sleep_get_wakeup_cause()));
	return buf;
};
