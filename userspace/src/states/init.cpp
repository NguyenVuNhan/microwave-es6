#include "../displayControl//displayControl.h"
#include "../utils/logging.h"
#include "idle.h"
#include "init.h"

#include <iostream>

using namespace logging;

Init::Init()
{
    this->state_e = INIT;
}

void Init::run(event_t e)
{
    LOG_INFO("running init");
    this->context->displayHandler->displayOSTime();
    this->context->displayHandler->setRadiator(0);
    this->context->displayHandler->setOvenLED(LOW);
    this->context->setState(new Idle());
}
