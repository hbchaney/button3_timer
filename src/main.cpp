#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <string>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "Timer.h"
#include "Display.h"
#include "button.h"
#include "three_button_manager.h"
#include "TimerDisplay.hpp"
#include "TimerManager.hpp"

Display feather_display;
ThreeButtonManager input_manager{9,8,7,650}; 
TimerManager time_manager{&feather_display}; 
Input answer; 

void setup() 
{ 
    Serial.begin(115200); 
    delay(250); 
    feather_display.begin(0x3C,true);
    feather_display.setRotation(1);

    feather_display.setTextSize(2); 
    feather_display.setCursor(0,0);
    feather_display.setTextColor(SH110X_WHITE);

    input_manager.Setup(); 

    feather_display.clearDisplay(); 

}

void loop() 
{ 
    feather_display.clearDisplay(); 
    answer = input_manager.Update(); 
    time_manager.Update(answer); 

    if (answer == B_long)
    { 
        Serial.println("B_long pressed"); 
    }

    feather_display.display(); 
}

// unsigned long last_pulse_on = 0;
// unsigned long last_pulse_off = 0;  
// unsigned long pulse_length = 200; 
// unsigned long off_length = 500; 
// bool on = false; 

// //Buzzer quick test 
// void setup() 
// { 
//     pinMode(0,OUTPUT);
//     pinMode(6,OUTPUT); 
//     digitalWrite(6,0); 
//     digitalWrite(0,0); 
// }

// void loop() 
// { 
//     digitalWrite(0,HIGH); 
//     sleep_ms(pulse_length); 
//     digitalWrite(0,LOW); 
//     sleep_ms(pulse_length);
//     digitalWrite(0,HIGH); 
     
// }

