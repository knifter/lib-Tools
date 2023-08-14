#include "tools-keys.h"

#include <stdint.h>

#include <Arduino.h> // millis(), 

#include "tools-log.h"

// higher bits are taken for events
/* Events: 
Events being given are, in this order:
 KEY_NONE (No keys are pressed)
 KEY_A (if fallthrough is defined)
 KEY_A_SHORT (A is continuously pressed for SHORT_MS duration: debounced A)
 then if A is released after SHORT_MS (and before LONG_MS):
    KEY_A_SHORT | KEY_A_RELEASED (indicating A has been shortly pressed, debounced and released. Define KEY_A_PRESSED=SHORT|RELEASE as a shorthand)
 or if A was held after SHORT_MS:
    KEY_A_LONG (A is continuously pressed for LONG_MS duration)
    KEY_A_LONG_REPEAR (A keeps being pressed, re-emitted every LONG_REPEAT_MS)
    KEY_A_LONG_RELEASED (A has been released)
 KEY_RELEASED (Always emitted once after all keys are released, with key mask = 0x00)
 
 This is done also any combination of A/B/C as KEY_AC_x for example.
*/

/* example code
typedef enum : uint32_t
{
	KEY_NONE = 0x00,
    KEY_RELEASED = KEYTOOL_RELEASED,
    KEY_PRESSED = KEYTOOL_SHORT | KEYTOOL_RELEASED,

    // key defs
	KEY_A = 0x01,
	KEY_B = 0x02,
	KEY_C = 0x04,

	// combinations
	KEY_AB = KEY_A | KEY_B,
	KEY_AC = KEY_A | KEY_C,
	KEY_BC = KEY_B | KEY_C,
	KEY_ABC = KEY_A | KEY_B | KEY_C,

    // single key modes
    KEY_A_SHORT = KEY_A | KEYTOOL_SHORT,
    KEY_B_SHORT = KEY_B | KEYTOOL_SHORT,
    KEY_C_SHORT = KEY_C | KEYTOOL_SHORT,
    KEY_A_PRESSED = KEY_A | KEYTOOL_SHORT_RELEASED,
    KEY_B_PRESSED = KEY_A | KEYTOOL_SHORT_RELEASED,
    KEY_C_PRESSED = KEY_A | KEYTOOL_SHORT_RELEASED,
    KEY_A_LONG = KEY_A | KEYTOOL_LONG,
    KEY_B_LONG = KEY_B | KEYTOOL_LONG,
    KEY_C_LONG = KEY_C | KEYTOOL_LONG,
    KEY_A_LONG_REPEAT = KEY_A | KEYTOOL_LONG_REPEAT,
    KEY_B_LONG_REPEAT = KEY_B | KEYTOOL_LONG_REPEAT,
    KEY_C_LONG_REPEAT = KEY_C | KEYTOOL_LONG_REPEAT,
    KEY_A_LONG_RELEASED = KEY_A | KEYTOOL_LONG_RELEASED,
    KEY_B_LONG_RELEASED = KEY_B | KEYTOOL_LONG_RELEASED,
    KEY_C_LONG_RELEASED = KEY_C | KEYTOOL_LONG_RELEASED,    

    // combinations of 2
	KEY_AB_SHORT = KEY_AB | KEYTOOL_SHORT,
	KEY_AC_SHORT = KEY_AC | KEYTOOL_SHORT,
	KEY_BC_SHORT = KEY_BC | KEYTOOL_SHORT,
    KEY_AB_PRESSED = KEY_AB | KEYTOOL_SHORT_RELEASED,
	KEY_AB_LONG = KEY_AB | KEYTOOL_LONG,
	KEY_AC_LONG = KEY_AC | KEYTOOL_LONG,
	KEY_BC_LONG = KEY_BC | KEYTOOL_LONG,
	KEY_AB_LONG_REPEAT = KEY_AB | KEYTOOL_LONG_REPEAT,
	KEY_AC_LONG_REPEAT = KEY_AC | KEYTOOL_LONG_REPEAT,
	KEY_BC_LONG_REPEAT = KEY_BC | KEYTOOL_LONG_REPEAT,

    // combinations of 3
	KEY_ABC_PRESSED = KEY_ABC | KEYTOOL_SHORT_RELEASED,
	KEY_ABC_LONG = KEY_ABC | KEYTOOL_LONG,
	KEY_ABC_LONG_REPEAT = KEY_ABC | KEYTOOL_LONG_REPEAT,
} demo_event_t;

const char* keytool_event_name(demo_event_t e)
{
	if(e == KEY_NONE)
		return "KEY_NONE";
	if(e == KEY_RELEASED)
		return "KEY_RELEASED";

    static char buf[sizeof("KEY_ABC_SHORT_LONG_REPEAT_RELEASED")+1];
	strcpy(buf, "KEY_");                                        // 4
	if(e & KEY_A)               strcat(buf, "A");               // 1
	if(e & KEY_B)               strcat(buf, "B");               // 1
	if(e & KEY_C)               strcat(buf, "C");               // 1
	if(e & KEYTOOL_SHORT)       strcat(buf, "_SHORT");          // 6
	if(e & KEYTOOL_LONG)        strcat(buf, "_LONG");           // 5
	if(e & KEYTOOL_LONG_REPEAT) strcat(buf, "_LONG_REPEAT");    // 12
    if(e & KEYTOOL_RELEASED)    strcat(buf, "_RELEASED");       // 9
	return buf;
};

void main()
{
    uint32_t keys = 0x00;
    if(digitalRead(PIN_KEY_A))
        keys |= KEY_A;
    if(digitalRead(PIN_KEY_B))
        keys |= KEY_B;
    if(digitalRead(PIN_KEY_C))
        keys |= KEY_C;
    test_event_t event = static_cast<demo_event_t>(key2event(keys));
	switch(event)
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

    // If a released is queued, emit that first
    // After a press dissapears, a KEYTOOL_RELEASED is emitted
    if(last == KEYTOOL_RELEASED)
    {
        last = KEYTOOL_NONE;
        return KEYTOOL_RELEASED;
    };

	// Remove the modifiers, if given any (should not)
    pressed &= KEYTOOL_KEYS_MASK;

	// No key press or release
    uint32_t last_keys = last & KEYTOOL_KEYS_MASK;
	if(pressed == KEYTOOL_NONE)
	{
        // if no keys were registered, this is not a release
        if(last == KEYTOOL_NONE)
            return KEYTOOL_NONE;

        // LONG_RELEASED:
        // Button(s) was released after LONG, don't emit SHORT_RELEASED but only LONG_RELEASED, then RELEASED
		if(last & KEYTOOL_LONG)
		{
            // DBG("released after long");
			last = KEYTOOL_RELEASED;
            return last_keys | KEYTOOL_LONG_RELEASED;
		};

        // SHORT_RELEASED
        // Button was released after only SHORT time, emit SHORT_RELEASED for this combination, then RELEASED
        if(last & KEYTOOL_SHORT)
        {
            last = KEYTOOL_RELEASED;
            return last_keys | KEYTOOL_SHORT_RELEASED;
        };

		// All presses were shorter than SHORT: reset and ignore
		return last = KEYTOOL_NONE;
	};

	// so we have one or more keys pressed from now on

	// If pressed keys are added, we restart counting. But ignore modifier bits for that
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

    // Short press detect, emit right away
    if(!(last & KEYTOOL_EVENT_MASK)) // && (now - start > KEYTOOL_SHORT))
    {
        if(now - start > KEYTOOL_SHORT_MS)
        {
            last = (pressed | KEYTOOL_SHORT);
            return last;
        };
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
            // Mark as LONG and return this (removing SHORT bit)
            last = last_keys |  KEYTOOL_LONG;
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