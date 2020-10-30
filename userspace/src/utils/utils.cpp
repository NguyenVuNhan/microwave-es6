#include "utils.h"

time_t TimeDialConvert(int step)
{
    return TimeDialConvert(0, step);
}

time_t TimeDialConvert(time_t initTime, int step)
{
    for (int i = 0; i < step; i++)
    {
        if (initTime < 10)
        {
            initTime += 1;
        }
        else if (10 <= initTime && initTime < 60)
        {
            initTime += 5;
        }
        else if (60 <= initTime && initTime < 240)
        {
            initTime += 15;
        }
        else if (240 <= initTime && initTime < 600)
        {
            initTime += 60;
        }
        else if (600 <= initTime && initTime < 1200)
        {
            initTime += 120;
        }
        else if (1200 <= initTime)
        {
            initTime += 300;
        }
    }
    return initTime;
}
