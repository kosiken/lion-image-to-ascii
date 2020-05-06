#include <list>

#include <string>
#include "Pixel.h"

#include "./LionUtils.h"

using namespace std;

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
    lionOptions options;

    char **arg = &argv[1];
    if (argc > 1)
    {
        options.fileName = *arg;
        if (argc > 2)
        {
            string opt2 = *(arg + 1);
            bool error = true;

            if (opt2 != string("-f") && opt2 != string("-r") && opt2 != string("-a") && opt2 != string("-w"))
            {
                options.errors.push_back("invalid argument " + opt2);
                return options;
            }
            if (argc > 3)
            {
                string opt3 = *(arg + 2);

                error = false;
                if (opt2 == string("-r"))
                {
                    options.resize = opt3;
                }
                else if (opt2 == string("-a"))

                {
                    options.ascii = opt3;
                    /* code */
                }

                else if (opt2 == string("-w"))

                {
                    options.winsize = opt3;
                    /* code */
                }

                else
                {
                    options.saveFile = opt3;
                }
            }
            if (argc > 4)
            {
                string opt4 = *(arg + 3);
                error = true;

                if (opt4 != string("-f") && opt4 != string("-r") && opt4 != string("-a") && opt4 != string("-w"))
                {
                    options.errors.push_back("invalid argument " + opt2);
                    return options;
                }

                if (opt2 == opt4)
                {
                    options.errors.push_back("Invalid arguments");
                    return options;
                }

                if (argc > 5)
                {

                    string opt5 = *(arg + 4);
                    error = false;
                    if (opt4 == string("-r"))
                    {
                        options.resize = opt5;
                    }
                    else if (opt4 == string("-a"))

                    {
                        options.ascii = opt5;
                        /* code */
                    }

                    else if (opt4 == string("-w"))

                    {
                        options.winsize = opt5;
                        /* code */
                    }

                    else
                    {
                        options.saveFile = opt5;
                    }
                }

                if (argc > 6)
                {
                    string opt6 = *(arg + 5);
                    error = true;

                    if (opt6 != string("-f") && opt6 != string("-r") && opt6 != string("-a") && opt6 != string("-w"))
                    {
                        options.errors.push_back("invalid argument " + opt2);
                        return options;
                    }

                    if (opt2 == opt6 || opt6 == opt4)
                    {
                        options.errors.push_back("Invalid arguments");
                        return options;
                    }

                    if (argc > 7)
                    {
                        string opt7 = *(arg + 6);
                        error = false;
                        if (opt6 == string("-r"))
                        {
                            options.resize = opt7;
                        }
                        else if (opt6 == string("-a"))

                        {
                            options.ascii = opt7;
                            /* code */
                        }

                        else if (opt6 == string("-w"))

                        {
                            options.winsize = opt7;
                            /* code */
                        }
                        else
                        {
                            options.saveFile = opt7;
                        }
                    }

                    if (argc > 8)
                    {
                        string opt8 = *(arg + 6);
                        error = true;

                        if (opt8 != string("-f") && opt8 != string("-r") && opt8 != string("-a") && opt8 != string("-w"))
                        {
                            options.errors.push_back("invalid argument " + opt2);
                            return options;
                        }

                        if (opt2 == opt8 || opt8 == opt4)
                        {
                            options.errors.push_back("Invalid arguments");
                            return options;
                        }

                        if (argc > 9)
                        {
                            string opt9 = *(arg + 6);
                            error = false;
                            if (opt8 == string("-r"))
                            {
                                options.resize = opt9;
                            }
                            else if (opt8 == string("-a"))

                            {
                                options.ascii = opt9;
                                /* code */
                            }

                            else if (opt8 == string("-w"))

                            {
                                options.winsize = opt9;
                                /* code */
                            }
                            else
                            {
                                options.saveFile = opt9;
                            }
                        }
                    }
                }
            }

            if (error)
            {
                string error = "Incorrect length of arguments";
                options.errors.push_back(error);
            }
        }
    }
    else
    {
        string error = "Incorrect length of arguments";
        options.errors.push_back(error);
    }
    return options;
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
    string ret = "{pixels:[";
    int currentIndex = 0, stop = (width*height)-1;


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
                if(currentIndex<stop)reti+=',';
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
    ret+="]";
    ret+= ", \"dimen\": ";
    ret+='"';
    ret+= to_string(width)+"x"+ to_string(height)+"\"}";
 
    return ret;
}