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

Display feather_display;
std::string out_put {"60:23"};  
Input answer = none; 
Timer first_timer {0}; 

std::string going_out; 

ThreeButtonManager input_manager{9,8,7,650}; 

int current_time = 0; 
state status; 



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

    answer = input_manager.Update();
    first_timer.update_cache(answer); 
    first_timer.update(); 

    feather_display.clearDisplay(); 
    feather_display.setCursor(0,0); 
    feather_display.print(first_timer.get_minutes()); 
    feather_display.print(':'); 
    feather_display.print(first_timer.get_seconds()); 
    feather_display.println(); 

    status = first_timer.get_state(); 

    switch (status)
    {
        case stopped: 
            feather_display.println("stopped"); 
            break; 
        case started: 
            feather_display.println("started"); 
            break; 
        case reset: 
            feather_display.println("reset"); 
            break; 
        case time_set: 
            feather_display.println("timeset"); 
            if (first_timer.get_setting() == minutes)
            { 
                feather_display.print("M");
            }
            else 
            { 
                feather_display.print("S"); 
            }
            break; 
    }
    

    feather_display.display(); 
}