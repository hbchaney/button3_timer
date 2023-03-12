#include "Display.h"

Display::Display(int w ,int  h, TwoWire *twi) : 
                Adafruit_SH1107(w, h, twi) {} 

void Display::Update() 
{ 

}