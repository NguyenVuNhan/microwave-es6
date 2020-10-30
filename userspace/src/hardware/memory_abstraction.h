#ifndef __MEMORY_ABSTRACTION_H

#define __MEMORY_ABSTRACTION_H

#include <time.h>

class IMemoryHandler
{
protected:
    time_t       duration;
    unsigned int power;

public:
    virtual ~IMemoryHandler() {}
    virtual time_t getDuration()                             = 0;
    virtual int    getPower()                                = 0;
    virtual void   save(unsigned int power, time_t duration) = 0;
};

#endif // ifndef __MEMORY_ABSTRACTION_H
