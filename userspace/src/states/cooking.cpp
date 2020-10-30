#include <iostream>

#include "../displayControl/displayControl.h"
#include "../utils/utils.h"
#include "../utils/logging.h"
#include "cooking.h"
#include "init.h"

Cooking::Cooking(unsigned int power, time_t duration)
{
    this->power    = power;
    this->duration = duration;
    this->end_time = time(NULL) + duration;
    this->bouncer  = Bouncer();
    this->state    = RUNNING;
    this->state_e  = COOKING_RUNNING;
}

using namespace logging;

void Cooking::run(event_t e)
{
    LOG_INFO("Running cooking");
    if (this->duration <= 0)
    {
        this->context->setState(new Init());
        return;
    }

    switch (e.sig)
    {
        case TIME_PRESSED:
            bouncer.start(2);
            this->context->displayHandler->displayOSTime();
        default:
            switch (this->state)
            {
                case RUNNING:
                    ST_RUNNING(e);
                    break;
                case POWER_SETTING:
                    ST_POWER_SETTING(e);
                    break;
                case TIME_DIAL_HANDLER:
                    ST_TIME_DIAL_HANDLER(e);
                    break;
            }
    }
}

void Cooking::ST_TIME_DIAL_HANDLER(event_t e)
{
    this->state_e = COOKING_TIME_DIAL_HANDLER;

    this->duration = TimeDialConvert(this->duration, e.ret);
    bouncer.start(1);
    this->context->displayHandler->display(this->duration, TIME);

    this->state = RUNNING;
}

void Cooking::ST_POWER_SETTING(event_t e)
{
    this->state_e = COOKING_POWER_SETTING;

    this->power = e.ret;
    bouncer.start(2);
    this->context->displayHandler->display(this->power, NUMBER);

    this->state = RUNNING;
}

void Cooking::ST_RUNNING(event_t e)
{
    this->state_e = COOKING_RUNNING;

    switch (e.sig)
    {
        case P_PRESSED:
            this->state = POWER_SETTING;
            this->run(e);
            break;
        case TIME_DIAL_CHANGED:
            this->state = TIME_DIAL_HANDLER;
            this->run(e);
            break;
        default:
            if (bouncer.timeout())
            {
                // duration will be treated as countdown
                this->context->displayHandler->display(this->duration, TIME);
            }
            else
            {
                bouncer.update();
            }

            this->context->displayHandler->setOvenLED(HIGH);

            if (context->isDoorOpen())
            {
                this->context->displayHandler->setRadiator(0);
                this->end_time = time(NULL) + this->duration; // Keep time unchanged
            }
            else
            {
                time_t current_time = time(NULL);
                this->duration      = this->end_time - current_time;
                this->context->displayHandler->setRadiator(this->power);
            }
    }
}
