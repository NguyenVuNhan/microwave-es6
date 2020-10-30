#include "../src/states/IMState.h"
#include "../src/states/idle.h"
#include "stub.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace testing;
using ::testing::_;
using ::testing::AllOf;
using ::testing::AtLeast;
using ::testing::Ge;


TEST(IdleState, Running__to_PowerSetting)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Idle(), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, NUMBER)).Times(2);

    event_t event = { P_PRESSED, 900 };
    context.run(event);
    ASSERT_EQ(context.getState(), IDLE_POWER_SETTING);
}

TEST(IdleState, Running__to_TimeDialHandler)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Idle(), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, _)).Times(AtLeast(1));

    event_t event = { TIME_DIAL_CHANGED, 2 };
    context.run(event);
    ASSERT_EQ(context.getState(), IDLE_TIME_DIAL_HANDLER);
}

TEST(IdleState, PowerSetting__to__PowerSetting)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Idle(), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, _)).Times(AtLeast(1));

    event_t event = { P_PRESSED, 2 };
    context.run(event);
    ASSERT_EQ(context.getState(), IDLE_POWER_SETTING);
}

TEST(IdleState, PowerSetting__to__Running)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Idle(), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, _)).Times(AtLeast(1));
    EXPECT_CALL(displayControl, displayOSTime()).Times(AtLeast(1));

    event_t event = { P_PRESSED, 900 };
    context.run(event);
    EXPECT_EQ(context.getState(), IDLE_POWER_SETTING);

    auto start = high_resolution_clock::now();
    event      = { NO_EVENT, 900 };
    while (context.getState() == IDLE_POWER_SETTING)
    {
        context.run(event);
    }
    auto stop     = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    EXPECT_THAT(duration.count(), AllOf(Ge(1500), Le(2000)));
    ASSERT_EQ(context.getState(), IDLE_RUNNING);
}

TEST(IdleState, TimeDialHandler__to__TimeDialHandler)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Idle(), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, _)).Times(AtLeast(1));

    event_t event = { TIME_DIAL_CHANGED, 2 };
    context.run(event);
    ASSERT_EQ(context.getState(), IDLE_TIME_DIAL_HANDLER);
}

TEST(IdleState, TimeDialHandler__to__Running)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Idle(), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, _)).Times(AtLeast(1));
    EXPECT_CALL(displayControl, displayOSTime()).Times(AtLeast(1));

    event_t event = { TIME_DIAL_CHANGED, 900 };
    context.run(event);
    EXPECT_EQ(context.getState(), IDLE_TIME_DIAL_HANDLER);

    auto start = high_resolution_clock::now();
    event      = { NO_EVENT, 900 };
    while (context.getState() == IDLE_TIME_DIAL_HANDLER)
    {
        context.run(event);
    }
    auto stop     = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    EXPECT_THAT(duration.count(), AllOf(Ge(1500), Le(2000)));
    ASSERT_EQ(context.getState(), IDLE_RUNNING);
}
