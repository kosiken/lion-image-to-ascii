#include <sys/ioctl.h>
#include <unistd.h>

#include "./Resizer.h"

LionResizer::LionResizer(int width, int height, double scalel)
{
    picSize.width = width;
    picSize.height = height;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    window_size.width = w.ws_col;
    window_size.height = w.ws_row;

    // when displaying images on the console we have to compromize for line height by doubling the
    // width of the image
    pixel_size.width = 2;
    pixel_size.height = 1;
    scale = scalel;
}
LionResizer::LionResizer(int width, int height, double scalel, lsize win)
{
    picSize.width = width;

    picSize.height = height;
    
    window_size.width = win.width;
    
    window_size.height = win.height;
    
    pixel_size.width = 2;
    
    pixel_size.height = 1;
    
    scale = scalel;
};
lsize LionResizer::computeSize(bool console = true)
{
    lsize wantedSize;

    wantedSize.height = window_size.height;
    wantedSize.width = -1;

    resizeByAspectRatio(wantedSize, picSize);

    int rW = wantedSize.width / pixel_size.width,
        rH = wantedSize.height / pixel_size.height,
        sW = window_size.width, sH = window_size.height;

    constrainToWindow(rW, rH, wantedSize);

    wantedSize.width = (int)(wantedSize.width * (console ? pixel_size.width : 1));
    wantedSize.height = (int)(wantedSize.height);

    return wantedSize;
};

lsize LionResizer::computeSize(lsize &wantedSizeP, bool console = true)
{
    lsize wantedSize = wantedSizeP;

    resizeByAspectRatio(wantedSize, picSize);

    int rW = wantedSize.width / pixel_size.width,
        rH = wantedSize.height / pixel_size.height,
        sW = window_size.width, sH = window_size.height;

    constrainToWindow(rW, rH, wantedSize);

    wantedSize.width = (int)(wantedSize.width * scale * (console ? pixel_size.width : 1));
    wantedSize.height = (int)(wantedSize.height * scale * pixel_size.height);

    return wantedSize;
}

void LionResizer::resizeByAspectRatio(lsize &resultObj, lsize realSize)
{

    if (resultObj.width < 0)
    {
        resultObj.width = realSize.width * resultObj.height / realSize.height;
    }
    else if (resultObj.height < 0 || resultObj.height / pixel_size.height > window_size.height || resultObj.height / resultObj.width != realSize.height / realSize.width)
    {
        resultObj.height = realSize.height * resultObj.width / realSize.width;
    }
}

void LionResizer::constrainToWindow(int rW, int rH, lsize &wantedSize)
{
    // we want to make sure the width of the printed image never exceeds the console width
    if ((rW > window_size.width))
    {
        wantedSize.width = window_size.width;
        resizeByAspectRatio(wantedSize, picSize);
    }
    // we want to make sure the width of the printed image never exceeds the console width
    if (rH > 10000)
    {
        wantedSize.height = window_size.height;
    }
}
