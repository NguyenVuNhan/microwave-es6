#include "../utils/logging.h"
#include "displayControl.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

//				.gfedcba
#define ZERO  0b01111110
#define ONE   0b00110000
#define TWO   0b01101101
#define THREE 0b01111001
#define FOUR  0b00110011
#define FIVE  0b01011011
#define SIX   0b01011111
#define SEVEN 0b01110000
#define EIGHT 0b01111111
#define NINE  0b01111011

#define MAX_DISPLAY_VALUE 9999
#define MAX_PWM_VALUE     1024
#define O_LED_PIN         0
#define M_LED_PIN         1
#define DISPLAY_DEVFS     "/dev/microwave_digit"
#define PWM_DEVFS         "/dev/microwave_pwm"
#define GPIO_DEVFS        "/dev/microwave_leds"

using namespace logging;

static const int digits[] = { ZERO, ONE, TWO,   THREE, FOUR,
                              FIVE, SIX, SEVEN, EIGHT, NINE };

static int valueToBinary(unsigned int value)
{
    if (value <= 9)
    {
        return digits[value];
    }
    else
    {
        return 0;
    }
}

static void displayNumber(long value)
{
    std::ostringstream ss;
    if (value <= MAX_DISPLAY_VALUE)
    {
        for (int i = 3; i >= 0; i--)
        {
            char          buffer[20];
            std::ofstream ofile(DISPLAY_DEVFS);
            sprintf(buffer, "%d %d ", i, valueToBinary(value % (10)));
            ofile << buffer;
            ss << buffer << std::endl;
            value /= 10;
            ofile.close();
        }
    }
    LOG_DEBUG(ss);
}

static void displayTime(time_t t)
{
    unsigned int value = ((long) t) % 10000;
    unsigned int time  = value % 60;
    value /= 60;
    time += 100 * value;

    displayNumber(time);
}

void LPCDisplayControl::display(long t, DISPLAY_TYPE type)
{
    switch (type)
    {
        case TIME:
            displayTime(t);
            break;
        case NUMBER:
            displayNumber(t);
            break;
    }
}

void LPCDisplayControl::displayOSTime()
{
    time_t       now   = time(NULL);
    tm*          gmnow = gmtime(&now);
    unsigned int value = gmnow->tm_hour * 100 + gmnow->tm_min;

    displayNumber(value);
}

void LPCDisplayControl::setRadiator(unsigned int value)
{
    std::ofstream ofile(PWM_DEVFS);
    if (value <= MAX_PWM_VALUE)
    {
        ofile << value << ' ';
    }
    ofile.close();
}

void LPCDisplayControl::setOvenLED(PIN_STATE state)
{
    std::ofstream ofile(GPIO_DEVFS);
    ofile << O_LED_PIN << ' ' << state << ' ';
    ofile.close();
}

void LPCDisplayControl::setMemoryLED(PIN_STATE state)
{
    std::ofstream ofile(GPIO_DEVFS);
    ofile << M_LED_PIN << ' ' << state << ' ';
    ofile.close();
}
