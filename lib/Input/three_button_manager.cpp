#include "three_button_manager.h"

ThreeButtonManager::ThreeButtonManager(int _button_pin1,
                                       int _button_pin2,
                                       int _button_pin3,
                                       unsigned long _long_press): 
                                       ButtonA{_button_pin1,_long_press},
                                       ButtonB{_button_pin2,_long_press},
                                       ButtonC{_button_pin3,_long_press} 
                                       {}
void ThreeButtonManager::Setup() 
{ 
    ButtonA.Setup(); 
    ButtonB.Setup();
    ButtonC.Setup(); 
}


Input ThreeButtonManager::Update() 
{ 
    ButtonA.Update(); 
    ButtonB.Update(); 
    ButtonC.Update(); 

    press_type pressA = ButtonA.get_output_cache();
    press_type pressB = ButtonB.get_output_cache(); 
    press_type pressC = ButtonC.get_output_cache(); 

    if (pressA != None) 
    { 
        if (pressA == Short)
        { 
            return A; 
        }
        else
        { 
            return A_long; 
        }
    } 
    else if (pressB != None) 
    { 
        if (pressB == Short) 
        { 
            return B;
        }
        else 
        {
             return B_long; 
        }
    }
    else if (pressC != None) 
    {
        if (pressC == Short) 
        { 
            return C; 
        }
        else
        {
             return C_long; 
        }
    }
    else 
    {
        return none; 
    }
    
}