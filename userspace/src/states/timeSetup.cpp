#include "../displayControl/displayControl.h"
#include "../utils/logging.h"
#include "idle.h"
#include "timeSetup.h"

#include <iostream>

using namespace logging;

TimeSetup::TimeSetup()
{
    this->bouncer = Bouncer();
    this->bouncer.start(DISPLAY_TIMEOUT);
    this->state    = HOUR;
    this->state_e  = TIME_SETUP_HOUR;
    this->raw_time = time(NULL);
}

void TimeSetup::run(event_t e)
{
    LOG_INFO("running time setup");
    this->bouncer.update();
    if (this->bouncer.timeout())
    {
        this->context->setState(new Idle());
        return;
    }

    switch (this->state)
    {
        case HOUR:
            ST_HOUR(e);
            break;
        case MINUTE:
            ST_MINUTE(e);
            break;
    }
}

void TimeSetup::ST_HOUR(event_t e)
{
    this->state_e = TIME_SETUP_HOUR;

    switch (e.sig)
    {
        case TIME_PRESSED:
            this->state = MINUTE;
            break;
        case TIME_DIAL_CHANGED:
            this->raw_time += e.ret * 3600;
            this->context->displayHandler->display(this->raw_time / 60, TIME);
            break;
        default:
            break;
    }
}

void TimeSetup::ST_MINUTE(event_t e)
{
    this->state_e = TIME_SETUP_MINUTE;

    switch (e.sig)
    {
        case TIME_PRESSED:
            changeTime();
            this->context->setState(new Idle());
            break;
        case TIME_DIAL_CHANGED:
            this->raw_time += (e.ret % 60) * 60;
            this->context->displayHandler->display(this->raw_time / 60, TIME);
            break;
        default:
            break;
    }
}

void TimeSetup::changeTime()
{
    this->raw_time += 80 * 60;
#ifndef TESTING
    stime(&raw_time);
#endif
}
