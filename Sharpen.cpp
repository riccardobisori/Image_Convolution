//
// Created by Utente on 16/03/2018.
//

#include "Sharpen.h"

Sharpen::Sharpen() {
    setRows(3);
    setColumns(3);
    buffer = new float[rows * columns];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++)
            buffer[j * rows + i] = 0;
    }
    buffer[1] = -1;
    buffer[3] = -1;
    buffer[4] = 5;
    buffer[5] = -1;
    buffer[7] = -1;
}

Sharpen::~Sharpen() {
    delete [] buffer;
}