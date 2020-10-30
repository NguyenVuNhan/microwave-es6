#ifndef __MEMORY_HANDLER_H

#define __MEMORY_HANDLER_H

#include "../hardware/memory_abstraction.h"

class LPCMemoryHandler : public IMemoryHandler
{
public:
    LPCMemoryHandler();
    time_t getDuration();
    int    getPower();
    void   save(unsigned int power, time_t duration);
};

#endif // ifndef __MEMORY_HANDLER_H
