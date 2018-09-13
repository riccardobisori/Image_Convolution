//
// Created by Utente on 24/09/2017.
//

#include "Identity.h"

Identity::Identity() {
    setRows(3);
    setColumns(3);
    buffer = new float[rows * columns];
    for(int i = 0; i <rows; i++){
        for(int j = 0; j < columns; j++)
            buffer[j * rows + i] = 0;
    }
    buffer[4] = 1;
}

Identity::~Identity() {
    delete [] buffer;
}
