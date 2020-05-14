#include <list>
#include <getopt.h>
#include <string>
#include "Pixel.h"

#include "./LionUtils.h"

using namespace std;

string usage()
{

    string use = "\nlimagetoasci filepath [options] [option argument]\n"
                 "prints a given image as ascii characters to the console or saves it to\n\n"
                 "a file if the  `-s` option is provided\n\n OPTIONS\n\n"
                 "-r --resize  The dimensions to use in resizing the image, format -> WxH \n"
                 "\twhere W = width and H = height\n\n"
                 "-s --savefile Path to the file to save the JSON output in\n\n"
                 "-a --ascii The set of ascii characters to use. MUST BE MORE THAN 5 in length\n\n"
#ifdef PACKAGE_VERSION
                 "limgtoasci version: " PACKAGE_VERSION "\n\n"
#endif
                 "limgtoasci homepage: <https://github.com/kosiken/lion-image-to-ascii/>\n\n";
    return use;
}

int *parseResizeOption(string dimen)
{

    char *hs = new char[1], *ws = new char[1];
    int *ans = new int[2];

    int i = 0, len = dimen.length(), j = 0;
    while (dimen[i] != 'x')
    {
        *(ws + i) = dimen[i];

        i++;
    }

    i++;

    while (i < len)
    {
        *(hs + j) = dimen[i];

        i++;
        j++;
    }

    *ans = atoi(ws);

    return ans;
}

lionOptions parseOptions(int argc, char **argv)
{
    lionOptions args;
    struct option long_options[]{
        {"resize", required_argument, 0, 'r'},
        {"ascii", required_argument, 0, 'a'},
        {"savefile", required_argument, 0, 's'},
        {"filter", required_argument, 0, 'f'},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, '?'},
        {0, 0, 0, 0}};

    int c;
    int option_index;
    if (argc < 2)
    {
        cout << usage();
        exit(1);
    }
    args.fileName = *(argv + 1);

    while ((c = getopt_long(argc, argv, "r:a:s:f:v", long_options, &option_index)) != -1)
    {
        // cout<<optarg;
        switch (c)
        {

        case 's':
            args.saveFile = optarg;
            break;
        case 'r':
            args.resize = optarg;
            break;
        case 'a':
            args.ascii = optarg;
            break;
        case 'f':
            args.filter = atoi(optarg);
            break;
#ifdef PACKAGE_VERSION
        case 'v':
            cout << PACKAGE_VERSION << endl;
            exit(0);
#endif
        default:
            cout << usage();
            exit(1);
            break;
        }
    }

    return args;
}
LionPixel pixelBg(LionPixel pixel, lionPixelStruct &bgColor)
{
    if (pixel.a == 1)
    {
        return pixel;
    }

    float diff = 1 - pixel.a;

    pixel.r = (diff * bgColor.r) + pixel.a * pixel.r;
    pixel.g = (diff * bgColor.g) + pixel.a * pixel.g;
    pixel.b = (diff * bgColor.b) + pixel.a * pixel.b;
    pixel.a = 1;
    return pixel;
}

char asciify(LionPixel &pixel, string &ascii)
{

    lionPixelStruct bgWhite;
    bgWhite.r = 255;
    bgWhite.g = 255;
    ;

    bgWhite.b = 255;

    pixel = pixelBg(pixel, bgWhite);

    pixel.updateCss();
    int value = pixel.intensity();
    int precision = 255 * 3 / (ascii.length() - 1);
    char text = ascii[(int)(value / precision)];
    return text;
}

string pixelMatrixToAscii(LionPixel *pixelMatrix, int height, int width, string asci, bool print = false)
{
    string ret = "{\"pixels\":[";
    int currentIndex = 0, stop = (width * height) - 1;

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            LionPixel pixel = pixelMatrix[currentIndex];

            //   cout<<pixel<<endl;
            char ascii = asciify(pixel, asci);
            if (!print)
            {

                string reti = "{ \"colour\": \"";
                reti += pixel.getCSS();
                reti += "\" , \"ch\": \"";
                reti += ascii;
                reti += "\"}";
                if (currentIndex < stop)
                    reti += ',';
                ret += reti;

                // ret = ret + "{ \"colour\": \"" + pixel.getCSS() + "\" , \"ch\": \"" + ascii + "\"}";
                // if(i<((width*height)-1)) ret+=",";
            }

            if (print)
            {
                cout << "\x1b[38;2;" << pixel.r << ";"
                     << pixel.g << ";"
                     << pixel.b << "m" << ascii;
            }
            currentIndex++;
        }
        if (print)
            cout << endl;
    };
    ret += "]";
    ret += ", \"dimen\": ";
    ret += '"';
    ret += to_string(width) + "x" + to_string(height) + "\"}";

    return ret;
}