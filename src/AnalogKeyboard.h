#ifndef __ANALOGKEYBOARD_H
#define __ANALOGKEYBOARD_H

typedef enum {
    BTN_RIGHT = 0,
    BTN_UP = 99 - 50,
    BTN_DOWN = 256 - 50,
    BTN_LEFT = 409 - 50,
    BTN_SELECT = 639 - 50,
    BTN_NONE = 1000,
} Button_t;

Button_t read_buttons();
Button_t read_buttons_once();


#endif // __ANALOGKEYBOARD_H
