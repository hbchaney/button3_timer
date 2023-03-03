#pragma once
#include "SoundSequence.hpp"

class Buzzer
{ 
    public: 
    Buzzer(); 
    ~Buzzer(); 

    void short_beep(); 
    void repeat_beep_on();
    void repeat_beep_off(); 

    void set_sequence(); 

    private: 

    bool repeated_beep; 
    bool noise_state;
    //pins 
    int pin_no;

};