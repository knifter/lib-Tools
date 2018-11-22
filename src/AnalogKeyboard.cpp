#include "analogkeyboard.h"

#include <Arduino.h>

#define CNT_MATCH   3

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
    if (adc > BTN_NONE)      return BTN_NONE;
    if (adc > BTN_SELECT)    return BTN_SELECT;
    if (adc > BTN_LEFT)      return BTN_LEFT;
    if (adc > BTN_DOWN)      return BTN_DOWN;
    if (adc > BTN_UP)        return BTN_UP;
    return BTN_RIGHT;
}
