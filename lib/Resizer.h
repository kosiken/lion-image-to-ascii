
#ifndef LION_RESIZER_H
#define LION_RESIZER_H
#include "./LionUtils.h"

#define LION_UTILS_H
// utility class to resize the images to fit resize input or console window
class LionResizer
{

public:
    lsize pixel_size;
    lsize window_size;
    lsize picSize;
    double scale;

public:
    LionResizer()
    {
    }
    LionResizer(int width, int height, double scale);
    LionResizer(int width, int height, double scale, lsize);
    // resize image with respect to aspect ratio
    void resizeByAspectRatio(lsize &, lsize);

    //  compute size to be used to display image
    lsize computeSize(bool console);

    //  compute size to be used to display image from given size options
    lsize computeSize(lsize &, bool);

    void constrainToWindow(int, int, lsize &);
};

#endif