#include "Timer.h"

Timer::Timer(int no) : timer_no(no) 
{
    timer_minutes = EEPROM.read(timer_no*2); 
    timer_seconds = EEPROM.read(timer_no*2 + 1); 
    current_minutes = timer_minutes; 
    current_seconds = timer_seconds; 
} 

Timer::~Timer() {} 

void Timer::stop() 
{
    // record the pause time 
    pause_time = millis(); 
    current_state = stopped; 

}

void Timer::start() 
{ 

    start_time = millis(); 
    //if starting from a stop 
    if (current_state == stopped) 
    {
       //adding to the pause cache 
        pause_cache += start_time - pause_time; 

        //updating the state 
        current_state = started;   
    }
    else //starting from reset
    { 
        //update the state 
        current_state =  started; 
    }
}

void Timer::update_current_time() 
{ 
    unsigned long end_time = start_time - pause_cache + timer_minutes*60*1000 + timer_seconds*1000; //end time in millis 
    unsigned long difference = (end_time - millis())/1000; 
    current_minutes = difference/60; 
    current_seconds = difference - current_minutes*60; 
}

void Timer::Toggle_start_stop() 
{ 
    if (current_state == started) 
    { 
        stop();
    }
    else 
    { 
        start();
    }
}

void Timer::save() 
{ 
    //saves the current minute and second settings 
    EEPROM.write(timer_no*2,current_minutes);
    EEPROM.write(timer_no*2 + 1,current_seconds); 

    timer_minutes = current_minutes; 
    timer_seconds = current_seconds; 
}


void Timer::restart() 
{
    pause_cache = 0;
    current_minutes = timer_minutes; 
    current_seconds = timer_seconds; 
    current_state = reset; 
}

void Timer::update() 
{  
    check_input();
    if (current_state == started) 
    { 
        update_current_time();  
    }
    
}

void Timer::update_cache(Input n_input)
{ 
    input_cache[1] = input_cache[0]; 
    input_cache[0] = n_input;
}

void Timer::check_input() 
{ 
    if (input_cache[0] == none)
    { 
        return;
    } 
    switch (current_state) 
    {
    case stopped: 
        stopped_input(); 
        break; 
    case started: 
        started_input(); 
        break; 
    case reset: 
        reset_input(); 
        break;
    case time_set: 
        time_set_input(); 
        break; 
    }

}

void Timer::stopped_input() 
{ 
    switch (input_cache[0]) 
    { 
        case A: 
            Toggle_start_stop(); 
            break; 
        case B: 
            restart(); 
            break; 
        case C_long: 
            restart(); 
            current_state = time_set; 
            break; 
    }
}

void Timer::started_input() 
{ 
    switch (input_cache[0])
    { 
        case A: 
            Toggle_start_stop(); 
            break; 
        case B: 
            //nothing for now cant restart while 
            break;
    }
}

void Timer::reset_input() 
{ 
    switch (input_cache[0]) 
    { 
        case A: 
            Toggle_start_stop(); 
            break; 
        case B: 
            //does nothing for now 
            break; 
        case C_long: 
            current_state = time_set; 
            break; 
    }
}

void Timer::time_set_input() 
{

    short* ad_no; 
    short* max_val;     
    if (current_setting == seconds) 
    { 
        short* ad_no = &current_seconds; 
        short* max_val = &max_seconds; 
    }
    
    if (current_setting == minutes)
    { 
        short* ad_no = &current_minutes;
        short* max_val = &max_minutes;  
    }

    
    switch (input_cache[0]) 
    { 
        case A: 
            *ad_no =  (*ad_no < *max_val) ? *ad_no + 1 : 0; 
            break;
        case A_long:
            *ad_no =  (*ad_no + 10 < *max_val) ? *ad_no + 10 : 0; 
             break; 
        case B: 
            *ad_no = (*ad_no > 0) ? *ad_no - 1: *max_val; 
            break; 
        case B_long: 
            *ad_no = (*ad_no - 10 > 0) ? *ad_no - 10 : *max_val; 
            break; 
        case C_long:
            //break out of the time set mode 
            if (current_setting == seconds) 
            { 
                current_setting = minutes; 
                break; 
            }
            save(); 
            restart(); 
            break; 
    }
}

int Timer::get_minutes() const
{
     return current_minutes; 
}

int Timer::get_seconds() const
{ 
    return current_seconds; 
}

void Timer::manual_save(int _minutes, int _seconds)
{ 
    EEPROM.write(timer_no*2,_minutes);
    EEPROM.write(timer_no*2 + 1,_seconds); 
}