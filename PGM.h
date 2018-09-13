//
// Created by Utente on 16/03/2018.
//

#ifndef IMAGE_CONVOLUTION_PGM_H
#define IMAGE_CONVOLUTION_PGM_H


#include "GrayPixel.h"
#include "BitmapImage.h"
#include <string>

using namespace std;

class PGM {
    void init();

    //info about the PPM file (height and width)
    int nLines;
    int nColumns;
    int maxColVal;

public:

    BitmapImage<GrayPixel> pgmImage;

    void matrixConvolutionPGM(const Filter &kernel);

    PGM(int _width = 1, int _height = 1);

    //create a PGM object and fill it with data stored in fname
    PGM(const string fname);

    //create a casual PGM image with a given width and height
    PGM(const int _width, const int _height, string fname);


    //read the PGM image from fname
    void read(const string fname);

    //write the PGM image in fname
    void write(const string fname);
};


#endif //IMAGE_CONVOLUTION_PGM_H
