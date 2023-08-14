#pragma once

#include <stdint.h>

// Needed for defining your event_t enum
#define KEYTOOL_NONE            ((uint32_t)(0x00000000))
#define KEYTOOL_SHORT           ((uint32_t)(0x10000000))
#define KEYTOOL_LONG            ((uint32_t)(0x20000000))
#define KEYTOOL_LONG_REPEAT     ((uint32_t)(0x40000000))
#define KEYTOOL_RELEASED        ((uint32_t)(0x80000000))
#define KEYTOOL_SHORT_RELEASED  (KEYTOOL_SHORT | KEYTOOL_RELEASED)
#define KEYTOOL_LONG_RELEASED   (KEYTOOL_LONG | KEYTOOL_RELEASED) 
#define KEYTOOL_EVENT_MASK      ((uint32_t)(0xF0000000))
#define KEYTOOL_KEYS_MASK       (~KEYTOOL_EVENT_MASK)   

// If not defined, use these defaults:
#ifndef KEYTOOL_SHORT_MS
    #define KEYTOOL_SHORT_MS       50
#endif
#ifndef KEYTOOL_LONG_MS
    #define KEYTOOL_LONG_MS        800
#endif
#ifndef KEYTOOL_LONG_REPEAT_MS
    #define KEYTOOL_LONG_REPEAT_MS 100
#endif

uint32_t key2event(uint32_t keystate);
