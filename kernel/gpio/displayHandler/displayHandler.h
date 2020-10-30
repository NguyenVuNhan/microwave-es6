#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include <linux/types.h>

#define ZERO    0b01111110
#define ONE     0b00110000
#define TWO     0b01101101
#define THREE   0b01111100
#define FOUR    0b00110011
#define FIVE    0b01011011
#define SIX     0b01011111
#define SEVEN   0b01110000
#define EIGHT   0b01111111
#define NINE    0b01111011


int setNumber(int8_t digitLocation, char value);

#endif // DISPLAY_HANDLER_H