#include <iomanip>
#include "matrix.h"

Matrix::Matrix() {
    ungueltig = false;
}

Matrix::Matrix(double val) {
    ungueltig = true;
    zeilen = 1;
    spalten = 1;
    grosse = 1;
    array = new double[1];
    array[0] = val;
}

Matrix::Matrix(int zeilen, int spalten) {
    ungueltig = true;
    this->zeilen = zeilen;
    this->spalten = spalten;
    grosse = zeilen * spalten;
    array = new double[zeilen * spalten];
    for (int i = 0; i < zeilen; i++)
        for (int j = 0; j < spalten; j++)
            array[i * spalten + j] = 0.0;
}

Matrix::Matrix(Matrix &m) {
    if (!m.ungueltig) {
        ungueltig = false;
    } else {
        ungueltig = true;
        zeilen = m.zeilen;
        spalten = m.spalten;
        grosse = m.grosse;
        array = new double[zeilen * spalten];
        int size = m.zeilen * m.spalten;
        for (int i = 0; i < size; i++)
            array[i] = m.array[i];
    }
}

Matrix::~Matrix() {
    if(ungueltig)
        delete[] array;
}

int Matrix::n_zeilen() {
    return zeilen;
}

int Matrix::n_spalten() {
    return spalten;
}

double Matrix::lese_element(int zeile, int spalte, int &erfolg) {
    if (zeile < 0 || zeile >= zeilen || spalte < 0 || spalte >= spalten) {
        erfolg = 0;
        return 0;
    } else {
        erfolg = 1;
        return array[zeile * spalten + spalte];
    }
}

int Matrix::setze_element(int zeile, int spalte, double wert) {
    if (zeile < 0 || zeile >= zeilen || spalte < 0 || spalte >= spalten) {
        return 0;
    } else {
        array[zeile * spalten + spalte] = wert;
        return 1;
    }
}

int Matrix::ist_gueltig() {
    return int(ungueltig);
}

Matrix Matrix::transposition() {
    if (ungueltig) {
        Matrix m(spalten, zeilen);
        for (int i = 0; i < zeilen; i++)
            for (int j = 0; j < spalten; j++) {
                double element = array[i * spalten + j];
                m.setze_element(j, i, element);
            }
        return m;
    } else {
        Matrix m;
        return m;
    }
}

Matrix Matrix::operator+(Matrix &m) {
    if (ungueltig && m.ungueltig && zeilen == m.zeilen && spalten == m.spalten) {
        Matrix sum(m.zeilen, m.spalten);
        int size = m.zeilen * m.spalten;
        for (int i = 0; i < size; i++) {
            sum.array[i] = array[i] + m.array[i];
        }
        return sum;
    } else {
        Matrix invalid_matrix;
        return invalid_matrix;
    }
}

Matrix Matrix::operator*(Matrix &m) {
    if (ungueltig && m.ungueltig && spalten == m.zeilen) {
        int zeile = zeilen;
        int spalte = m.spalten;
        Matrix product(zeile, spalte);
        for (int i = 0; i < zeile; i++)
            for (int j = 0; j < spalte; j++)
            {
                double result = 0;
                for (int k = 0; k < spalten; k++) {
                    double val1 = array[i * spalten + k];
                    double val2 = m.array[k * m.spalten + j];
                    result += val1 * val2;
                }
                product.array[i * spalte + j] = result;
            }
        return product;
    } else {
        Matrix invalid_matrix;
        return invalid_matrix;
    }
}

int Matrix::operator==(Matrix &m) {
    if (ungueltig) {
        if (m.ungueltig) {
            if (zeilen == m.zeilen && spalten == m.spalten) {
                bool similar = true;
                for (int i = 0; i < grosse; i++) {
                    if (array[i] != m.array[i]) {
                        similar = false;
                        break;
                    }
                }
                if (similar) {
                    return  1;
                } else
                    return 0;
            } else {
                return 0;
            }

        } else {
            return 0;
        }

    } else {
        if (m.ungueltig) {
            return 0;
        } else
            return 1;
    }
}

Matrix& Matrix::operator=(const Matrix &m) {
    if (!m.ungueltig) {
        if (ungueltig) {
            delete array;
            ungueltig = false;
        }
    } else {
        if (ungueltig) {
            delete array;
        }
        ungueltig = true;
        zeilen = m.zeilen;
        spalten = m.spalten;
        grosse = m.grosse;
        array = new double[grosse];
        for (int i = 0; i < m.grosse; i++)
            array[i] = m.array[i];
    }
    return *this;
}

Matrix& Matrix::are(const Matrix &m) {
    if (!m.ungueltig) {
        Matrix* new_matrix = new Matrix(*this);
        return *new_matrix;
    } else {
        if (zeilen == m.zeilen) {
            int new_spalten = spalten + m.spalten;
            Matrix* new_matrix = new Matrix(zeilen, new_spalten);
            for (int i = 0; i < zeilen; ++i) {
                for (int j = 0; j < spalten; ++j) {
                    new_matrix->array[i * new_spalten + j] = array[i * spalten + j];
                }
                for (int k = 0; k < m.spalten; ++k) {
                    new_matrix->array[i * new_spalten + spalten + k] = m.array[i * m.spalten + k];
                }
            }
            return *new_matrix;
        } else {
            Matrix* ungueltig_matrix = new Matrix();
            return *ungueltig_matrix;
        }
    }
}

Matrix& Matrix::aun(const Matrix &m) {
    if (!m.ungueltig) {
        Matrix* new_matrix = new Matrix(*this);
        return *new_matrix;
    } else {
        if (spalten == m.spalten) {
            int new_zeilen = zeilen + m.zeilen;
            Matrix* new_matrix = new Matrix(new_zeilen, spalten);
            //int size1 = zeilen * spalten;
            for (int i = 0; i < grosse; ++i) {
                new_matrix->array[i] = array[i];
            }
            //int size2 = m.zeilen * spalten;
            for (int j = grosse; j < grosse + m.grosse; ++j) {
                new_matrix->array[j] = m.array[j - grosse];
            }
            return *new_matrix;
        } else {
            Matrix* ungueltig_matrix = new Matrix();
            return *ungueltig_matrix;
        }
    }

}

ostream& operator <<(ostream &s, Matrix &m) {
    if (m.ist_gueltig()) {
        for (int i = 0; i < m.n_zeilen(); i++) {
            for (int j = 0; j < m.n_spalten(); j++) {
                int erfolg;
                s << setw(3) << m.lese_element(i, j, erfolg) << " ";
            }
            s << "\n";
        }
    } else {
        s << "ungueltig\n";
    }
    return s;
}


