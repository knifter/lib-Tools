#ifndef __ANALOGKEYBOARD_H
#define __ANALOGKEYBOARD_H

#include <Arduino.h>
#include <stdint.h>

typedef enum {
    BTN_RIGHT = 0,
    BTN_UP = 99 - 50,
    BTN_DOWN = 256 - 50,
    BTN_LEFT = 409 - 50,
    BTN_SELECT = 639 - 50,
    BTN_NONE = 1000,
} Button_t;

class AnalogKeyboard
{
public:
    AnalogKeyboard(const uint8_t analog_pin = PIN_A0) : _pin(analog_pin) {};
        
    Button_t read_buttons_once();
    Button_t read_buttons();

private:
    uint8_t _pin;
};


#endif // __ANALOGKEYBOARD_H
