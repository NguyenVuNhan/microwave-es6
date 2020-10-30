#ifndef __DISPLAY_ABSTRACTION_H

#define __DISPLAY_ABSTRACTION_H

#include <time.h>

#include <string>

enum PIN_STATE
{
    LOW,
    HIGH
};

enum DISPLAY_TYPE
{
    TIME,
    NUMBER
};

class IDisplayControl
{
public:
    virtual ~IDisplayControl() {}
    virtual void display(long t, DISPLAY_TYPE type) = 0;
    virtual void displayOSTime()                    = 0;
    virtual void setRadiator(unsigned int value)    = 0;
    virtual void setOvenLED(PIN_STATE state)        = 0;
    virtual void setMemoryLED(PIN_STATE state)      = 0;
};

#endif // ifndef __DISPLAY_ABSTRACTION_H
