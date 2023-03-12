#pragma once 
// #include "Buzzer.h"

enum press_type 
{ 
    Long, 
    Short,
    None
};

class Button 
{ 
    public: 

    Button(int,unsigned long); 
    //Button(int,unsigned long, Buzzer*); 

    void Setup(); 
    void Update();
    press_type get_output_cache(); 

    private: 

    void update_filter(); 
    int filtered_press = 0; 
    int buffered_press = 0; 
    bool buffering = true; 
    unsigned long buffer_length = 50; 
    unsigned long buffer_start = 0; 
    
    int pin_no; 
    unsigned long press_start; 
    unsigned long press_length; 

    bool last_state = false; //true when pressed down
    bool long_trigger = false; 
    unsigned long delay_length = 100; //delay between possible press inputs
    unsigned long last_press = 0; 
    // Buzzer* buzz = nullptr; 

    press_type output_cache = None;

};
