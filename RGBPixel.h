//
// Created by Utente on 24/09/2017.
//

#ifndef IMAGE_CONVOLUTION_RGBPIXEL_H
#define IMAGE_CONVOLUTION_RGBPIXEL_H


class RGBPixel {
public:
    RGBPixel(unsigned char r=0, unsigned char g=0, unsigned char b=0);

    unsigned char getR() const;

    void setR(unsigned char R);

    void setR(float R);

    unsigned char getG() const;

    void setG(unsigned char G);

    void setG(float G);

    unsigned char getB() const;

    void setB(unsigned char B);

    void setB(float B);

private:
    unsigned char R,G,B;

};


#endif //IMAGE_CONVOLUTION_RGBPIXEL_H
