#ifndef __IMSTATE_H

#define __IMSTATE_H

#include "../displayControl/displayControl.h"
#include "../event.h"
#include "../utils/bounce.h"
#include "../utils/memoryHandler.h"

#include <time.h>

#include <iostream>

#ifdef TESTING
    #define DISPLAY_TIMEOUT 2
#else
    #define DISPLAY_TIMEOUT 60
#endif // ifndef TEST_CONFIG

#ifndef nullptr
    #define nullptr 0
#endif // ifndef nullptr

enum ICMSTATE
{
    RUNNING,
    POWER_SETTING,
    TIME_DIAL_HANDLER
};


enum MSTATE
{
    INIT,
    IDLE_RUNNING,
    IDLE_POWER_SETTING,
    IDLE_TIME_DIAL_HANDLER,
    COOKING_RUNNING,
    COOKING_POWER_SETTING,
    COOKING_TIME_DIAL_HANDLER,
    MEMORY_SETUP_RUNNING,
    MEMORY_SETUP_POWER_SETTING,
    MEMORY_SETUP_TIME_DIAL_HANDLER,
    TIME_BTN_DEBOUNCER,
    TIME_SETUP_HOUR,
    TIME_SETUP_MINUTE
};

class MStateContext;

class IMState
{
protected:
    Bouncer        bouncer;
    MSTATE         state_e;
    MStateContext* context;

public:
    virtual ~IMState() {};
    virtual void run(event_t e) = 0;
    MSTATE       getState_e();
    void         setContext(MStateContext* context);
};

class IICMState
{
protected:
    ICMSTATE     state;
    unsigned int power;
    time_t       duration;

protected:
    virtual void ST_RUNNING(event_t e)           = 0;
    virtual void ST_POWER_SETTING(event_t e)     = 0;
    virtual void ST_TIME_DIAL_HANDLER(event_t e) = 0;

public:
    virtual ~IICMState() {}
};

class MStateContext
{
private:
    IMState* state;
    bool     doorOpen;
    bool     willDeleteMemoryHandler;
    bool     willDeleteDisplayHandler;

public:
    IMemoryHandler*  memoryHandler;
    IDisplayControl* displayHandler;

public:
    MStateContext(IMState*         state,
                  IMemoryHandler*  memoryHandler  = nullptr,
                  IDisplayControl* displayHandler = nullptr);
    ~MStateContext();
    MSTATE getState();
    void   setState(IMState* state);
    void   run(event_t e);
    bool   isDoorOpen();
};

#endif // ifndef __IMSTATE_H
