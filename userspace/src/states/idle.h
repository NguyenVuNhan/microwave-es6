#ifndef __IDLE_H

#define __IDLE_H

#include "IMState.h"

class Idle : public IMState, public IICMState
{
private:
    Bouncer timePressedBouncer;
    bool    isTimeBtnHolding;

protected:
    void ST_RUNNING(event_t e);
    void ST_POWER_SETTING(event_t e);
    void ST_TIME_DIAL_HANDLER(event_t e);

public:
    Idle();
    void run(event_t e);
};

#endif // ifndef __IDLE_H
