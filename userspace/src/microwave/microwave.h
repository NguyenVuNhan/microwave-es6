#ifndef __MICROWAVE_H

#define __MICROWAVE_H

#include "../event.h"
#include "../hardware/statusChecker_abstraction.h"
#include "../states/IMState.h"

class Microwave
{
    int             lastButtons;
    int             lastTimeDial;
    bool            willDeleteStatusChecker;
    IStatusChecker* status;
    MStateContext*  context;

public:
    Microwave(MStateContext* context, IStatusChecker* status = nullptr);
    ~Microwave();
    event_t eventHandler();
    void    run();
};

class LPCStatusChecker : public IStatusChecker
{
public:
    int getTimeDial();
    int getButtons();
};

#endif // ifndef __MICROWAVE_H
