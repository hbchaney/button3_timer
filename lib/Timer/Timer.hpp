#pragma once 


class Timer 
{ 

    private: 

    int current_minutes; 
    int current_seconds;
    int timer_minutes; 
    int timer_seconds;  
    bool start = false; 

    unsigned long pause_time;
    unsigned long start_time; 
    unsigned long start_time; 

    //private functions
    void start(); 
    void stop(); 

    public: 
    Timer(); 
    ~Timer(); 

    //public functions 
    //basic utilities

    void Toggle_start_stop(); 
    void restart(); 
    void save(); 

    //time setting functions

    void increase(); 
    void decrease(); 

    int get_minutes(); 
    


};