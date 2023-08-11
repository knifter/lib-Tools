#pragma once

#include <stdint.h>

#define KEYTOOL_NONE           ((uint32_t)(0x00000000))
#define KEYTOOL_SHORT          ((uint32_t)(0x10000000))
#define KEYTOOL_LONG           ((uint32_t)(0x20000000))
#define KEYTOOL_LONG_REPEAT    ((uint32_t)(0x40000000))
#define KEYTOOL_RELEASED       ((uint32_t)(0x80000000))
#define KEYTOOL_LONG_RELEASED  (KEYTOOL_LONG | KEYTOOL_RELEASED) 
#define KEYTOOL_EVENT_MASK     ((uint32_t)(0xF0000000))
#define KEYTOOL_SHORT_MS       50
#define KEYTOOL_LONG_MS        1000
#define KEYTOOL_LONG_REPEAT_MS 100

uint32_t key2event(uint32_t keystate);
