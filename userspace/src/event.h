#ifndef __EVENT_H

#define __EVENT_H

enum EVENT
{
    NO_EVENT,
    P_RELEASE,
    P_PRESSED,
    M_RELEASE,
    M_PRESSED,
    START_RELEASE,
    START_PRESSED,
    STOP_RELEASE,
    STOP_PRESSED,
    TIME_RELEASE,
    TIME_PRESSED,
    TIME_DIAL_CHANGED,
    DOOR_CLOSE,
    DOOR_OPEN,
    TICK
};

struct event_t
{
    enum EVENT sig;
    int        ret;
};

#endif // ifndef __EVENT_H
