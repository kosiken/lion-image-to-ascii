#include <iostream>
#include <vector>
#include <string>
#include <Magick++.h>
#include "LionFilters.h"
#include <chrono>
#include <thread>
using namespace Magick;

#include "ToAScii.h"

using namespace std;

using namespace std::this_thread;
using namespace std::chrono;
ToAscii::ToAscii(lionOptions opt)
{
    options = opt;

    try
    {
        image.read(options.fileName);
        if (image.format() == "CompuServe graphics interchange format")
        {
            readImages(&images, options.fileName);
            while (1)
            {
                for (list<Image>::iterator it = images.begin(); it != images.end(); it++)
                {
                    image = *it;
                    buildImage();
                    printImage();

                    sleep_for(milliseconds(50));

                    //cout<<"\033[2J";
                    cout << "\033[0;0G";
                }
            }
        }
        else
            buildImage();
    }

    catch (ErrorBlob err)
    {
        cout << "\x1b[38;2;255;0;0m"
             << "no such image -> "
             << "'" << options.fileName
             << "'" << endl;
    }
};

void ToAscii::buildImage()
{
    LionResizer rsizer(image.size().width(), image.size().height(), 1.0);
    sizer = rsizer;
    if (options.resize.length() > 0)
    {
        // pointer holding the dimensions of the resize option
        int *resize = parseResizeOption(options.resize);
        imageSize.width = *resize;
        imageSize.height = *(resize + 1);

        imageSize = sizer.computeSize(imageSize, true);
    }
    else
    {
        imageSize = sizer.computeSize(true);
    }

    int W = imageSize.width;
    int H = imageSize.height;
    string width = to_string(W), heigth = to_string(H);

    // force image magick to force image resize
    string dimen = width + "x" + heigth + '!';

    Geometry geom(dimen.c_str());

    image.resize(geom);

    // Set the image type to TrueColor DirectClass representation.
    image.type(TrueColorType);
    s = imageSize.width * imageSize.height;
    imageMatrix = new LionPixel[s];

    // used to keep track of where we are in the image
    int currentIndex = 0;
    for (int i = 0; i < H; i++)
    {
        for (int w = 0; w < W; w++)
        {
            // for some reason image.getPixels() returns a Quantum that
            // we cannot access to get pixel data so we resort to use
            // the Color class
            const Color pixel_sample = image.pixelColor(w, i);
            ColorRGB color(pixel_sample);
            ;
            int r = (int)(color.red() * 255);
            int g = (int)(color.green() * 255);
            int b = (int)(color.blue() * 255);

            double a = color.alpha();

            LionPixel pixel(r, g, b, a);

            *(imageMatrix + currentIndex) = pixel;
            //  cout<<imageMatrix[currentIndex]<<endl;
            currentIndex++;
        }
    }
    if (options.filter > 0)
    {
        switch (options.filter)
        {
        case 1:
            filter(LionFilters::FilterOne);
            break;
        case 2:
            filter(LionFilters::FilterTwo);
            break;

        default:
            filter(LionFilters::FilterThree);
            break;
        }
    }
}

void ToAscii::printImage()
{

    const int H = imageSize.height;
    const int W = imageSize.width;
    string ascii = ".,:;i1tfLCG08@", ans;
    // make sure that any user defined ascii string's length is
    // up to 5
    if (options.ascii.length() > 5)
    {

        ascii = options.ascii;
    }
    ans = pixelMatrixToAscii(imageMatrix, H, W, ascii, true);
}
void ToAscii::saveFile(const char *fileName)
{

    const int H = imageSize.height;
    const int W = imageSize.width;
    string ascii = ".,:;i1tfLCG08@", ans;
    // make sure that any user defined ascii string's length is
    // up to 5
    if (options.ascii.length() > 5)
    {

        ascii = options.ascii;
    }
    ans = pixelMatrixToAscii(imageMatrix, H, W, ascii, false);

    FILE *mfile = fopen(fileName, "w");
    fprintf(mfile, ans.c_str());

    cout << "done" << endl;
};

void ToAscii::filter(int filterType)
{

    for (int i = 0; i < s; i++)
    {
        LionFilters::filter(imageMatrix[i], filterType);
    }
}
