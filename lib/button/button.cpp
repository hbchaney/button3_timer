#include "button.h" 
#include "Timer.h"
#include <Arduino.h>


Button::Button(int in_pin_no, unsigned long in_press_length) :
        pin_no{in_pin_no}, 
        press_length{in_press_length},
        press_start{0} 
        {} 

// Button::Button(int in_pin_no, unsigned long in_press_length, Buzzer* in_buzz) :
//         pin_no{in_pin_no}, 
//         press_length{in_press_length},
//         press_start{0},
//         buzz{in_buzz} {} 

void Button::Setup() 
{
    pinMode(pin_no,INPUT_PULLUP); 
}

void Button::update_filter() 
{ 
    //does not report changes that are shorter than the buffer length 
    buffered_press = digitalRead(pin_no); 
    if (buffered_press == filtered_press)
    { 
        buffer_start = false; 
        return; 
    }
    else if (buffering)
    {
        if (buffer_start + buffer_length < millis()) 
        { 
            filtered_press = buffered_press; 
        }
    }
    else 
    { 
        buffer_start = millis(); 
        buffer_start = true; 
        return; 
    }

}

void Button::Update() 
{ 
    if (last_press + delay_length > millis())
    { 
        return; 
    }
    //update the filtered input 
    update_filter(); 
    //button not pressed down or button pressed to soon
    if (filtered_press == HIGH)
    {   
        if (last_state == true) 
        { 
            if (!long_trigger)
            { 
                output_cache = Short; 
            }
        }
        last_state = false; 
        return; 
    }

    //button pressed down 
    if (last_state) 
    { 
        //long trigger already off
        if (press_start + press_length < millis())
        { 
            output_cache = Long; 
            long_trigger = true; 
            press_start = millis(); 
            return; 
        }
        
    }
    else
    { 
        last_state = true; 
        long_trigger = false; 
        press_start = millis();
        last_press = millis(); 
        return; 
    }
}

press_type Button::get_output_cache() 
{ 
    press_type temp = output_cache; 
    output_cache = None; 
    return temp; 
}
