#pragma once 
#include "Buzzer.h"


class Button 
{ 
    public: 

    Button(); 
    Button(Buzzer*); 
    ~Button(); 

    private: 

    int pin_no; 
    unsigned long press_start; 


};