#pragma once

#include <stdint.h>

#define KEYTOOL_LONG_MASK    ((uint32_t)(0x80000000))
#define KEYTOOL_KEY_NONE     ((uint32_t)(0x00000000))
#define KEYTOOL_LONG_MS      1500
#define KEYTOOL_SHORT_MS     50
#define KEYTOOL_HOLDOFF_MS	 0

uint32_t keytool_get_event(uint32_t keystate);
