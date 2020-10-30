#include "../src/event.h"
#include "../src/states/IMState.h"
#include "../src/states/cooking.h"
#include "../src/states/idle.h"
#include "../src/states/init.h"
#include "../src/states/memorySetup.h"
#include "../src/states/timeSetup.h"
#include "stub.h"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace std::chrono;
using namespace testing;
using ::testing::_;
using testing::AllOf;
using ::testing::AtLeast;
using ::testing::Ge;
using ::testing::Return;

TEST(StateTransition_Init, Init__to__Idle)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Init(), &memoryHandler);

    event_t event = { NO_EVENT, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), IDLE_RUNNING);
}

TEST(StateTransition_Idle, Idle__to__Init)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Idle(), &memoryHandler);

    event_t event = { STOP_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), INIT);
}

TEST(StateTransition_Idle, Idle__to__MemorySetup)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Idle(), &memoryHandler);

    event_t event = { M_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), MEMORY_SETUP_RUNNING);
}

TEST(StateTransition_Idle, Idle__to__Cooking)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Idle(), &memoryHandler);

    EXPECT_CALL(memoryHandler, getPower()).Times(1).WillOnce(Return(300));
    EXPECT_CALL(memoryHandler, getDuration()).Times(1).WillOnce(Return(30));

    event_t event = { START_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), COOKING_RUNNING);
}

TEST(StateTransition_Idle, Idle__to__TimeSetup)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Idle(), &memoryHandler);

    event_t event = { TIME_PRESSED, 0 };
    context.run(event);
    auto start = high_resolution_clock::now();
    event      = { NO_EVENT, 0 };
    while (context.getState() == TIME_BTN_DEBOUNCER ||
           context.getState() == IDLE_RUNNING)
    {
        context.run(event);
    }
    auto stop     = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    EXPECT_THAT(duration.count(), AllOf(Ge(1700), Le(2000)));
    ASSERT_EQ(context.getState(), TIME_SETUP_HOUR);
}

TEST(StateTransition_MemorySetup, MemorySetup__to__Init)
{
    StubMemoryHandler memoryHandler;
    MStateContext context = MStateContext(new MemorySetup(), &memoryHandler);

    event_t event = { STOP_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), INIT);
}

TEST(StateTransition_MemorySetup, MemorySetup__to__Idle)
{
    StubMemoryHandler memoryHandler;
    MStateContext context = MStateContext(new MemorySetup(), &memoryHandler);

    event_t event = { M_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), IDLE_RUNNING);
}

TEST(StateTransition_TimeSetup, TimeSetup__to__Init)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new TimeSetup(), &memoryHandler);

    event_t event = { STOP_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), INIT);
}

TEST(StateTransition_Cooking, Cooking__to__Init)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context =
      MStateContext(new Cooking(900, 3300), &memoryHandler);

    event_t event = { STOP_PRESSED, 0 };
    context.run(event);
    ASSERT_EQ(context.getState(), INIT);
}
