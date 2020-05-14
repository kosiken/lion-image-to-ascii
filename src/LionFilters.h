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
    static void filterOne(LionPixel &pixel);
    static void filterTwo(LionPixel &pixel);
    static void filterThree(LionPixel &pixel);
    
};

#endif