#ifndef TEST_TIMER_CLASS_H
#define TEST_TIMER_CLASS_H

#include "scene/main/timer.h"

#include "tests/test_macros.h"

namespace TestTimerClass{

TEST_CASE("[TimerTest] get and set wait time"){
    Timer *timer =memnew(Timer);
    timer->set_wait_time(1.0);
    //test that wait time won't be set to a negative number
    timer->set_wait_time(-1.0);
    CHECK(timer->get_wait_time() == doctest::Approx(1.0f));
    memdelete(timer);
}






}

#endif