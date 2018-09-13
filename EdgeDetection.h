//
// Created by Utente on 24/09/2017.
//

#ifndef IMAGE_CONVOLUTION_EDGEDETECTION_H
#define IMAGE_CONVOLUTION_EDGEDETECTION_H


#include "Filter.h"

// Versione "soft" dell'edge detection, ci sono anche versioni più forti.

class EdgeDetection : public Filter {
public:
    EdgeDetection();

    virtual ~EdgeDetection();
};


#endif //IMAGE_CONVOLUTION_EDGEDETECTION_H
