#pragma once 
#include "Input.h"
#include <Arduino.h>
#include <EEPROM.h>

class Timer 
{ 

    private: 

    int timer_no; //dictates where data will be stored in flash for the times 

    short current_minutes; 
    short current_seconds;
    short timer_minutes; 
    short timer_seconds;  
    bool set_mode = true;

    Input input_cache[2] {none,none}; 

    enum state { 
        stopped, 
        started,
        reset,
        time_set,
    }; 

    state current_state = reset; 

    enum setting { 
        seconds, 
        minutes, 
    };

    setting current_setting = seconds; 

    short max_minutes = 60;
    short max_seconds = 60; 

    unsigned long pause_cache = 0; 
    unsigned long pause_time = 0;
    unsigned long start_time = 0; 

    //private functions
    void start(); 
    void stop(); 
    void save(); 
    
    void Toggle_start_stop(); 

    void update_current_time(); 

    void stopped_input(); 
    void started_input();
    void reset_input(); 
    void time_set_input(); 
    void check_input(); 

    public: 
    /// @brief Initializes Timer Object
    Timer(int no); 
    ~Timer(); 


    /// @brief toggles between the stop and start state also starts after setting the time 
    

    /// @brief  restarts the time
    void restart(); 

    //input processing params 
    void update_cache(Input); 
    
    

    // display grabbing info 
    int get_minutes() const; 
    int get_seconds() const; 

    void manual_save(int _minutes, int _seconds); 
    
    void update(); 

};