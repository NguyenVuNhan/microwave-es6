#include "displayHandler.h"
#include "../GPIO/gpio_driver.h"
#include "../GPIO/include/common.h"
#include <linux/delay.h>
#include <linux/module.h>

//int getPort(int8_t digitLocation)
//{
//    switch(digitLocation)
//    {
//        case 0:
//        case 1:
//            return 0;
//        case 2:
//        case 3:
//            return 1;
//        default:
//            return -1;
//    }
//}

int8_t getPin(int8_t digitLocation)
{
    switch(digitLocation)
    {
        case 0:
            return 15;
        case 1:
            return 17;
        case 2:
            return 19;
        case 3:
            return 21;
        default:
            return -EINVAL;
    }
}

int setNumber(int8_t digitLocation, char digit)
{
    int8_t i, pin;
    int8_t port = 1;
    int8_t errorCode = 0;

//    port = getPort(digitLocation);
    pin = getPin(digitLocation);

    if(port < 0 || pin < 0)
        return -1;
    for(i = 0; i < 8; i++)
    {
        int8_t stripeState = (digit >> i) & 1;
        errorCode += setGpioOutput(port, pin, stripeState);
        errorCode += setGpioOutput(port, pin + 1, Low);
        ndelay(100);
        errorCode += setGpioOutput(port, pin + 1, High);
        if(errorCode != 0)
            return errorCode;
    }
    errorCode += setGpioOutput(3, 4, Low);
    ndelay(100);
    errorCode += setGpioOutput(3, 4, High);
    return 0;
}

