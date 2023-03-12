#pragma once 
#include <Arduino.h>
#include <vector>

//timing sequence with for fun blinking and oscilating fun 
class Sequence
{ 
    public: 
    /// @brief setups a sequencer that will return a bool called with update()
    /// @param ts a timestate vector 
    /// @param pt 
    /// @param rc 
    Sequence(std::vector<TimeState> ts = {TimeState{250,1},TimeState{250,0}}, unsigned long pt = 250, unsigned long rc = 10000) : 
    time_state(ts), 
    ts_on(false),
    repeat_start_time(0),
    current_position(0),
    pulse_length(pt),
    repeat_cutoff(rc) {}

    void Repeat_on() 
    { 
        current_position = 0; 
        ts_on = true; 
        interval_time = 0; 
        repeat_start_time = millis(); 

    }

    bool Update() 
    { 
        
    }

    void Pulse() 
    { 
        pulse_on = true; 
    }
    
    private: 

    //repeating pattern stuff 
    std::vector<TimeState> time_state; 
    int current_position; 
    unsigned long repeat_start_time; 
    unsigned long interval_time = 0; 
    bool ts_on; 

    unsigned long repeat_cutoff; 

    //short pulse stuff (overrides the repeat) 
    unsigned long pulse_length; 
    bool pulse_on; 


};

struct TimeState
{ 
    unsigned long Time; 
    bool state; 
};