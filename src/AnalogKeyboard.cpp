#include "analogkeyboard.h"

#include <Arduino.h>

#define CNT_MATCH   3

Button_t AnalogKeyboard::read_buttons_once()
{
    Button_t key = read_buttons();

    static Button_t key_prv = BTN_NONE;
    static uint8_t cnt = 0;
    if(key != key_prv)
    {
        cnt = 0;
        key_prv = key;
        return BTN_NONE;
    };
    cnt++;
    if(cnt == CNT_MATCH)
        return key;

    return BTN_NONE;
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
