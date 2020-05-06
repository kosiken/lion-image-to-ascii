#include "LionFilters.h"

void LionFilters::filter(LionPixel &lionPixel, int type)
{

    switch (type)
    {
    case LionFilters::FilterOne:
        filterOne(lionPixel);
        /* code */
        break;
    case LionFilters::FilterTwo:
        filterTwo(lionPixel);
        /* code */
        break;
    case LionFilters::FilterThree:
        filterThree(lionPixel);
        /* code */
        break;

    default:
        break;
    }
}


void LionFilters::filterOne(LionPixel &pixel){
    pixel.r = 255;
};

void LionFilters::filterTwo(LionPixel &pixel){
    pixel.g = 255;
};

void LionFilters::filterThree(LionPixel &pixel){
    pixel.b = 255;
};
