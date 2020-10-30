#ifndef __STUB_H

#define __STUB_H

#include "../src/hardware/display_abstraction.h"
#include "../src/hardware/memory_abstraction.h"
#include "../src/hardware/statusChecker_abstraction.h"

#include <gmock/gmock.h>

class StubDisplayControl : public IDisplayControl
{
public:
    MOCK_METHOD(void, display, (long value, DISPLAY_TYPE type), (override));
    MOCK_METHOD(void, displayOSTime, (), (override));
    MOCK_METHOD(void, setRadiator, (unsigned int value), (override));
    MOCK_METHOD(void, setOvenLED, (PIN_STATE state), (override));
    MOCK_METHOD(void, setMemoryLED, (PIN_STATE state), (override));
};


class StubMemoryHandler : public IMemoryHandler
{
public:
    MOCK_METHOD(time_t, getDuration, (), (override));
    MOCK_METHOD(int, getPower, (), (override));
    MOCK_METHOD(void, save, (unsigned int power, time_t duration), (override));
};

class StubStatusChecker : public IStatusChecker
{
public:
    MOCK_METHOD(int, getTimeDial, (), (override));
    MOCK_METHOD(int, getButtons, (), (override));
};

#endif // ifndef __STUB_H
