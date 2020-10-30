#include "startup.h"

#include <mach/hardware.h>
#include "../gpio/gpio_driver.h"
#include "../gpio/include/common.h"

#define DO_NOTHING 9999

const unsigned int btnSetup[][4] = {
        // { Mux, Dir, port, pin }
        // Port 0
        { DO_NOTHING, Output, 0, 0 },
        { DO_NOTHING, Output, 0, 1 },
        { DO_NOTHING, Output, 0, 2 },
        { DO_NOTHING, Output, 0, 3 },
        { DO_NOTHING, Output, 0, 4 },
        { DO_NOTHING, Output, 0, 5 },
        { DO_NOTHING, Output, 0, 6 },
        // Port 1
        { High, Output, 1, 15 },
        { High, Output, 1, 16 },
        { High, Output, 1, 17 },
        { High, Output, 1, 18 },
        { High, Output, 1, 19 },
        { High, Output, 1, 20 },
        { High, Output, 1, 21 },
        { High, Output, 1, 22 },
        // Port 2
        { High, DO_NOTHING, 2, 3},
        { DO_NOTHING, Input, 2, 0 },
        { DO_NOTHING, Input, 2, 1 },
        { DO_NOTHING, Input, 2, 2 },
        // Port 3
        { DO_NOTHING, Output, 3, 0 },
        { DO_NOTHING, Output, 3, 1 },
        { DO_NOTHING, Output, 3, 4 },
};

void lcdOff(void)
{
    char* lcdAddress1 = io_p2v(0x31040018);
    char* lcdAddress2 = io_p2v(0x40004054);
    *lcdAddress1 = 0;
    *lcdAddress2 = 0;
}

void initPins(void)
{
    int i;
    int n = sizeof(btnSetup) / sizeof(btnSetup[0]);
    for (i = 0; i < n; i++)
    {
        if (btnSetup[i][0] != DO_NOTHING)
        {
            setMux(btnSetup[i][2], btnSetup[i][3], btnSetup[i][0]);
        }
        if (btnSetup[i][1] != DO_NOTHING)
        {
            setDirection(btnSetup[i][2], btnSetup[i][3], btnSetup[i][1]);
        }
    }
}