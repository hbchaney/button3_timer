#pragma once 

#include <Arduino.h>
#include "Adafruit_SH110X.h"
#include "Timer.h"
#include "UtilityStructs.hpp"
#include "Display.h"

#include <map>
#include <string>

class TimerDisplay 
{ 
    public: 

    TimerDisplay(Display* in_display, int in_timer_no, Timer* in_timer) : 
    display_pointer{in_display},
    timer_no{in_timer_no},
    display_location{0,timer_no*21},
    timer_pointer{in_timer}
    {}

    void set_selected() 
    { 
        selected = true; 
    }

    void set_unselected()
    { 
        selected = false; 
    }

    void Update() 
    { 
        display_pointer->setCursor(display_location._x, display_location._y); 
        display_pointer->print(timer_pointer->get_minutes()); 
        display_pointer->print(':'); 
        display_pointer->print(timer_pointer->get_seconds()); 
        display_pointer->print("  "); 
        if(timer_pointer->get_state() == time_set)
        { 
            display_pointer->str_print(output_map.at(timer_pointer->get_state())); 
            if (timer_pointer->get_setting() == minutes)
            { 
                display_pointer->print("m"); 
            }
            else 
            { 
                display_pointer->print("s"); 
            }
        }
        else
        { 
            display_pointer->str_print(output_map.at(timer_pointer->get_state())); 
        }

        if (selected) 
        { 
            display_pointer->print("~"); 
        }
        
    }

    private: 
    Display* display_pointer; 
    Timer* timer_pointer; 
    int timer_no; 
    utilities::Coordinate<int> display_location; 
    bool selected = false; 

    const static std::map<state,std::string> output_map; 

};

const std::map<state,std::string> TimerDisplay::output_map = {
    {state::reset, ">"},
    {state::started, "="},
    {state::stopped, ">"},
    {state::time_set, ""}
};