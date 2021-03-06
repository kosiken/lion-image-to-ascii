#ifndef LION_UTILS_H
#define LION_UTILS_H
# define PACKAGE_VERSION "1.0.1" 
#include <list>

#include <string>
#include "Pixel.h"

using std::cout;
using std::endl;
using std::list;
using std::string;
// object to hold the size and width of an object
struct lsize
{

    float width;
    float height = 1.0;
};

// object to hold pixel data
struct lionPixelStruct
{
    float a = 1.0;
    int r;
    int g;
    int b;
};

// hold command line options
struct lionOptions
{
    string fileName;
    string resize;
    string winsize;
    string saveFile;
    list<string> errors;
    int filter = 0;
    string ascii;
};

string usage();
// converts the resize option WidthxHeight to an int pointer containing [Width, Height]
int *parseResizeOption(string dimen);

// parses the command line arguments to create options
lionOptions parseOptions(int argc, char **argv);

// edit transperent pixels
LionPixel pixelBg(LionPixel, lionPixelStruct &);

// Converts a matrix of pixels to ASCII characters and prints to the console if print is true
string pixelMatrixToAscii(LionPixel  *pixelMatrix, int height, int width, string asci, bool print);

// Converts a pixel to an ascii character
char asciify(LionPixel &, string &);

#endif