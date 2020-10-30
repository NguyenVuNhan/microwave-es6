#include "../src/states/cooking.h"
#include "stub.h"

#include <gtest/gtest.h>

#include <chrono>

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Ge;


TEST(CookingState, Running__to_PowerSetting)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Cooking(900, 2), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(900, NUMBER)).Times(AtLeast(1));

    event_t event = { P_PRESSED, 900 };
    context.run(event);
    ASSERT_EQ(context.getState(), COOKING_POWER_SETTING);
}

TEST(CookingState, Running__to_TimeDialHandler)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Cooking(900, 2), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(4, TIME)).Times(AtLeast(1));

    event_t event = { TIME_DIAL_CHANGED, 2 };
    context.run(event);
    ASSERT_EQ(context.getState(), COOKING_TIME_DIAL_HANDLER);
}

TEST(CookingState, Running)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    MStateContext      context =
      MStateContext(new Cooking(900, 2), &memoryHandler, &displayControl);

    EXPECT_CALL(displayControl, display(_, _)).Times(AtLeast(1));
    EXPECT_CALL(displayControl, setOvenLED(HIGH)).Times(AtLeast(1));
    EXPECT_CALL(displayControl, setRadiator(Ge((unsigned int) 0))).Times(10);

    event_t event = { NO_EVENT, 2 };
    for (int i = 0; i < 10; ++i)
    {
        context.run(event);
    }

    EXPECT_CALL(displayControl, setRadiator(0)).Times(10);

    event = { DOOR_OPEN, 2 };
    for (int i = 0; i < 10; ++i)
    {
        context.run(event);
    }
}
