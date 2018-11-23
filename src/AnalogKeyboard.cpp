#include "analogkeyboard.h"

#include <Arduino.h>

#define CNT_MATCH           3
#define LONG_PRESS_MS       500

enum {
    VAL_RIGHT = 0,
    VAL_UP = 99 - 50,
    VAL_DOWN = 256 - 50,
    VAL_LEFT = 409 - 50,
    VAL_SELECT = 639 - 50,
    VAL_NONE = 1000,
};

Button_t AnalogKeyboard::read_buttons_long()
{
    Button_t key1 = read_buttons();

    // Only process key if we have three identical reads
    static uint8_t cnt = 0;
    static Button_t key = BTN_NONE;
    if(key1 != key)
    {
        key = key1;
        cnt = 0;
        return BTN_NONE;
    };
    cnt++;
    if(cnt < CNT_MATCH)
        return BTN_NONE;

    // only return this state once
    Serial.println("start");
    static Button_t key_prv = BTN_NONE;
    static uint32_t key_start = 0;

    // first press
    if(key > BTN_NONE && key_prv == BTN_NONE)
    {
        Serial.println("first");
        key_start = millis();
        key_prv = key;
        return BTN_NONE;
    };
    Serial.println("!first");

    // Detect long
    bool longpress = false;
    if(millis() > key_start + LONG_PRESS_MS)
    {
        Serial.println("long");
        key = (Button_t) key | 0x01; // Convert short press to _LONG
    };

    // Detect release or short -> long
    if(key == BTN_NONE && key_prv != BTN_NONE)
    {
        Serial.println("release");
        key_prv = key;
        return key;
    }
    Serial.println("end");
    return BTN_NONE;
};

Button_t AnalogKeyboard::read_buttons_once()
{
    Button_t key1 = read_buttons();

    // Only process key if we have three identical reads
    static uint8_t cnt = 0;
    static Button_t key = BTN_NONE;
    if(key1 != key)
    {
        key = key1;
        cnt = 0;
        return BTN_NONE;
    };
    cnt++;
    if(cnt < CNT_MATCH)
        return BTN_NONE;

    // only return this state once
    static Button_t key_prv = BTN_NONE;
    if(key == key_prv)
        return BTN_NONE;

    key_prv = key;
    return key;
};

Button_t AnalogKeyboard::read_buttons()
{
    int adc = analogRead(_pin);      // read the value from the sensor
    if (adc > VAL_NONE)      return BTN_NONE;
    if (adc > VAL_SELECT)    return BTN_SELECT;
    if (adc > VAL_LEFT)      return BTN_LEFT;
    if (adc > VAL_DOWN)      return BTN_DOWN;
    if (adc > VAL_UP)        return BTN_UP;
    return BTN_RIGHT;
}
