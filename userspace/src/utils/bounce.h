#ifndef __BOUNCE_H

#define __BOUNCE_H

#include <time.h>

class Bouncer
{
private:
    time_t start_time;
    long   duration;
    bool   debouncing;

public:
    Bouncer();
    Bouncer(long duration);
    void update();
    void start(long duration);
    bool timeout();
};

#endif // ifndef __BOUNCE_H
