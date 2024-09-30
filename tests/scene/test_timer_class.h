#ifndef TEST_TIMER_CLASS_H
#define TEST_TIMER_CLASS_H

#include "scene/main/timer.h"
#include "scene/gui/tree.h"

#include "tests/test_macros.h"

namespace TestTimerClass{

TEST_CASE("[TimerClass] Check Wait Time Setters and Getters"){
    Timer *timer =memnew(Timer);
    
    //check default time
    CHECK(timer->get_wait_time() == doctest::Approx(1.0f));

    //test that wait time won't be set to a negative number
    timer->set_wait_time(-1.0);
    CHECK(timer->get_wait_time() == doctest::Approx(1.0f));

    //test that wait time can be set to a large number
    timer->set_wait_time(10000.0);
    CHECK(timer->get_wait_time() == doctest::Approx(10000.0f));
    memdelete(timer);
}

TEST_CASE("[TimerClass] Check One Shot Setters and Getters"){
    Timer *timer =memnew(Timer);

    //test default
    CHECK(timer->is_one_shot() == false);
    //test that one_shot can be set

    timer->set_one_shot(true);
    CHECK(timer->is_one_shot() == true);
    timer->set_one_shot(false);
    CHECK(timer->is_one_shot() == false);
    memdelete(timer);
}

TEST_CASE("[TimerCLass] Check Auto Start Setters and Getters"){
    Timer *timer =memnew(Timer);

    //test default
    CHECK(timer->has_autostart() == false);

    //test that auto start can be set
    timer->set_autostart(true);
    CHECK(timer->has_autostart() == true);
    timer->set_autostart(false);
    CHECK(timer->has_autostart() == false);

    //check that autostart is set to false after timer enters scene
    SceneTree::get_singleton()->get_root()->add_child(timer);
    CHECK(timer->has_autostart() == false);
    memdelete(timer);
}

TEST_CASE("[SceneTree] [TimerClass] Check Start and Stop of Timer "){
    Timer *timer =memnew(Timer);
    SceneTree::get_singleton()->get_root()->add_child(timer);

    //test start while timer is added to scene
    timer->start(3.0);
    CHECK(timer->get_wait_time() == doctest::Approx(3.0f));

    //test stop
    timer->stop();
    CHECK(timer->is_stopped() == true);
    timer->start(3.0);
    CHECK(timer->is_stopped() == false);
    timer->stop();

    //test get_time_left
    timer->start(3.0);
    CHECK(timer->get_time_left() <= doctest::Approx(3.0f));

    //test pause
    timer->set_paused(true);
    CHECK(timer->is_paused() == true);
    timer->set_paused(false);
    CHECK(timer->is_paused() == false);
    memdelete(timer);

}

TEST_CASE("[TimerClass] Test TimerProcessCallback"){
    Timer *timer =memnew(Timer);

    //check default
    CHECK(timer->get_timer_process_callback() == Timer::TimerProcessCallback::TIMER_PROCESS_IDLE);

    //check setter and getter
    timer->set_timer_process_callback(Timer::TimerProcessCallback::TIMER_PROCESS_PHYSICS);
    CHECK(timer->get_timer_process_callback() == Timer::TimerProcessCallback::TIMER_PROCESS_PHYSICS);
    memdelete(timer);
}
}

#endif