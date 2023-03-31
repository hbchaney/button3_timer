#pragma once

#include "Adafruit_SH110X.h"
#include <string>

class Display : public Adafruit_SH1107
{ 
    public: 
    Display(int w = 64,int  h = 128, TwoWire *twi = &Wire1); 


    void str_print(const std::string&); 
    private: 

};