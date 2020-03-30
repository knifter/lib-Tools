#include "keytool.h"

#include <stdint.h>

#include <Arduino.h> // millis(), 

uint32_t keytool_get_event(uint32_t keystate)
{
	static uint32_t last = KEYTOOL_KEY_NONE;
	static uint32_t start = 0;

    keystate = keystate & (~KEYTOOL_LONG_MASK);

	// Hold off our cycle if we're called too soon
	uint32_t now = millis();
#if KEYTOOL_HOLDOFF_MS > 0
	static uint32_t lasttime = 0;
	if(now - lasttime < KEYTOOL_HOLDOFF_MS)
		return KEYTOOL_KEY_NONE;
	lasttime = now;
#endif

	// Serial.printf("pressed: %x, last: %x, start = %u, now = %u, hold = %d\n", pressed, last, start, now, now - start);

	// Did we release a key?
	if(keystate == KEYTOOL_KEY_NONE)
	{
		// last one was long press, now released, which wont be a short press
		if(last & KEYTOOL_LONG_MASK) 
		{
			last = KEYTOOL_KEY_NONE;
			start = now;
		}

		// Did we release a key?
		uint32_t ret = KEYTOOL_KEY_NONE;
		// Short press detect, only if long enough will we return it
		if((now - start) > KEYTOOL_SHORT_MS)
			ret = last;
		// reset detector
		last = KEYTOOL_KEY_NONE;
		start = now;
		return ret;
	};

	// so we have a key pressed from now on

	// first press down?
	if(!(last & KEYTOOL_LONG_MASK) && last != keystate)
	{
		last = keystate; 
		start = now;
	};

	// Long press detect
	if(now - start > KEYTOOL_LONG_MS)
	{
		if(last & KEYTOOL_LONG_MASK) // long press already detected
			return KEYTOOL_KEY_NONE;

		last |= KEYTOOL_LONG_MASK; // make it a long press
		return last;

		// // last = KEY_NONE; // to prevent short key detect
		// start = now;
	};

	return KEYTOOL_KEY_NONE;
}
