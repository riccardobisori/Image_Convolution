//
// Created by Utente on 24/09/2017.
//

#ifndef IMAGE_CONVOLUTION_GRAYPIXEL_H
#define IMAGE_CONVOLUTION_GRAYPIXEL_H


class GrayPixel {
public:
    GrayPixel(unsigned char g=0);
    //~GrayPixel(); finchè non ci son puntatori non si implementa o non si dichiara neanche per usare quello fornito dal compilatore

    unsigned char getGray() const;

    void setGray(unsigned char gray);

    void setGray(float gray);

    GrayPixel& operator=(const GrayPixel &c);

private:
    unsigned char gray;


};


#endif //IMAGE_CONVOLUTION_GRAYPIXEL_H
