#ifndef __TOOLS_ESP_H
#define __TOOLS_ESP_H

#include <esp_system.h>
#include <esp_sleep.h>

// Short, human readable names (max 15 chars), e.g. "brownout", "panic", "ext0", "timer"
const char* esp_reset_reason_str(esp_reset_reason_t reason);
const char* esp_wakeup_cause_str(esp_sleep_wakeup_cause_t cause);

// Why this boot happened: the reset reason, or after a deep sleep wake "wake:<cause>" (e.g. "wake:ext0").
// Returns a static buffer in the deep sleep case: not reentrant, copy it if you keep it.
const char* esp_boot_reason_str();

#endif // __TOOLS_ESP_H
