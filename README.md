# Lion image to ascii

A C++ Program that prints a given image as ascii characters to the console or saves it to 
a file if the  `-f` option is provided; it has kind of a faulty support for animating gif images and if you can figure it out I'll love your contribution


## Example 

![example](example.png)

## Usage

> You must have the Imagemagick program and Magick++ library to compile this program 

```sh

make

```

then run

```sh

make install && make clean

```

After compiling just run ->

```sh

limgtoasci imagePath 

```

## Options

| Option          | Use                  |
| -------------   |:--------------------:|
| -r --resize     | resize the image     |
| -s --savefile   | Save output to file  |
| -a --ascii      | ascii characters used|
| -f --filter     | add a filter (1 to 3)|

## Tools

 [ImageMagick®](https://imagemagick.org/) 


## Author

**Kosiken**


### Todo

- Fix window size option [ <span style="color: red">x</span> ]
- Add option for scale [ <span style="color: red">x</span> ]
- Fix issues for gif resize [ <span style="color: red">x</span> ]
