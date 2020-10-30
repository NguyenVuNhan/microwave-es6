#include "../src/microwave/microwave.h"
#include "../src/states/idle.h"
#include "../src/utils/utils.h"
#include "stub.h"

#include <gtest/gtest.h>

#include <iostream>

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

TEST(HelperFunction, TimeDialConvert)
{
    time_t durationValue[] = {
        1,    2,    3,    4,    5,    6,    7,    8,   9,   10, // range 1
        15,   20,   25,   30,   35,   40,   45,   50,  55,  60, // range 2
        75,   90,   105,  120,  135,  150,  165,  180, 195, 210,
        225,  240,                                // range 3
        300,  360,  420,  480,  540,  600,        // range 4
        720,  840,  960,  1080, 1200,             // range 5
        1500, 1800, 2100, 2400, 2700, 3000, 3300, // range 6
    };

    for (int i = 1; i <= 50; i++)
    {
        EXPECT_EQ(TimeDialConvert(i), durationValue[i - 1]);
    }

    EXPECT_GT(TimeDialConvert(55), 3300);
}

TEST(HelperFunction, TimeDialConvert_with_initTime)
{
    time_t durationValue[][2] = { { 9, 1 },    { 11, 5 },    { 61, 15 },
                                  { 238, 15 }, { 650, 120 }, { 9999, 300 } };

    for (auto duration : durationValue)
    {
        int timeDiff = TimeDialConvert(duration[0], 1) - duration[0];
        EXPECT_EQ(timeDiff, duration[1]);
    }

    EXPECT_GT(TimeDialConvert(55), 3300);
}

TEST(Microwave, EventHandler)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    StubStatusChecker  status;
    Microwave          microwave =
      Microwave(new MStateContext(new Idle(), &memoryHandler, &displayControl),
                &status);

    int evtExpects[][3] = {
        // btnState,	evt.sig	   evt.ret
        { 0b0000000000, TIME_DIAL_CHANGED, 58 }, // Door
        { 0b0000000000, NO_EVENT, 0 },           //
        { 0b1000000000, TIME_PRESSED, 0 },       // Time btn
        { 0b1000000000, NO_EVENT, 0 },           //
        { 0b0100000000, TIME_RELEASE, 0 },       //
        { 0b0100000000, STOP_PRESSED, 0 },       // Stop btn
        { 0b0100000000, NO_EVENT, 0 },           //
        { 0b0010000000, STOP_RELEASE, 0 },       //
        { 0b0010000000, START_PRESSED, 0 },      // Start btn
        { 0b0010000000, NO_EVENT, 0 },           //
        { 0b0001000000, START_RELEASE, 0 },      //
        { 0b0001000000, P_PRESSED, 90 },         // P90 btn
        { 0b0001000000, NO_EVENT, 0 },           //
        { 0b0000100000, P_RELEASE, 90 },         //
        { 0b0000100000, P_PRESSED, 180 },        // P180 btn
        { 0b0000100000, NO_EVENT, 0 },           //
        { 0b0000010000, P_RELEASE, 180 },        //
        { 0b0000010000, P_PRESSED, 360 },        // P360 btn
        { 0b0000010000, NO_EVENT, 0 },           //
        { 0b0000001000, P_RELEASE, 360 },        //
        { 0b0000001000, P_PRESSED, 600 },        // P600 btn
        { 0b0000001000, NO_EVENT, 0 },           //
        { 0b0000000100, P_RELEASE, 600 },        //
        { 0b0000000100, P_PRESSED, 900 },        // P900 btn
        { 0b0000000100, NO_EVENT, 0 },           //
        { 0b0000000010, P_RELEASE, 900 },        //
        { 0b0000000010, DOOR_OPEN, 0 },          // Door
        { 0b0000000010, NO_EVENT, 0 },           //
        { 0b0000000001, DOOR_CLOSE, 0 },         //
        { 0b0000000001, M_PRESSED, 0 },          // Memory btn
        { 0b0000000001, NO_EVENT, 0 },           //
        { 0b0000000000, M_RELEASE, 0 },          //
    };
    int nr_of_test_case = sizeof(evtExpects) / sizeof(evtExpects[0]);

    for (int i = 0; i < nr_of_test_case; i++)
    {
        EXPECT_CALL(status, getButtons()).WillOnce(Return(evtExpects[i][0]));
        EXPECT_CALL(status, getTimeDial()).WillOnce(Return(1200));

        event_t evt = microwave.eventHandler();

        EXPECT_EQ(evt.sig, evtExpects[i][1]);
        EXPECT_EQ(evt.ret, evtExpects[i][2]);
    }
}

TEST(Microwave, Run)
{
    StubMemoryHandler  memoryHandler;
    StubDisplayControl displayControl;
    StubStatusChecker  status;
    MStateContext*     context =
      new MStateContext(new Idle(), &memoryHandler, &displayControl);
    Microwave microwave = Microwave(context, &status);

    EXPECT_CALL(status, getButtons()).WillOnce(Return(0b0000010000));
    EXPECT_CALL(status, getTimeDial()).WillOnce(Return(1200));
    EXPECT_CALL(displayControl, display(_, TIME)).Times(AtLeast(1));
    microwave.run();
}
