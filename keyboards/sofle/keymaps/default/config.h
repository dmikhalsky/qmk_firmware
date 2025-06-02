#pragma once

//#define MASTER_LEFT
#define MASTER_RIGHT

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   0
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    1


/*
#define PS2_INT_INIT()  do { EICRA |= ((1<<ISC01) | (0<<ISC00));} while (0)
#define PS2_INT_ON()  do { EIMSK |= (1<<INT0);} while (0)
#define PS2_INT_OFF() do { EIMSK &= ~(1<<INT0);} while (0)
#define PS2_INT_VECT   INT0_vect
*/


#define PS2_MOUSE_INVERT_Y
#define PS2_MOUSE_INVERT_X

#define PS2_MOUSE_SCROLL_BTN_MASK (1 << PS2_MOUSE_BTN_MIDDLE)
#define PS2_MOUSE_SCROLL_BTN_SEND TAPPING_TERM
#define PS2_MOUSE_SCROLL_DIVISOR_V 3
#define PS2_MOUSE_SCROLL_DIVISOR_H PS2_MOUSE_SCROLL_DIVISOR_V

//#define PS2_MOUSE_X_MULTIPLIER 2
//#define PS2_MOUSE_Y_MULTIPLIER 2
//#define PS2_MOUSE_V_MULTIPLIER 1
//#define PS2_MOUSE_USE_2_1_SCALING

#define ENCODER_RESOLUTION 8