#ifndef __TIME_SETUP_H

#define __TIME_SETUP_H

#include "IMState.h"

enum TIME_SETUP_STATE
{
    HOUR,
    MINUTE,
};

class TimeSetup : public IMState
{
private:
    enum TIME_SETUP_STATE state;
    time_t raw_time;

private:
    void ST_HOUR(event_t e);
    void ST_MINUTE(event_t e);
    void changeTime();

public:
    TimeSetup();
    void run(event_t e);
};

#endif // ifndef __TIME_SETUP_H
