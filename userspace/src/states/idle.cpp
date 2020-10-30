#include "../displayControl/displayControl.h"
#include "../utils/utils.h"
#include "../utils/logging.h"
#include "cooking.h"
#include "idle.h"
#include "init.h"
#include "memorySetup.h"
#include "timeSetup.h"

#include <ostream>

using namespace logging;

Idle::Idle()
{
    this->power              = 0;
    this->duration           = 0;
    this->bouncer            = Bouncer();
    this->timePressedBouncer = Bouncer();
    this->isTimeBtnHolding   = false;
    this->state              = RUNNING;
    this->state_e            = IDLE_RUNNING;
}

void Idle::run(event_t e)
{
    LOG_INFO("running idle");
    if (this->isTimeBtnHolding)
    {
        this->timePressedBouncer.update();
        if (this->timePressedBouncer.timeout())
        {
            this->context->setState(new TimeSetup());
            return;
        }
    }

    switch (e.sig)
    {
        case START_PRESSED:
            if (this->power == 0)
            {
                this->power = this->context->memoryHandler->getPower();
            }
            if (this->duration == 0)
            {
                this->duration = this->context->memoryHandler->getDuration();
            }
            this->context->setState(new Cooking(this->power, this->duration));
            break;
        case M_PRESSED:
            this->context->displayHandler->setMemoryLED(HIGH);
            this->context->setState(new MemorySetup());
            break;
        case TIME_PRESSED:
            this->state_e = TIME_BTN_DEBOUNCER;
            this->timePressedBouncer.start(2);
            this->isTimeBtnHolding = true;
            break;
        case TIME_RELEASE:
            this->isTimeBtnHolding = false;
            break;
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

void Idle::ST_TIME_DIAL_HANDLER(event_t e)
{
    switch (e.sig)
    {
        case TIME_DIAL_CHANGED:
            this->duration = TimeDialConvert(this->duration, e.ret);
            bouncer.start(DISPLAY_TIMEOUT);
            this->context->displayHandler->display(this->duration, TIME);
            break;
        default:
            this->state_e = IDLE_TIME_DIAL_HANDLER;
            this->bouncer.update();
            if (bouncer.timeout())
            {
                this->state = RUNNING;
            }
            break;
    }
}

void Idle::ST_POWER_SETTING(event_t e)
{
    switch (e.sig)
    {
        case P_PRESSED:
            this->power = e.ret;
            bouncer.start(DISPLAY_TIMEOUT);
            this->context->displayHandler->display(this->power, NUMBER);
            break;
        case TIME_DIAL_CHANGED:
            this->duration = TimeDialConvert(this->duration, e.ret);
            bouncer.start(DISPLAY_TIMEOUT);

            this->context->displayHandler->display(this->duration, TIME);
            this->state = TIME_DIAL_HANDLER;
            break;
        default:
            this->state_e = IDLE_POWER_SETTING;
            this->bouncer.update();
            if (bouncer.timeout())
            {
                this->state = RUNNING;
            }
            break;
    }
}

void Idle::ST_RUNNING(event_t e)
{
    this->state_e = IDLE_RUNNING;

    switch (e.sig)
    {
        case P_PRESSED:
            this->power = e.ret;
            bouncer.start(DISPLAY_TIMEOUT);

            this->context->displayHandler->display(this->power, NUMBER);
            this->state = POWER_SETTING;
            this->run(e);
            break;
        case TIME_DIAL_CHANGED:
            this->duration = TimeDialConvert(this->duration, e.ret);
            bouncer.start(DISPLAY_TIMEOUT);

            this->context->displayHandler->display(this->duration, TIME);
            this->state = TIME_DIAL_HANDLER;
            this->run(e);
            break;
        default:
            this->context->displayHandler->displayOSTime();
    }
}
