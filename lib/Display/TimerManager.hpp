#pragma once 

#include "TimerDisplay.hpp"
#include "Display.h"
#include "Input.h"

class TimerManager 
{ 
    public: 
    TimerManager(Display* in_display) :
    timer_display0{in_display,0,&timer0},
    timer_display1{in_display,1,&timer1},
    timer_display2{in_display,2,&timer2}
    {
        timer_display_cycler.push_back(&timer_display0);
        timer_display_cycler.push_back(&timer_display1); 
        timer_display_cycler.push_back(&timer_display2); 

        timer_cycler.push_back(&timer0); 
        timer_cycler.push_back(&timer1); 
        timer_cycler.push_back(&timer2); 

        timer_display0.set_selected(); 
    }

    void Update(Input new_input)
    { 
        //switch the timer if B long is called while the timer is not being set 
        if (new_input == Input::B_long && timer_cycler[current_timer]->get_state() != state::time_set)
        { 
            switch_state(); 
        }
        else
        {
            timer_cycler[current_timer]->update_cache(new_input); 
        }

        for (auto timers : timer_cycler)
        { 
            timers->update(); 
        }
        for (auto disp : timer_display_cycler)
        { 
            disp->Update(); 
        }


    }

    private: 
    //state switch parameters
    int current_timer = 0; 

    //timers and display info
    TimerDisplay timer_display0;
    TimerDisplay timer_display1;
    TimerDisplay timer_display2;

    std::vector<TimerDisplay*> timer_display_cycler; 
    std::vector<Timer*> timer_cycler; 

    Timer timer0 {0}; 
    Timer timer1 {1}; 
    Timer timer2 {2}; 

    //utility functions 
    void switch_state() 
    { 
        timer_display_cycler[current_timer]->set_unselected(); 
        current_timer = (current_timer < 2) ? current_timer + 1 : 0; 
        timer_display_cycler[current_timer]->set_selected(); 
    }
};