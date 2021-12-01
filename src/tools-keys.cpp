#include "tools-keys.h"

#include <stdint.h>

#include <Arduino.h> // millis(), 

#include "tools-log.h"

// higher bits are taken for events
#define KEYTOOL_MODIFIER_MASK	(KEYTOOL_SHORT | KEYTOOL_LONG | KEYTOOL_LONG_REPEAT | KEYTOOL_RELEASED)
#define KEYTOOL_KEYS_MASK       (~KEYTOOL_MODIFIER_MASK)    

/*
    Debug code:
	switch(e)
	{
		case KEY_A:                 Serial.println("KEY_A"); break;
	    case KEY_B:                 Serial.println("KEY_B"); break;
		case KEY_AB:                Serial.println("KEY_AB"); break;
		case KEY_A_SHORT:           Serial.println("KEY_A_SHORT"); break;
		case KEY_A_LONG:            Serial.println("KEY_A_LONG"); break;
		case KEY_A_LONG_REPEAT:     Serial.println("KEY_A_LONG_REPEAT"); break;
		case KEY_B_SHORT:           Serial.println("KEY_B_SHORT"); break;
		case KEY_B_LONG:            Serial.println("KEY_B_LONG"); break;
		case KEY_B_LONG_REPEAT:     Serial.println("KEY_B_LONG_REPEAT"); break;
		case KEY_AB_SHORT:          Serial.println("KEY_AB_SHORT"); break;
		case KEY_AB_LONG:           Serial.println("KEY_AB_LONG"); break;
		case KEY_AB_LONG_REPEAT:    Serial.println("KEY_AB_LONG_REPEAT"); break;
		case KEY_RELEASED:          Serial.println("KEY_RELEASED"); break;
	};
*/

uint32_t key2event(uint32_t pressed)
{
	static uint32_t last = KEYTOOL_NONE;
	static uint32_t start = 0;

	uint32_t now = millis();

	// Remove the modifiers, if given any (should not)
    pressed &= KEYTOOL_KEYS_MASK;

	// No key press or release
	if(pressed == KEYTOOL_NONE)
	{
        // if no keys were registered, this is not a release
        if(!last)
            return KEYTOOL_NONE;

		// last one was long press which is now released, we already sent out an event so skip sending a short
		if(last & KEYTOOL_LONG)
		{
            // DBG("released after long");
			last = KEYTOOL_NONE;
			start = now;
            return KEYTOOL_RELEASED;
		};

		// Did we release a key?
		uint32_t ret = KEYTOOL_NONE;
		// Short press detect, only if long enough will we return it
		if((now - start) > KEYTOOL_SHORT_MS)
			ret = last | KEYTOOL_SHORT;

		// reset detector
		last = KEYTOOL_NONE;
		start = now;
		return ret;
	};

	// so we have a (or more) key pressed from now on

	// If pressed keys are added, we restart counting. But ignore modifier bits for that
    uint32_t last_keys = last & KEYTOOL_KEYS_MASK;
    if(last_keys != (pressed | last_keys))
	{
        // keys are added, modifiers removed
		last = (last | pressed) & KEYTOOL_KEYS_MASK; 
		start = now;
#ifdef KEYTOOL_FALLTHROUGH
        return pressed;
#else
        return KEYTOOL_NONE;
#endif
	};

	// Long press detect
    if(last & KEYTOOL_LONG)
    {
        // LONG already set: waiting for LONG_REPEAT
        if(now - start > KEYTOOL_LONG_REPEAT_MS)
        {
            // this is LONG_REPEAT, we need to remove modifiers, only add LONG_REPEAT
            // but also send full key detected key mask to prevent AB_LONG->A_LONG migration
            // while releasing keys
            start = now;
            return last_keys | KEYTOOL_LONG_REPEAT; // for all previously pressed keys
        };
    }else{
        // LONG not set: waiting for LONG
        if(now - start > KEYTOOL_LONG_MS)
        {
            // Mark as LONG and return this
            last |= KEYTOOL_LONG;
            start = now;
            return last;
        };
    };

    // nothing, just chillin' until LONG or LONG_REPEAT
#ifdef KEYTOOL_FALLTHROUGH
    return pressed;
#else
    return KEYTOOL_NONE;
#endif
};

#if KEYTOOL_HOLDOFF_MS > 0
    #error "HOLDOFF no longer supported. Implement in calling loop."
#endif
