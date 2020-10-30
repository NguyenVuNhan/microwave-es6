#include "bounce.h"

#include <iostream>

Bouncer::Bouncer()
{
    this->start_time = time(NULL);
    this->debouncing = false;
}

Bouncer::Bouncer(long duration)
{
    this->start(duration);
}

void Bouncer::update()
{
    time_t now = time(NULL);

    if (now - this->start_time >= this->duration)
    {
        debouncing = false;
    }
}

void Bouncer::start(long duration)
{
    this->start_time = time(NULL);
    this->duration   = (time_t) duration;
    this->debouncing = this->duration > 0 ? true : false;
}

bool Bouncer::timeout()
{
    return !this->debouncing;
}
