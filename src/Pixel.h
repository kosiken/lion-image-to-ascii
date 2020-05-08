
#ifndef LIONPIXEL_H
#define LIONPIXEL_H

#include <iostream>
#include <string>
#include <cstring>

/* A class that is used to get a simple representation of an
image pixel */
class LionPixel {

    private:
     char*css=new char[7];

    public:

        int r;
        int g;
        int b;
       double a = 1.0;
        double intensityV;
        char ch;

        LionPixel();
        LionPixel(int, int, int);
        LionPixel(int, int, int, double);
        
        // returns the intensity at which to generate ansi colors for the pixel
        double intensity();
        void updateCss(){
            std::strcpy(css,("rgb("+ std::to_string(r) +','+ std::to_string(g) +','+
             std::to_string(b)+')').c_str());
        };

        char*getCSS() {
            return css;
        }
       friend std::ostream & operator<<(std::ostream & os, const LionPixel & t);

};


#endif