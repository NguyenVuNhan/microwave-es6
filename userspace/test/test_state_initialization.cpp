#include "../src/states/IMState.h"
#include "../src/states/cooking.h"
#include "../src/states/idle.h"
#include "../src/states/init.h"
#include "../src/states/memorySetup.h"
#include "../src/states/timeSetup.h"
#include "stub.h"

#include <gtest/gtest.h>

TEST(StateInitialize, Init)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Init(), &memoryHandler);

    ASSERT_EQ(context.getState(), INIT);
}

TEST(StateInitialize, Idle)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new Idle(), &memoryHandler);

    ASSERT_EQ(context.getState(), IDLE_RUNNING);
}

TEST(StateInitialize, MemorySetup)
{
    StubMemoryHandler memoryHandler;
    MStateContext context = MStateContext(new MemorySetup(), &memoryHandler);

    ASSERT_EQ(context.getState(), MEMORY_SETUP_RUNNING);
}

TEST(StateInitialize, TimeSetup)
{
    StubMemoryHandler memoryHandler;
    MStateContext     context = MStateContext(new TimeSetup(), &memoryHandler);

    ASSERT_EQ(context.getState(), TIME_SETUP_HOUR);
}
