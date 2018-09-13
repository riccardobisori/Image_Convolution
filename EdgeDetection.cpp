//
// Created by Utente on 24/09/2017.
//

#include "EdgeDetection.h"

EdgeDetection::EdgeDetection() {
    setRows(3);
    setColumns(3);
    buffer = new float[rows * columns];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++)
            buffer[j * rows + i] = 0;
    }
    buffer[0] = 1;
    buffer[2] = -1;
    buffer[6] = -1;
    buffer[8] = 1;
}

EdgeDetection::~EdgeDetection() {
    delete [] buffer;
}
