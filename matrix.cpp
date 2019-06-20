#include <iomanip>
#include <algorithm>
#include "matrix.h"

Matrix::Matrix() {
    gueltig = false;
}

Matrix::Matrix(double val) {
    gueltig = true;
    zeilen = 1, spalten = 1;
    if (val != 0) {
        rows = vector<int>(1, 0);
        cols = vector<int>(1, 0);
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
        gueltig = true;
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

int Matrix::istNull(int z, int s) {
    if(find_position(z, s) != -1) {
        return 0;
    } else {
        return 1;
    }
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
        int pos = find_position(zeile, spalte);
        if (pos != -1) {
            if (wert < 1e-10 && wert >= -1e-10) {
               rows.erase(rows.begin() + pos);
               cols.erase(rows.begin() + pos);
               vals.erase(vals.begin() + pos);
            } else {
                vals[pos] = wert;
            }
        } else {
            if (wert >= 1e-10 || wert <-1e-10) {
                auto upper_row = upper_bound(rows.begin(), rows.end(), zeile);
                auto lower_row = find(rows.begin(), rows.end(), zeile);
                int upper_row_index = (int)distance(rows.begin(), upper_row);
                int lower_row_index = (int)distance(rows.begin(), lower_row);
                if (lower_row == rows.end()) {
                    rows.insert(upper_row, zeile);
                    cols.insert(cols.begin() + upper_row_index, spalte);
                    vals.insert(vals.begin() + upper_row_index, wert);
                } else {
                    auto upper_col = upper_bound(cols.begin() + lower_row_index, cols.begin() + upper_row_index, spalte);
                    int upper_col_index = (int)distance(cols.begin(), upper_col);
                    rows.insert(rows.begin() + upper_col_index, zeile);
                    cols.insert(upper_col, spalte);
                    vals.insert(vals.begin() + upper_col_index, wert);
                }
            }
        }
    }
    return 1;
}

int Matrix::find_position(int z, int s) {
    auto first_row_entrance = find(rows.begin(), rows.end(), z);
    if (first_row_entrance != rows.end()) {
        auto last_row_entrance = upper_bound(rows.begin(), rows.end(), z);
        int first_row_index = (int)std::distance(rows.begin(), first_row_entrance);
        int last_row_index = (int)std::distance(rows.begin(), last_row_entrance);
//        auto col_entrance = find(cols.begin() + first_row_index, cols.begin() + last_row_index, s);
        int i;
        for (i = first_row_index; i < last_row_index; ++i) {
            if(cols[i] == s) break;
        }
        if (i < last_row_index ) {
            return i;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int Matrix::n_zeilen() {
    return zeilen;
}

int Matrix::n_spalten() {
    return spalten;
}

int Matrix::ist_gueltig() {
    return gueltig;
}

double Matrix::lese_element(int zeile, int spalte, int &erfolg) {
    if (zeile < 0 || spalte < 0 || zeile >= zeilen || spalte >= spalten) {
        erfolg = 0;
        return 0;
    } else {
        erfolg = 1;
        int pos = find_position(zeile, spalte);
        if (pos == -1) {
            return 0;
        } else {
            return vals[pos];
        }
    }
}

Matrix Matrix::transposition() {
    Matrix m(spalten, zeilen);
    for (int col = 0; col < spalten; ++col) {
        int index = 0;
        while (index < vals.size()) {
            if (cols[index] == col) {
                m.cols.push_back(rows[index]);
                m.rows.push_back(cols[index]);
                m.vals.push_back(vals[index]);
            }
            index++;
        }
    }
    return m;
}

Matrix Matrix::operator+(Matrix &m) {
    if (gueltig && m.gueltig && zeilen != m.zeilen && spalten != m.spalten) {
        Matrix ung;
        return ung;
    } else {
        Matrix sum(zeilen, spalten);
        int index = 0, mindex = 0;
        while (index < vals.size() && mindex < m.vals.size()) {
            if (rows[index] == m.rows[mindex]) {
                if(cols[index] == m.cols[mindex]) {
                    double s = vals[index] + m.vals[mindex];
                    if ( s >= 1e-10 || s < -1e-10) {
                        sum.rows.push_back(rows[index]);
                        sum.cols.push_back(cols[index]);
                        sum.vals.push_back(s);
                    }
                    index++;
                    mindex++;
                } else {
                    sum.rows.push_back(rows[index]);
                    if (cols[index] < m.cols[mindex]) {
                        sum.cols.push_back(cols[index]);
                        sum.vals.push_back(vals[index]);
                        index++;
                    } else {
                        sum.cols.push_back(m.cols[mindex]);
                        sum.vals.push_back(m.vals[mindex]);
                        mindex++;
                    }
                }
            } else {
                if(rows[index] < m.rows[mindex]) {
                    sum.rows.push_back(rows[index]);
                    sum.cols.push_back(cols[index]);
                    sum.vals.push_back(vals[index]);
                    index++;
                } else {
                    sum.rows.push_back(m.rows[mindex]);
                    sum.cols.push_back(m.cols[mindex]);
                    sum.vals.push_back(m.vals[mindex]);
                    mindex++;
                }
            }
        }
        if (index >= vals.size()) {
            for (int i = mindex; i < m.vals.size(); ++i) {
                sum.rows.push_back(m.rows[i]);
                sum.cols.push_back(m.cols[i]);
                sum.vals.push_back(m.vals[i]);
            }
        } else {
            for (int i = index; i < vals.size(); ++i) {
                sum.rows.push_back(rows[i]);
                sum.cols.push_back(cols[i]);
                sum.vals.push_back(vals[i]);
            }
        }

        return sum;
    }
}

int Matrix::operator==(Matrix &m) {
    if (gueltig) {
        if (m.gueltig) {
            if (zeilen == m.zeilen && spalten == m.spalten) {
                if (m.rows == rows &&
                        m.cols == cols &&
                        m.vals == vals) {
                return 1;
                } else {
                    return 0;
                }
            }
        } else {
            return 0;
        }

    } else {
        if (m.gueltig) {
            return 0;
        } else
            return 1;
    }
}

Matrix &Matrix::are(const Matrix &m) {
    if (m.zeilen == zeilen) {
        Matrix* neu_m = new Matrix(zeilen, spalten + m.spalten);
        neu_m->rows = rows;
        neu_m->cols = cols;
        neu_m->vals = vals;
        for (int i = 0; i < m.vals.size(); ++i) {
            auto it = find(neu_m->rows.begin(), neu_m->rows.end(), m.rows[i]);
            auto upper = upper_bound(neu_m->rows.begin(), neu_m->rows.end(), m.rows[i]);
            if (it != neu_m->rows.end()) {
                int index = (int)std::distance(neu_m->rows.begin(), upper);
                neu_m->rows.insert(upper, m.rows[i]);
                neu_m->cols.insert(neu_m->cols.begin() + index, m.cols[i] + spalten);
                neu_m->vals.insert(neu_m->vals.begin() + index, m.vals[i]);
            }

        }
        return *neu_m;
    } else {
        Matrix* neu_m = new Matrix();
        return *neu_m;
    }

}

Matrix &Matrix::aun(const Matrix &m) {
    if(m.spalten == spalten) {
        Matrix* neu_m = new Matrix(zeilen + m.zeilen, spalten);
        neu_m->rows = rows;
        neu_m->cols = cols;
        neu_m->vals = vals;
        vector<int> rows1(m.rows);
        for (int i = 0; i < m.rows.size(); ++i) {
            rows1[i] += zeilen;
        }
        neu_m->rows.reserve(rows.size() + m.rows.size());
        neu_m->cols.reserve(cols.size() + m.cols.size());
        neu_m->vals.reserve(vals.size() + m.vals.size());

        neu_m->rows.insert(neu_m->rows.end(), rows1.begin(), rows1.end());
        neu_m->cols.insert(neu_m->cols.end(), m.cols.begin(), m.cols.end());
        neu_m->vals.insert(neu_m->vals.end(), m.vals.begin(), m.vals.end());

        return *neu_m;

    } else {
        Matrix* neu_m = new Matrix();
        return *neu_m;
    }
}

Matrix Matrix::operator*(Matrix &m) {
    if (gueltig && m.gueltig && spalten != m.zeilen) {
        Matrix ung;
        return ung;
    } else {
        Matrix neu(zeilen, m.spalten);
        Matrix transp;
        transp = m.transposition();

        for (int row_number = 0; row_number < zeilen; ++row_number) {
            for (int col_number = 0; col_number < transp.zeilen; ++col_number) {
                auto lower_ptr_row_nuber = find(rows.begin(), rows.end(), row_number);
                if (lower_ptr_row_nuber != rows.end()) {
                    auto upper_ptr_row_number = upper_bound(rows.begin(), rows.end(), row_number);
                }
            }
        }

        return neu;
    }
}

ostream &operator<<(ostream &s, Matrix &m) {
    int erfolg;
    if (m.ist_gueltig()) {
        for (int i = 0; i < m.n_zeilen(); i++) {
            for (int j = 0; j < m.n_spalten(); j++) {
                s << setw(3) << m.lese_element(i, j, erfolg) << " ";
            }
            s << endl;
        }
    } else {
        s << "ungueltig\n";
    }
    return s;
}
