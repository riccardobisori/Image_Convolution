//
// Created by Utente on 24/09/2017.
//

#include "RGBPixel.h"

RGBPixel::RGBPixel(unsigned char r, unsigned char g, unsigned char b) {
    if (r < 0)
        R = 0;
    else if (r > 255)
        R = 255;
    else
        R = r;

    if (g < 0)
        G = 0;
    else if (g > 255)
        G = 255;
    else
        G = g;

    if (b < 0)
        B = 0;
    else if (b > 255)
        B = 255;
    else
        B = b;
}


unsigned char RGBPixel::getR() const {
    return R;
}

void RGBPixel::setR(unsigned char R) {
    RGBPixel::R = R;
}

void RGBPixel::setR(float R) {
    if (R > 255)
        RGBPixel::R = 255;
    else if (R < 0)
        RGBPixel::R = 0;
    else
        RGBPixel::R = static_cast<unsigned char> (R);
}

unsigned char RGBPixel::getG() const {
    return G;
}

void RGBPixel::setG(unsigned char G) {
    RGBPixel::G = G;
}

void RGBPixel::setG(float G) {
    if (G > 255)
        RGBPixel::G = 255;
    else if (G < 0)
        RGBPixel::G = 0;
    else
        RGBPixel::G = static_cast<unsigned char> (G);
}


unsigned char RGBPixel::getB() const {
    return B;
}

void RGBPixel::setB(unsigned char B) {
    RGBPixel::B = B;
}

void RGBPixel::setB(float B) {
    if (B > 255)
        RGBPixel::B = 255;
    else if (B < 0)
        RGBPixel::B = 0;
    else
        RGBPixel::B = static_cast<unsigned char> (B);
}

