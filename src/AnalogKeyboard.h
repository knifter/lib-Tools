#ifndef __ANALOGKEYBOARD_H
#define __ANALOGKEYBOARD_H

#include <Arduino.h>
#include <stdint.h>

// Key identifiers are chosen specifically: long presses have 0x01 set, short do not!
typedef enum {
    BTN_NONE = 0,
    BTN_RIGHT = 2,
    BTN_RIGHT_LONG,
    BTN_UP,
    BTN_UP_LONG,
    BTN_DOWN,
    BTN_DOWN_LONG,
    BTN_LEFT,
    BTN_LEFT_LONG,
    BTN_SELECT,
    BTN_SELECT_LONG,
} Button_t;

class AnalogKeyboard
{
public:
    AnalogKeyboard(const uint8_t analog_pin = PIN_A0) : _pin(analog_pin) {};
        
    Button_t read_buttons_long();
    Button_t read_buttons_once();
    Button_t read_buttons();

private:
    uint8_t _pin;
};


#endif // __ANALOGKEYBOARD_H
