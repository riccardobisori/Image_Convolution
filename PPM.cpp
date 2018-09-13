//
// Created by Utente on 01/02/2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdlib.h>
#include <time.h>


#include "PPM.h"

using namespace std;

//init with default values

void PPM::init() {
    ppmImage = BitmapImage<RGBPixel>(1, 1);
    maxColVal = 255;
}

//create a PPM object
PPM::PPM(int _width, int _height) {
    init();
    nColumns = _width;
    nLines = _height;
    ppmImage.setWidth(nColumns);
    ppmImage.setHeight(nLines);
    ppmImage.setBuffer(nColumns, nLines);
}

//create a PPM object and fill it wit data stored in fname
PPM::PPM(const string fname) {
    init();
    read(fname);
}


//create a casual PPM image with given width and height
PPM::PPM(const int _width, const int _height, string fname) {
    init();
    ppmImage.setWidth(_width);
    ppmImage.setHeight(_height);
    nLines = ppmImage.getHeight();
    nColumns = ppmImage.getWidth();

    ppmImage.setBuffer(nColumns, nLines);

    ofstream inp;
    inp.open(fname, ios::out | ios::binary);
    if (inp.is_open()) {
        inp << "P6\n";
        inp << nColumns;
        inp << " ";
        inp << nLines << "\n";
        inp << maxColVal << "\n";

        char aux;
        RGBPixel tmp;

        srand((unsigned) time(0));

        for (int i = 0; i < nLines; ++i) {
            for (int j = 0; j < nColumns; ++j) {
                tmp.setR(static_cast<unsigned char>((rand() % 255) + 1));
                tmp.setG(static_cast<unsigned char>((rand() % 255) + 1));
                tmp.setB(static_cast<unsigned char>((rand() % 255) + 1));

                aux = (char) tmp.getR();
                inp.write(&aux, 1);
                aux = (char) tmp.getG();
                inp.write(&aux, 1);
                aux = (char) tmp.getB();
                inp.write(&aux, 1);
            }
        }
        inp.close();
    } else {
        cout << "Error. Unable to open " << fname << endl;
        return;
    }

}


//read the PPM image from fname
void PPM::read(const string fname) {
    ifstream inp(fname.c_str(), ios::in | ios::binary);
    if (inp.is_open()) {
        string line;
        getline(inp, line);
        if (line != "P6") {
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
            ppmImage.setWidth(nColumns);
            ppmImage.setHeight(nLines);
            ppmImage.setBuffer(nColumns, nLines);
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
        RGBPixel tmp;
        for (int i = 0; i < nLines; ++i) {
            for (int j = 0; j < nColumns; ++j) {
                inp.read(&aux, 1);
                tmp.setR((unsigned char) aux);
                //r[i] = (unsigned char) aux;
                inp.read(&aux, 1);
                tmp.setG((unsigned char) aux);
                //g[i] = (unsigned char) aux;
                inp.read(&aux, 1);
                tmp.setB((unsigned char) aux);
                //b[i] = (unsigned char) aux;
                ppmImage.setPixel(i, j, tmp);
            }
        }
        inp.close();
    } else {
        cout << "Error. Unable to open " << fname << endl;
        return;
    }
}

//write the PPM image in fname
void PPM::write(const string fname) {
    ofstream inp(fname, ios::out | ios::binary);
    if (inp.is_open()) {
        inp << "P6\n";
        inp << nColumns;
        inp << " ";
        inp << nLines << "\n";
        inp << maxColVal << "\n";

        char aux;
        RGBPixel tmp;

        for (int i = 0; i < nLines; i++) {
            for (int j = 0; j < nColumns; j++) {
                tmp = ppmImage.getPixel(i, j);

                aux = (char) tmp.getR();
                inp.write(&aux, 1);
                aux = (char) tmp.getG();
                inp.write(&aux, 1);
                aux = (char) tmp.getB();
                inp.write(&aux, 1);
            }
        }
        inp.close();
    } else {
        cout << "Error. Unable to open " << fname << endl;
        return;
    }
}

void PPM::matrixConvolutionPPM(const Filter &kernel) {
    int kCols = kernel.getColumns();
    int kRows = kernel.getRows();
    int kCenterX = kCols / 2;
    int kCenterY = kRows / 2;
    int i, j, m, mm, n, nn, ii, jj;
    float rSum, gSum, bSum; // somme temporanee per svolgere la convoluzione (verranno troncate a 0 o 255 quando inserite nel tmpBuffer)
    RGBPixel *tmpBuffer = new RGBPixel[nColumns * nLines]; //buffer temporaneo dinamico (dinamico per lavorare on immagini grandi)

    try {
        for (i = 0; i < nLines; i++) {      // righe immagine
            for (j = 0; j < nColumns; j++) { // colonne immagine
                rSum = 0;
                gSum = 0;
                bSum = 0;
                for (m = 0; m < kRows; m++) {   // righe kernel
                    mm = kRows - 1 - m;      // indice righe kernel opposto
                    for (n = 0; n < kCols; n++) {  // colonne kernel
                        nn = kCols - 1 - n;  // indice colonne kernel opposto
                        ii = i + (m - kCenterY); // indici usati per controllo valori fuori dai bordi
                        jj = j + (n - kCenterX);

                        if (ii >= 0 && ii < nLines && jj >= 0 && jj < nColumns) { // entra nell'if quando il kernel non è fuori dai bordi dell'immagine

                            rSum += (float) (ppmImage.getBuffer()[jj * nLines + ii].getR()) *
                                    kernel.getBuffer()[nn * kRows + mm];
                            gSum += (float) (ppmImage.getBuffer()[jj * nLines + ii].getG()) *
                                    kernel.getBuffer()[nn * kRows + mm];
                            bSum += (float) (ppmImage.getBuffer()[jj * nLines + ii].getB()) *
                                    kernel.getBuffer()[nn * kRows + mm];

                        }

                    }
                }
                tmpBuffer[j * nLines + i].setR(rSum);
                tmpBuffer[j * nLines + i].setG(gSum);
                tmpBuffer[j * nLines + i].setB(bSum);

            }
        }

        for (int p = 0; p < nLines; p++) {
            for (int q = 0; q < nColumns; q++) {
                ppmImage.setPixel(p, q, tmpBuffer[q * nLines + p]);
            }
        }

    } catch (exception &e) {
        delete[] tmpBuffer;
        cout << "Errore durante la convoluzione!" << endl;
        return;
    }
    delete[] tmpBuffer;

}


