//
// Created by Utente on 01/02/2018.
//

#include <vector>
#include <string>
#include "BitmapImage.h"
#include "Filter.h"

using namespace std;

#ifndef IMAGE_CONVOLUTION_PPM_H
#define IMAGE_CONVOLUTION_PPM_H

class PPM {
    void init();

    //info about the PPM file (height and width)
    int nLines;
    int nColumns;
    int maxColVal;

public:

    BitmapImage<RGBPixel> ppmImage;

    void matrixConvolutionPPM(const Filter &kernel);

    PPM(int _width = 1, int _height = 1);

    //create a PPM object and fill it with data stored in fname
    PPM(const string fname);

    //create a casual PPM image with a given width and height
    PPM(const int _width, const int _height, string fname);


    //read the PPM image from fname
    void read(const string fname);

    //write the PPM image in fname
    void write(const string fname);

};


#endif //IMAGE_CONVOLUTION_PPM_H
