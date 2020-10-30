#ifndef __COOKING_H

#define __COOKING_H

#include "IMState.h"

class Cooking : public IMState, public IICMState
{
private:
    time_t end_time;

protected:
    void ST_RUNNING(event_t e);
    void ST_POWER_SETTING(event_t e);
    void ST_TIME_DIAL_HANDLER(event_t e);

public:
    Cooking(unsigned int power, time_t duration);
    void run(event_t e);
};

#endif // ifndef __COOKING_H
