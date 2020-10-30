#include "../states/init.h"
#include "../utils/logging.h"
#include "microwave.h"

#include <math.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

/* ret: "<TimeBtn> <StopBtn> <StartBtn> <90Btn> <180Btn> <360Btn> <600Btn>
 * <900Btn> <MemBtn>" */
#define M_PIN      9
#define DOOR_PIN   8
#define P900_PIN   7
#define P600_PIN   6
#define P360_PIN   5
#define P180_PIN   4
#define P90_PIN    3
#define START_PIN  2
#define STOP_PIN   1
#define T_PIN      0
#define GPIO_DEVFS "/dev/microwave_buttons"
#define ADC_DEVFS  "/dev/microwave_adc"

#define POTENTIOMETER_MAX    1023
#define POTENTIOMETER_MIN    0
#define NR_OF_DIFFERENT_TIME 50
#define TIME_CHANGE_THRESSHOLD \
    ((float) (POTENTIOMETER_MAX - POTENTIOMETER_MIN) / NR_OF_DIFFERENT_TIME)

using namespace logging;

std::string getData(std::string fn)
{
    std::string        line;
    std::ostringstream ss;
    std::ifstream      ifile(fn.c_str());
    if (ifile.is_open())
    {
        getline(ifile, line);
        ifile.close();
        // ss << line << std::endl << "fname: " << fn.c_str();
        // LOG_DEBUG(ss);
        return line;
    }
    else
    {
        LOG_ERROR("Unable to open file");
    }

    return "";
}

Microwave::Microwave(MStateContext* context, IStatusChecker* status)
{
    this->willDeleteStatusChecker = false;
    this->lastButtons             = 0;
    this->lastTimeDial            = POTENTIOMETER_MIN;
    this->context                 = context;
    this->status                  = status;

    if (status == nullptr)
    {
        this->status                  = new LPCStatusChecker();
        this->willDeleteStatusChecker = true;
    }
}

Microwave::~Microwave()
{
    /* if (this->willDeleteStatusChecker) */
    /*     delete this->status; */
    if (this->context != nullptr)
        delete this->context;
}

void Microwave::run()
{
    event_t evt;
    evt = eventHandler();
    this->context->run(evt);
}

event_t Microwave::eventHandler()
{
    event_t evt;
    evt.ret = 0;
    evt.sig = NO_EVENT;
    std::ostringstream ss;

    int buttons = this->status->getButtons();
    // ss << "buttons: " << buttons << '\n';

    int timeDial = this->status->getTimeDial();

    if (buttons != -1 && buttons != this->lastButtons)
    {
        // 0000000000
        // 0123456789
        // 
        int diff_pos      = log2(buttons ^ this->lastButtons);
        this->lastButtons = this->lastButtons ^ (1 << diff_pos);
        // ss << "diff_pos: " << diff_pos << std::endl;
        // ss << "button State: " << ((buttons >> diff_pos) & 1) <<  '\n';

        switch (9 - diff_pos)
        {
            case T_PIN:
                evt.sig = (EVENT)(TIME_RELEASE + ((buttons >> diff_pos) & 1));
                break;
            case STOP_PIN:
                evt.sig = (EVENT)(STOP_RELEASE + ((buttons >> diff_pos) & 1));
                break;
            case START_PIN:
                evt.sig = (EVENT)(START_RELEASE + ((buttons >> diff_pos) & 1));
                break;
            case P90_PIN:
                evt.sig = (EVENT)(P_RELEASE + ((buttons >> diff_pos) & 1));
                evt.ret = 90;
                break;
            case P180_PIN:
                evt.sig = (EVENT)(P_RELEASE + ((buttons >> diff_pos) & 1));
                evt.ret = 180;
                break;
            case P360_PIN:
                evt.sig = (EVENT)(P_RELEASE + ((buttons >> diff_pos) & 1));
                evt.ret = 360;
                break;
            case P600_PIN:
                evt.sig = (EVENT)(P_RELEASE + ((buttons >> diff_pos) & 1));
                evt.ret = 600;
                break;
            case P900_PIN:
                evt.sig = (EVENT)(P_RELEASE + ((buttons >> diff_pos) & 1));
                evt.ret = 900;
                break;
            case M_PIN:
                evt.sig = (EVENT)(M_RELEASE + ((buttons >> diff_pos) & 1)); 
                break;
            case DOOR_PIN:
                evt.sig = (EVENT)(DOOR_CLOSE + ((buttons >> diff_pos) & 1));
                break;
        }
    }

    int timeChangedSteps = (timeDial - this->lastTimeDial);
    timeChangedSteps /= TIME_CHANGE_THRESSHOLD;
    // ss << "Current time dial: " << timeDial << std::endl;
    // ss << "Last time dial:    " << this->lastTimeDial << std::endl;
    // ss << "Steps changed:     " << timeChangedSteps << std::endl;
    if (timeDial != -1 && abs(timeChangedSteps) > 0)
    {
        // ss << "timeChange: " << timeDial << std::endl;
        // ss << "stepChanged: " << timeChangedSteps << std::endl;
        evt.sig = TIME_DIAL_CHANGED;
        evt.ret = timeChangedSteps;
        this->lastTimeDial += timeChangedSteps * TIME_CHANGE_THRESSHOLD;
        // ss << evt.ret << std::endl;
    }

    LOG_DEBUG(ss);
    return evt;
}

int LPCStatusChecker::getButtons()
{
    std::string data = getData(GPIO_DEVFS);
    LOG_DEBUG(data);
    if (data == "")
        return -1;
    return atoi(data.c_str()) & 0x3FF;
}

int LPCStatusChecker::getTimeDial()
{
    std::string data = getData(ADC_DEVFS);
    if (data == "")
        return -1;
    return atoi(data.c_str());
}
