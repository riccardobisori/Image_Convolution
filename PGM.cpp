//
// Created by Utente on 16/03/2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "PGM.h"


using namespace std;

//init with default values
void PGM::init() {
    pgmImage = BitmapImage<GrayPixel>(1, 1);
    maxColVal = 255;
}

//create a PGM object
PGM::PGM(int _width, int _height) {
    init();
    nColumns = _width;
    nLines = _height;
    pgmImage.setWidth(nColumns);
    pgmImage.setHeight(nLines);
    pgmImage.setBuffer(nColumns, nLines);
}

//destructor


//create a PGM object and fill it wit data stored in fname
PGM::PGM(const string fname) {
    init();
    read(fname);
}


//create a casual PGM image with given width and height
PGM::PGM(const int _width, const int _height, string fname) {
    init();
    pgmImage.setWidth(_width);
    pgmImage.setHeight(_height);
    nLines = pgmImage.getHeight();
    nColumns = pgmImage.getWidth();

    pgmImage.setBuffer(nColumns, nLines);

    ofstream inp;
    inp.open(fname, ios::out | ios::binary);
    if (inp.is_open()) {
        inp << "P5\n";
        inp << nColumns;
        inp << " ";
        inp << nLines << "\n";
        inp << maxColVal << "\n";

        char aux;
        GrayPixel tmp;

        srand((unsigned) time(0));

        for (int i = 0; i < nLines; ++i) {
            for (int j = 0; j < nColumns; ++j) {
                tmp.setGray(static_cast<unsigned char>((rand() % 255) + 1));

                aux = (char) tmp.getGray();
                inp.write(&aux, 1);
            }
        }
        inp.close();
    } else {
        cout << "Error. Unable to open " << fname << endl;
        return;
    }
}


//read the PGM image from fname
void PGM::read(const string fname) {
    ifstream inp(fname.c_str(), ios::in | ios::binary);
    if (inp.is_open()) {
        string line;
        getline(inp, line);
        if (line != "P5") {
            cout << "Error. Unrecognized file format." << endl;
            return;
        }
        getline(inp, line);
        while (line[0] == '#') {
            getline(inp, line);
        }
        stringstream dimensions(line);

        try {
            dimensions >> nColumns;
            dimensions >> nLines;
            pgmImage.setWidth(nColumns);
            pgmImage.setHeight(nLines);
            pgmImage.setBuffer(nColumns, nLines);
        } catch (exception &e) {
            cout << "Header file format  error. " << e.what() << endl;
            return;
        }

        getline(inp, line);
        stringstream maxVal(line);
        try {
            maxVal >> maxColVal;
        } catch (exception &e) {
            cout << "Header file format error." << e.what() << endl;
            return;
        }

        char aux;
        GrayPixel tmp;
        for (int i = 0; i < nLines; ++i) {
            for (int j = 0; j < nColumns; ++j) {
                inp.read(&aux, 1);
                tmp.setGray((unsigned char) aux);

                pgmImage.setPixel(i, j, tmp);
            }
        }
        inp.close();
    } else {
        cout << "Error. Unable to open " << fname << endl;
        return;
    }
}

//write the PGM image in fname
void PGM::write(const string fname) {
    ofstream inp(fname, ios::out | ios::binary);
    if (inp.is_open()) {
        inp << "P5\n";
        inp << nColumns;
        inp << " ";
        inp << nLines << "\n";
        inp << maxColVal << "\n";

        char aux;
        GrayPixel tmp;

        for (int i = 0; i < nLines; i++) {
            for (int j = 0; j < nColumns; j++) {
                tmp = pgmImage.getPixel(i, j);

                aux = (char) tmp.getGray();
                inp.write(&aux, 1);
            }
        }
        inp.close();
    } else {
        cout << "Error. Unable to open " << fname << endl;
        return;
    }
}

void PGM::matrixConvolutionPGM(const Filter &kernel) {
    int kCols = kernel.getColumns();
    int kRows = kernel.getRows();
    int kCenterX = kCols / 2;
    int kCenterY = kRows / 2;
    int i, j, m, mm, n, nn, ii, jj;
    float graySum; // somma temporanea durante la convoluzione di un singolo pixel (se viene <0 si mette 0, se viene >255 si mette 255)
    GrayPixel *tmpBuffer = new GrayPixel[nColumns * nLines]; // buffer temporaneo dinamico (dinamico per lavorare anche con immagini grandi)

    try {
        for (i = 0; i < nLines; i++) {      // righe immagine
            for (j = 0; j < nColumns; j++) {// colonne immagine
                graySum = 0;

                for (m = 0; m < kRows; m++) {   // righe kernel
                    mm = kRows - 1 - m;      // indice righe kernel opposto
                    for (n = 0; n < kCols; n++) {  // colonne kernel
                        nn = kCols - 1 - n;  // indice colonne kernel opposto
                        ii = i + (m - kCenterY); // indici usati per controllo valori fuori dai bordi
                        jj = j + (n - kCenterX);

                        if (ii >= 0 && ii < nLines && jj >= 0 && jj < nColumns) { // controllo degli indici (entra nell'if quando il pixel del kernel non è fuori dai bordi dell'immagine)

                            graySum += (float) (pgmImage.getBuffer()[jj * nLines + ii].getGray()) *
                                    kernel.getBuffer()[nn * kRows + mm];
                        }
                    }
                }

                tmpBuffer[j * nLines + i].setGray(graySum);

            }
        }

        for (int p = 0; p < nLines; p++) {
            for (int q = 0; q < nColumns; q++) {
                pgmImage.setPixel(p, q, tmpBuffer[q * nLines + p]);
            }
        }

    } catch (exception &e) {
        delete[] tmpBuffer;
        cout << "Errore durante la convoluzione!";
        return;
    }

    delete[] tmpBuffer;

}

