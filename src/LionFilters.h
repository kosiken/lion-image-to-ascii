#ifndef LION_FILTERS_H_
#define LION_FILTERS_H_

#include "Pixel.h"

// A simple class to  add simple filters to the output
class LionFilters
{


public:
        enum filters
    {
        FilterOne,
        FilterTwo,
        FilterThree
    };

    static void filter(LionPixel &lionPixel, int);

    //This would filter the picture by increasing all the pixels red value to 255
    static void filterOne(LionPixel &pixel);

    //This would filter the picture by increasing all the pixels green value to 255
    static void filterTwo(LionPixel &pixel);

    //This would filter the picture by increasing all the pixels blue value to 255
    static void filterThree(LionPixel &pixel);
    
};

#endif