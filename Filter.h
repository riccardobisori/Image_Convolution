//
// Created by Utente on 24/09/2017.
//

// QUESTA CLASSE PRENDE IN INGRESSO I FILTRI E LI APPLICA ALL'IMMAGINE, ANZI NO SI FA DAL MAIN SENNÒ È UNO SMATTO CON GLI ATTRIBUTI PRIVATI


#ifndef IMAGE_CONVOLUTION_FILTER_H
#define IMAGE_CONVOLUTION_FILTER_H


//#include <stdexcept>


class Filter {
public:
    // virtual Filter();//le matrici di convulazione devono avere dimensione dispari
    virtual ~Filter() = 0;
    int getRows() const;
    int getColumns() const;
    void setRows(int rows);
    void setColumns(int columns);

    float *getBuffer() const;

    void setBuffer(float *buffer);

protected:
    int rows;
    int columns;
    float* buffer;

};



#endif //IMAGE_CONVOLUTION_FILTER_H
