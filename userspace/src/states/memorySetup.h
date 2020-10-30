#ifndef __MEMORY_SETUP_H

#define __MEMORY_SETUP_H

#include "IMState.h"

class MemorySetup : public IMState, public IICMState
{
protected:
    void ST_RUNNING(event_t e);
    void ST_POWER_SETTING(event_t e);
    void ST_TIME_DIAL_HANDLER(event_t e);

public:
    MemorySetup();
    void run(event_t);
};

#endif // ifndef __MEMORY_SETUP_H
