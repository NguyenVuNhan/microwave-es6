#include "../displayControl/displayControl.h"
#include "../utils/logging.h"
#include "../utils/utils.h"
#include "idle.h"
#include "memorySetup.h"

using namespace logging;

MemorySetup::MemorySetup()
{
    this->power    = 0;
    this->duration = 0;
    this->bouncer  = Bouncer();
    this->state    = RUNNING;
    this->state_e  = MEMORY_SETUP_RUNNING;
    this->bouncer.start(DISPLAY_TIMEOUT);
}

void MemorySetup::run(event_t e)
{
    LOG_INFO("running memory setup");
    this->bouncer.update();
    if (bouncer.timeout())
    {
        this->context->displayHandler->setMemoryLED(LOW);
        this->context->setState(new Idle());
        return;
    }

    switch (e.sig)
    {
        case M_PRESSED:
            if (this->power != 0 && this->duration >= 0)
            {
                this->context->memoryHandler->save(this->power, this->duration);
            }
            this->context->displayHandler->setMemoryLED(LOW);
            this->context->setState(new Idle());
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

void MemorySetup::ST_TIME_DIAL_HANDLER(event_t e)
{
    this->state_e = MEMORY_SETUP_TIME_DIAL_HANDLER;

    switch (e.sig)
    {
        case P_PRESSED:
            this->power = e.ret;
            bouncer.start(DISPLAY_TIMEOUT);
            this->context->displayHandler->display(this->power, NUMBER);

            this->state = POWER_SETTING;
            break;
        case TIME_DIAL_CHANGED:
            this->duration = TimeDialConvert(this->duration, e.ret);
            bouncer.start(DISPLAY_TIMEOUT);
            this->context->displayHandler->display(this->duration, TIME);
            break;
        default:
            break;
    }
}

void MemorySetup::ST_POWER_SETTING(event_t e)
{
    this->state_e = MEMORY_SETUP_POWER_SETTING;

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
            break;
    }
}

void MemorySetup::ST_RUNNING(event_t e)
{
    this->state_e = MEMORY_SETUP_RUNNING;

    switch (e.sig)
    {
        case P_PRESSED:
            this->power = e.ret;
            bouncer.start(DISPLAY_TIMEOUT);

            this->state = POWER_SETTING;
            break;
        case TIME_DIAL_CHANGED:
            this->duration = TimeDialConvert(this->duration, e.ret);
            bouncer.start(DISPLAY_TIMEOUT);

            this->state = TIME_DIAL_HANDLER;
            break;
        default:
            this->context->displayHandler->displayOSTime();
    }
}
