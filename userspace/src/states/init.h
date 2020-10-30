#ifndef __INIT_H

#define __INIT_H

#include "IMState.h"

class Init : public IMState
{
public:
    Init();
    void run(event_t e);
};

#endif // ifndef __INIT_H
