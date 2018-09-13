/*(4) Classe template che rappresenta immagini a 1 e 3 canali. Classe che implementa kernel
 * image processing. (https://en.wikipedia.org/wiki/Kernel_(image_processing) -
 * http://rosettacode.org/wiki/Image_convolution). Lettura e scrittura in formato PPM/PGM.
 * (https://en.wikipedia.org/wiki/Netpbm_format)
*/


#include <iostream>
#include "BitmapImage.h"
#include "GrayPixel.h"
#include "Identity.h"
#include "EdgeDetection.h"
#include "PPM.h"
#include "PGM.h"
#include "Sharpen.h"
#include "Emboss.h"
#include "Blur.h"
#include <stdlib.h>
#include <random>
#include <time.h>

using namespace std;

void menuFiltri();

int main() {
    int w, h;
    string menu;
    Filter *filter;

    cout << "\n**********************************************************************************************" << endl;
    cout << "Lettura, scrittura e applicazione filtri a immagini PPM e PGM" << endl;
    cout << "**********************************************************************************************" << endl;

    while (true) {

        cout << "\n\nCosa vuoi fare?" << endl;
        cout << "1) Crea matrice casuale ed esegui convoluzione (esempio del funzionamento della convoluzione)" << endl;
        cout << "2) Inserisci immagine da file e applica filtro." << endl;
        cout << "3) Crea immagine casuale." << endl;
        cout << "4) Chiudi programma." << endl;


        cin >> menu;

        while (menu != "1" && menu != "2" && menu != "3") {
            if (menu == "4")
                return 0;

            cout << "\nErrore. Inserire 1, 2 o 3. Inserire 4 per uscire." << endl;
            cin >> menu;

        }


        //********************************************************************************************************
        // Creazione matrice casuale e applicazione del filtro. Utile per vedere come funziona la convoluzione
        //********************************************************************************************************

        if (menu == "1") {
            cout << "\nCrea una matrice casuale e applica filtro.\n" << endl;
            cout << "Inserisci larghezza: " << endl;
            cin >> w;
            cout << "\nInserisci altezza: " << endl;
            cin >> h;
            cout << "\nSeleziona tipo di immagine: " << endl;
            cout << "1) Immagine a gradazione di grigio" << endl << "2) Immagine a colori" << endl;
            cout << "3) Chiudi programma" << endl;


            cin >> menu;

            while (menu != "1" && menu != "2") {
                if (menu == "3")
                    return 0;


                cout << "\nImmagine non valida. Inserire 1 o 2." << endl;
                cin >> menu;
            }


            if (menu == "1") {
                PGM grayImage(w, h);
                srand((unsigned int) time(0));

                cout << "\nL'immagine creata e': \n" << endl;

                for (int i = 0; i < h; i++) {
                    cout << " " << endl;
                    for (int j = 0; j < w; j++) {
                        GrayPixel u(static_cast<unsigned char>((rand() % 255) + 1));
                        grayImage.pgmImage.setPixel(i, j, u);
                        cout << (static_cast<int> (grayImage.pgmImage.getBuffer()[j * h + i].getGray())) << " ";
                    }
                }

                cout << endl;

                menuFiltri();


                cin >> menu;

                while (menu != "1" && menu != "2" && menu != "3" && menu != "4" && menu != "5") {
                    if (menu == "6")
                        return 0;

                    cout << endl << "\nFiltro non valido. Inserire 1, 2, 3, 4 o 5." << endl;
                    cin >> menu;
                }


                if (menu == "1")
                    filter = new Identity;
                else if (menu == "2")
                    filter = new EdgeDetection;
                else if (menu == "3")
                    filter = new Sharpen;
                else if (menu == "4")
                    filter = new Emboss;
                else if (menu == "5")
                    filter = new Blur;


                try {
                    grayImage.matrixConvolutionPGM(*filter);
                    cout << endl << "\nL'immagine filtrata e': " << endl;

                    for (int i = 0; i < h; i++) {
                        cout << endl;
                        for (int j = 0; j < w; j++) {
                            cout << (static_cast<int> (grayImage.pgmImage.getBuffer()[j * h + i].getGray())) << " ";
                        }
                    }
                    cout << endl;
                } catch (exception &e) {
                    delete filter;
                    cerr << "Errore nella convoluzione." << endl;
                    return -1;
                }
                delete filter;
            }

            else if (menu == "2") {
                PPM coloredImage(w, h);

                srand((unsigned int) time(0));

                cout << endl << "\nL'immagine creata e': " << endl;

                for (int i = 0; i < h; i++) {
                    cout << endl;
                    for (int j = 0; j < w; j++) {
                        RGBPixel u(static_cast<unsigned char>((rand() % 255) + 1),
                                   static_cast<unsigned char>((rand() % 255) + 1),
                                   static_cast<unsigned char>((rand() % 255) + 1));
                        coloredImage.ppmImage.setPixel(i, j, u);
                        cout << "(" << (static_cast<int> (coloredImage.ppmImage.getBuffer()[j * h + i].getR())) << ", ";
                        cout << (static_cast<int> (coloredImage.ppmImage.getBuffer()[j * h + i].getG())) << ", ";
                        cout << (static_cast<int> (coloredImage.ppmImage.getBuffer()[j * h + i].getB())) << ") ";
                    }
                }

                cout << endl;

                menuFiltri();


                cin >> menu;

                while (menu != "1" && menu != "2" && menu != "3" && menu != "4" && menu != "5") {
                    if (menu == "6")
                        return 0;

                    cout << endl << "\nFiltro non valido. Inserire 1, 2, 3, 4 o 5." << endl;
                    cin >> menu;
                }

                if (menu == "1")
                    filter = new Identity;
                else if (menu == "2")
                    filter = new EdgeDetection;
                else if (menu == "3")
                    filter = new Sharpen;
                else if (menu == "4")
                    filter = new Emboss;
                else if (menu == "5")
                    filter = new Blur;


                try {
                    coloredImage.matrixConvolutionPPM(*filter);
                    cout << endl << "\nL'immagine filtrata e': " << endl;

                    for (int i = 0; i < h; i++) {
                        cout << endl;
                        for (int j = 0; j < w; j++) {
                            cout << "(" << (static_cast<int> (coloredImage.ppmImage.getBuffer()[j * h + i].getR())) <<
                            ", ";
                            cout << (static_cast<int> (coloredImage.ppmImage.getBuffer()[j * h + i].getG())) << ", ";
                            cout << (static_cast<int> (coloredImage.ppmImage.getBuffer()[j * h + i].getB())) << ") ";
                        }
                    }
                    cout << endl;
                } catch (exception &e) {
                    delete filter;
                    cerr << "Errore nella convoluzione" << endl;
                    return -1;
                }

                delete filter;

            }
        }

            //***************************************************************************************************
            // Lettura immagine, applicazione filtro, scrittura immagine.
            //***************************************************************************************************

        else if (menu == "2") {

            cout << "\nCon che immagini vuoi lavorare?" << endl;
            cout << "1) Immagini a gradazione di grigio (.pgm)" << endl;
            cout << "2) Immagini a colori (.ppm)" << endl;

            cin >> menu;

            while (menu != "1" && menu != "2") {
                cout << "\nErrore. Inserire 1 o 2." << endl;
                cin >> menu;
            }


            if (menu == "1") {
                string fileNamePGM, newFileNamePGM;
                cout << "\nInserisci nome file (comprensivo del percorso, pgm binary only)." << endl;
                cin >> fileNamePGM;

                PGM imagePGM(fileNamePGM);

                menuFiltri();

                cin >> menu;

                while (menu != "1" && menu != "2" && menu != "3" && menu != "4" && menu != "5") {
                    if (menu == "6")
                        return 0;

                    cout << endl << "Filtro non valido. Inserire 1, 2, 3, 4 o 5." << endl;
                    cin >> menu;
                }

                cout << "\nInserisci nuovo nome file (comprensivo del percorso): " << endl;
                cin >> newFileNamePGM;

                if (menu == "1")
                    filter = new Identity;
                else if (menu == "2")
                    filter = new EdgeDetection;
                else if (menu == "3")
                    filter = new Sharpen;
                else if (menu == "4")
                    filter = new Emboss;
                else if (menu == "5")
                    filter = new Blur;


                try {
                    imagePGM.matrixConvolutionPGM(*filter);
                    imagePGM.write(newFileNamePGM);
                    cout << "Fatto! :)" << endl;
                } catch (exception &e) {
                    delete filter;
                    cerr << "Errore nella convoluzione" << endl;
                    return -1;
                }
                delete filter;

            }
            else if (menu == "2") {
                string fileNamePPM, newFileNamePPM;
                cout << "\nInserisci nome file (comprensivo del percorso, ppm binary only)." << endl;
                cin >> fileNamePPM;

                PPM imagePPM(fileNamePPM);

                menuFiltri();


                cin >> menu;

                while (menu != "1" && menu != "2" && menu != "3" && menu != "4" && menu != "5") {
                    if (menu == "6")
                        return 0;

                    cout << endl << "Filtro non valido. Inserire 1, 2, 3, 4 o 5." << endl;
                    cin >> menu;
                }

                cout << "\nInserisci nuovo nome file (comprensivo del percorso): " << endl;
                cin >> newFileNamePPM;

                if (menu == "1")
                    filter = new Identity;
                else if (menu == "2")
                    filter = new EdgeDetection;
                else if (menu == "3")
                    filter = new Sharpen;
                else if (menu == "4")
                    filter = new Emboss;
                else if (menu == "5")
                    filter = new Blur;


            try {
                imagePPM.matrixConvolutionPPM(*filter);
                imagePPM.write(newFileNamePPM);
                cout << "Fatto! :)" << endl;
            } catch (exception &e) {
                delete filter;
                cerr << "Errore nella convoluzione" << endl;
                return -1;
            }
            delete filter;

        }
    }

    //*********************************************************************************************
    // Creazione immagine completamente casuale.
    //*********************************************************************************************

    else if (menu == "3") {
        string fileName;
        cout << "\nChe tipo di immagine vuoi creare?" << endl;
        cout << "1) Immagine a gradazione di grigio." << endl << "2) Immagine a colori" << endl;
        cout << "3) Chiudi programma" << endl;

            cin >> menu;

            while (menu != "1" && menu != "2") {
                if (menu == "3")
                    return 0;

                cout << "\nErrore. Inserire 1 o 2." << endl;
                cin >> menu;
            }


        if (menu == "1") {

            cout << "\nCrea immagine casuale (pgm binary image).\n" << endl;
            cout << "Inserisci larghezza: " << endl;
            cin >> w;
            cout << "\nInserisci altezza: " << endl;
            cin >> h;
            cout << "\nInserisci nome file (comprensivo del percorso): " << endl;
            cin >> fileName;

            PGM imagePGM(w, h, fileName);

            cout << "\nFatto! :)" << endl;
        }

        else if (menu == "2") {

            cout << "\nCrea immagine casuale (ppm binary image).\n" << endl;
            cout << "Inserisci larghezza: " << endl;
            cin >> w;
            cout << "\nInserisci altezza: " << endl;
            cin >> h;
            cout << "\nInserisci nome file (comprensivo del percorso): " << endl;
            cin >> fileName;

            PPM imagePPM(w, h, fileName);

            cout << "\nFatto! :)" << endl;
        }
    }
}

}

void menuFiltri() {
    cout << "\nQuale filtro desideri applicare?" << endl;
    cout << "1) Identity: lascia l'immagine invariata (che noia! :P)" << endl;
    cout <<
    "2) Edge Detection: mette in mostra le differenze tra i valori dei pixel. Un pixel vicino ad altri pixel "
            "con circa la stessa intensità diventerà nero, un pixel vicino a pixel molto differenti diventerà "
            "bianco." << endl;
    cout << "3) Sharpen: enfatizza la differenza tra i pixel vicini. Rende l'immagine più definita." <<
    endl;
    cout <<
    "4) Emboss: enfatizza le differenze dei pixel in una data direzione. In questo caso, dall'angolo"
            " in alto a sinistra all'angolo in basso a destra, accentuando l'impressione di profondità." <<
    endl;
    cout << "5) Blur: attenua le differenze tra pixel vicini. Rende l'immagine meno nitida." << endl;
    cout << "6) Chiudi programma." << endl;
}

