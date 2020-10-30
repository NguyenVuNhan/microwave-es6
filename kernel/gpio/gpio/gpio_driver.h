#ifndef __GPIO_DRIVER

#define __GPIO_DRIVER

#include <linux/kernel.h>
#include <linux/module.h>

enum registerType
{
	DirClr,
	DirSet,
};

enum customError
{
	fileError = -1,
	noOutpStateReg = -2,
};

ssize_t setGpioOutput(uint8_t port, uint8_t pin, uint8_t value);

ssize_t getGpioState(uint8_t port, uint8_t pin);

ssize_t setMux(uint8_t port, uint8_t pin, uint8_t value);

ssize_t setDirection(uint8_t port, uint8_t pin, uint8_t direction);

#endif
