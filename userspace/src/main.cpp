#include "displayControl/displayControl.h"
#include "microwave/microwave.h"
#include "states/idle.h"
#include "utils/logging.h"

#include <time.h>

#include <iostream>

using namespace std;
using namespace logging;

int main()
{
    LOG_TYPE(CONSOLE);
    LOG_LEVEL(LOG_LEVEL_TRACE);

    Microwave microwave = Microwave(new MStateContext(new Idle()));
    while (1)
    {
         microwave.run();
    }
    return 0;
}
