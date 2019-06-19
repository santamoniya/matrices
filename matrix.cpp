#include <iomanip>
#include "matrix.h"

Matrix::Matrix() {
    gueltig = false;
}

Matrix::Matrix(double val) {
    gueltig = true;
    zeilen = 1, spalten = 1;
    if (val != 0) {
        rows = vector<size_t>(1, 0);
        cols = vector<size_t>(1, 0);
        vals = vector<double>(1, val);
    }
}

Matrix::Matrix(int zeilen, int spalten) {
    gueltig = true;
    this->zeilen = zeilen;
    this->spalten = spalten;
}

Matrix::Matrix(Matrix &m) {
    if (!m.gueltig) {
        gueltig = false;
    } else {
        zeilen = m.zeilen;
        spalten = m.spalten;
        if (!m.vals.empty()) {
            rows = m.rows;
            cols = m.cols;
            vals = m.vals;
        }
    }
}

Matrix::~Matrix() {

}

Matrix &Matrix::operator=(const Matrix &m) {
    if (!m.gueltig) {
        if (gueltig) {
            rows.clear();
            cols.clear();
            vals.clear();
            gueltig = false;
        }
    } else {
        gueltig = m.gueltig;
        zeilen = m.zeilen;
        spalten = m.spalten;
        if (!m.vals.empty()) {
            rows = m.rows;
            cols = m.cols;
            vals = m.vals;
        }
    }
    return *this;
}

int Matrix::setze_element(int zeile, int spalte, double wert) {
    if (zeile < 0 || spalte < 0 || zeile >= zeilen || spalte >= spalten) {
        return 0;
    } else {

    }
    return 0;
}
