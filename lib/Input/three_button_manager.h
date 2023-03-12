#pragma once
#include "Input.h"
#include "button.h"


class ThreeButtonManager 
{ 
    public: 

    ThreeButtonManager(int _button_pin1,
                       int _button_pin2,
                       int _button_pin3,
                       unsigned long _long_press); 

    void Setup(); 
    Input Update(); 

    private: 
    
    Button ButtonA; 
    Button ButtonB; 
    Button ButtonC; 
};