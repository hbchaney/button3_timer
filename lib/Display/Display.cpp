#include "Display.h"

Display::Display(int w ,int  h, TwoWire *twi) : 
                Adafruit_SH1107(w, h, twi) {} 

//overloads 
void Display::str_print(const std::string& in_str)
{ 
    Adafruit_SH1107::print(in_str.c_str()); 
}