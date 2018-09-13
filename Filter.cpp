//
// Created by Utente on 24/09/2017.
//

#include "Filter.h"

Filter::~Filter() { }

int Filter::getRows() const {
    return rows;
}

int Filter::getColumns() const {
    return columns;
}

void Filter::setRows(int rows) {
    Filter::rows = rows;
}

void Filter::setColumns(int columns) {
    Filter::columns = columns;
}

float *Filter::getBuffer() const {
    return buffer;
}

void Filter::setBuffer(float *buffer) {
    Filter::buffer = buffer;
}

