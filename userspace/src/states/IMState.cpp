#include <iostream>
#include <iterator>
#include <ostream>

#include "IMState.h"
#include "init.h"

MSTATE IMState::getState_e()
{
    return this->state_e;
}

void IMState::setContext(MStateContext* context)
{
    this->context = context;
}

MStateContext::MStateContext(IMState*         state,
                             IMemoryHandler*  memoryHandler,
                             IDisplayControl* displayHandler)
    : state(nullptr), doorOpen(false), memoryHandler(memoryHandler), displayHandler(displayHandler)
{
    this->willDeleteMemoryHandler  = false;
    this->willDeleteDisplayHandler = false;

    if (memoryHandler == nullptr)
    {
        this->memoryHandler           = new LPCMemoryHandler();
        this->willDeleteMemoryHandler = true;
    }

    if (displayHandler == nullptr)
    {
        this->displayHandler           = new LPCDisplayControl();
        this->willDeleteDisplayHandler = true;
    }

    this->setState(state);
}

MStateContext::~MStateContext()
{
    if (this->state != nullptr)
        delete this->state;
    if (willDeleteMemoryHandler)
        delete this->memoryHandler;
    if (willDeleteDisplayHandler)
        delete this->displayHandler;
}

MSTATE MStateContext::getState()
{
    return this->state->getState_e();
}

void MStateContext::setState(IMState* state)
{
    if (this->state != nullptr)
    {
        delete this->state;
    }
    this->state = state;
    this->state->setContext(this);
}

void MStateContext::run(event_t e)
{
    switch (e.sig)
    {
        case DOOR_OPEN:
            this->doorOpen = true;
            this->state->run(e);
            break;
        case DOOR_CLOSE:
            this->doorOpen = false;
            this->state->run(e);
            break;
        case STOP_PRESSED:
            this->setState(new Init());
            break;
        default:
            this->state->run(e);
            break;
    }
}

bool MStateContext::isDoorOpen()
{
    return this->doorOpen;
}
