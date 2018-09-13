//
// Created by Utente on 17/03/2018.
//

#include "Blur.h"

Blur::Blur() {

    setRows(3);
    setColumns(3);
    buffer = new float[rows * columns];
    buffer[0] = 0.0625;
    buffer[1] = 0.125;
    buffer[2] = 0.0625;
    buffer[3] = 0.125;
    buffer[4] = 0.25;
    buffer[5] = 0.125;
    buffer[6] = 0.0625;
    buffer[7] = 0.125;
    buffer[8] = 0.0625;
}

Blur::~Blur() {
    delete [] buffer;
}