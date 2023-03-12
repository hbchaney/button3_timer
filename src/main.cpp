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

ThreeButtonManager input_manager{9,8,7,650}; 

int current_time = 0; 


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

    //button a 
    if (answer == A)
    { 
        current_time++; 
    }
    else if (answer == A_long) 
    { 
        current_time = current_time + 10;  
    }

    //button b 
    if (answer == B)
    {
        current_time = (current_time > 0) ? current_time -1 : 0; 
    }
    if (answer == B_long) 
    { 
        current_time = (current_time -10 > 0) ? current_time - 10 : 0; 
    }

    if (answer == C_long) 
    { 
        current_time = 0; 
    }
    feather_display.clearDisplay(); 
    feather_display.setCursor(0,0); 
    feather_display.print(current_time); 
    feather_display.display(); 
}