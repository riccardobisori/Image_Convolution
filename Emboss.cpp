//
// Created by Utente on 17/03/2018.
//

#include "Emboss.h"

Emboss::Emboss() {
    setRows(3);
    setColumns(3);
    buffer = new float[rows * columns];

    buffer[0] = -2;
    buffer[1] = -1;
    buffer[2] = 0;
    buffer[3] = -1;
    buffer[4] = 1;
    buffer[5] = 1;
    buffer[6] = 0;
    buffer[7] = 1;
    buffer[8] = 2;
}

Emboss::~Emboss() {
    delete [] buffer;
}
