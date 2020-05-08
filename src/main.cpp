/*
A C++ Program that prints a given image as ascii characters to the console
*/

#include "ToAScii.h"

#include <iostream>


// using namespace Magick;


int main(int argc, char **argv)
{

 

    string ascii="";
    int H, W;

    // Keeps track of command line options
    lionOptions options = parseOptions(argc, argv);

    if (options.errors.size() > 0)
    {
        cout << usage() << endl;
        list<string>::iterator pos = options.errors.begin();
        while (pos != options.errors.end())
        {
            cout << "\x1b[38;2;255;0;0m"
                 << *(pos)
                 << endl;

            pos++;
        }
        return 0;
    }
  // cout<<options.fileName;
   //cout<<options.winsize<<endl;
    ToAscii toas(options);


if(options.saveFile.length()> 0) toas.saveFile(options.saveFile.c_str());
else  toas.printImage();


    return 0;
}


