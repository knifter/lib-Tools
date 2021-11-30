# Common c++ Tools Library for my projects

*KeyTools*
Function to debounce and detect short/long/simultaneous presses

*NonCopyable*
Disables copy- and assignemnt constructors when inherited from

*log.h*
Log formatter helpers

## tools-keys.cpp: key2event 
Convert raw key scan bits to events: debounce, detect simultaneous presses and all with short, long, long repeat, release events.

### Usage
 * Define enum with key bits, combinations etc
 * Scan keys into bits of a uint32_t (or the keys)
 * feed these bits through key2event() often
 * key2event uses internal time-tracking to generate events for each key and combinations

### Example
Define your enum for used combinations:
```
typedef enum : uint32_t
{
  KEY_NONE = 0x00,
  KEY_RELEASED = KEYTOOL_RELEASED,

  // key defs
  KEY_A = 0x01,
  KEY_B = 0x02,
  KEY_C = 0x04,

  // single key modes
  KEY_A_SHORT = KEY_A | KEYTOOL_SHORT,
  KEY_B_SHORT = KEY_B | KEYTOOL_SHORT,
  KEY_C_SHORT = KEY_C | KEYTOOL_SHORT,
  KEY_A_LONG = KEY_A | KEYTOOL_LONG,
  KEY_B_LONG = KEY_B | KEYTOOL_LONG,
  KEY_C_LONG = KEY_C | KEYTOOL_LONG,
  KEY_A_LONG_REPEAT = KEY_A | KEYTOOL_LONG_REPEAT,
  KEY_B_LONG_REPEAT = KEY_B | KEYTOOL_LONG_REPEAT,
  KEY_C_LONG_REPEAT = KEY_C | KEYTOOL_LONG_REPEAT,

  // combinations of 2
  KEY_AB_SHORT = KEY_A | KEY_B | KEYTOOL_SHORT,
  KEY_AC_SHORT = KEY_A | KEY_C | KEYTOOL_SHORT,
  KEY_BC_SHORT = KEY_B | KEY_C | KEYTOOL_SHORT,
  KEY_AB_LONG = KEY_A | KEY_B | KEYTOOL_LONG,
  KEY_AC_LONG = KEY_A | KEY_C | KEYTOOL_LONG,
  KEY_BC_LONG = KEY_B | KEY_C | KEYTOOL_LONG,
  KEY_AB_LONG_REPEAT = KEY_A | KEY_B | KEYTOOL_LONG_REPEAT,
  KEY_AC_LONG_REPEAT = KEY_A | KEY_C | KEYTOOL_LONG_REPEAT,
  KEY_BC_LONG_REPEAT = KEY_B | KEY_C | KEYTOOL_LONG_REPEAT,

  // combinations of 3
  KEY_ABC_SHORT = KEY_A | KEY_B | KEY_C | KEYTOOL_SHORT,
  KEY_ABC_LONG = KEY_A | KEY_B | KEY_C | KEYTOOL_LONG,
  KEY_ABC_LONG_REPEAT = KEY_A | KEY_B | KEY_C | KEYTOOL_LONG_REPEAT,
} keyevent_t;
```

and use key2event() like this:
```
void test_keys()
{
  // Scan keys (note the OR'ing!)
  uint32_t pressed = KEY_NONE;
  if(digitalRead(PIN_BTN_A) == LOW)
  pressed |= KEY_A;
  if(digitalRead(PIN_BTN_B) == LOW)
  pressed |= KEY_B;
  if(digitalRead(PIN_BTN_C) == LOW)
  pressed |= KEY_C;

  // feed through key2event
  uint32_t k = key2event(pressed);
  
  // Check results
  switch(k)
  {
    case KEY_A_SHORT:           print("A short-pressed"); break;
    case KEY_A_LONG:            print("A long press"); break;
    case KEY_A_LONG_REPEAT:     print("A long repeated event"); break;
    case KEY_B_SHORT:           print("B short-pressed"); break;
    case KEY_B_LONG:            print("B long press"); break;
    case KEY_B_LONG_REPEAT:     print("B long press is held"); break;
    case KEY_AB_SHORT:          print("A+B combined"); break;
    case KEY_AB_LONG:           print("A+B long pressed"); break;
    case KEY_AB_LONG_REPEAT:    print("A+B long held"); break;
    case KEY_RELEASED:          print("long press is released"); break;
  };
};
```

If you need immidiate key responses as well you can let the keys 'fall-through' too.
```
  keyevent_t k = key2event(pressed) | pressed;
```

And check for raw keys:
```
  // Check results
  switch(e)
  {
    case KEY_A:                 print("A is pressed"); break;
    case KEY_A_SHORT:           print("A short-pressed"); break;
    case KEY_A_LONG:            print("A long press"); break;
    case KEY_A_LONG_REPEAT:     print("A long repeated event"); break;
    case KEY_B:                 print("B is pressed"); break;
    ....
    
  };
```
