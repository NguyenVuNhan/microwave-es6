#ifndef __DISPLAY_CONTROL_H

#define __DISPLAY_CONTROL_H

#include "../hardware/display_abstraction.h"

class LPCDisplayControl : public IDisplayControl
{
public:
    void display(long t, DISPLAY_TYPE type);
    void displayOSTime();
    void setRadiator(unsigned int value);
    void setOvenLED(PIN_STATE state);
    void setMemoryLED(PIN_STATE state);
};

#endif // ifndef __DISPLAY_CONTROL_H
