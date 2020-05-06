#include <iostream>



#include "Pixel.h"

#define LION_DIV 256


LionPixel::LionPixel() {
    r = 0;
    g= 0;
    b = 0;
}


LionPixel::LionPixel(int red, int green, int blue) {
    r = red;
    g = green;
    b = blue;

}


LionPixel::LionPixel(int red, int green, int blue, double alpha) {
    r = red;
    g = green;
    b = blue;
    a= alpha;
   updateCss();
}

double LionPixel::intensity() {
    intensityV = (r + g + b) * a;

    return intensityV;
}


std::ostream & operator<<(std::ostream & os, const LionPixel & t){
     os << "[ r => " << t.r << ", g => " <<
     t.g << ", b => " << t.b << ", a => " << t.a << " ]";

     return os;
 };
