#ifndef TO_ASCII_H
#define TO_ASCII_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <Magick++.h>
using namespace Magick;
#include "./Resizer.h"

class ToAscii
{
private:
    lionOptions options;
    Image image;
    lsize imageSize;
    LionResizer sizer;
    LionPixel*imageMatrix;
    list<Image> images;
    int s;

    /* data */
public:
    ToAscii(lionOptions);

    void buildImage();

    void printImage();

    void saveFile(const char* fileName);
    void filter(int);

};

#endif