//
// Created by Utente on 24/09/2017.
//

#include "GrayPixel.h"

GrayPixel::GrayPixel(unsigned char g) {
    if (g < 0)
        gray = 0;
    else if (g > 255)
        gray = 255;
    else
        gray = g;
}

unsigned char GrayPixel::getGray() const {
    return gray;
}

void GrayPixel::setGray(unsigned char gray) {
    GrayPixel::gray = gray;
}

void GrayPixel::setGray(float gray) {
    if (gray > 255)
        GrayPixel::gray = 255;
    else if (gray < 0)
        GrayPixel::gray = 0;
    else
        GrayPixel::gray = static_cast<unsigned char>(gray);
}

GrayPixel &GrayPixel::operator=(const GrayPixel &c) {
    gray = c.gray;
    return *this;
}
