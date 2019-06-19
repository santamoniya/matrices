// pvl_main.cpp
// Informatik 2, PVL, Sommersemester 2019
// Hauptdatei
// Bei Abgabe hinzufügen: Vorname, Name, Matrikelnummer

#include <iostream>
#include "matrix.h"
using namespace std;


void belegen_m1(Matrix &m)
{
    double cmat[5][3] = { { 1.0, 0.0, 0.0 },
                          { 0.0, 2.0, 0.0 },
                          { 0.0, 0.0, 3.0 },
                          { 4.0, 0.0, 0.0 },
                          { 0.0, 5.0, 0.0 }
    };
    for (int z = 0; z < m.n_zeilen(); z++)
        for (int s = 0; s < m.n_spalten(); s++)
            if (m.setze_element(z, s, cmat[z][s]) == 0)
            {
                cout << "Fehler bei belegen_m1(), Abbruch" << endl;
                exit(EXIT_FAILURE);
            }


}
void belegen_m2(Matrix &m)
{
    double cmat[3][5] = { { 1.0, 0.0, 0.0, 4.0, 0.0 },
                          { 0.0, 2.0, 0.0, 0.0, 5.0 },
                          { 0.0, 0.0, 3.0, 0.0, 0.0 }
    };
    for (int z = 0; z < m.n_zeilen(); z++)
        for (int s = 0; s < m.n_spalten(); s++)
            if (m.setze_element(z, s, cmat[z][s]) == 0)
            {
                cout << "Fehler bei belegen_m2(), Abbruch" << endl;
                exit(EXIT_FAILURE);
            }

}

Matrix erzeuge_quadr_testmatrix(int n)
{
    Matrix test(n, n);
    for (int z = 0; z < test.n_zeilen(); z++)
        for (int s = 0; s < test.n_spalten(); s++)
            if (test.setze_element(z, s, z*test.n_zeilen()+s) == 0)
            {
                cout << "Fehler bei erzeuge_quadr_testmatrix(), Abbruch" << endl;
                exit(EXIT_FAILURE);
            }
    return test;
}


int main()
{
    Matrix m1(5,3), m2(3,5);
    Matrix m3, m4, m5, m6 ,m7;


    belegen_m1(m1);

    belegen_m2(m2);

    cout<<"m1:"<<endl<<m1<<endl;
    cout<<"m2:"<<endl<<m2<<endl;

    m3 = m1.transposition();

    cout<<"m3= m1.transposition():"<<endl<<m3<<endl;

    if (m3.transposition() == m1 )
    {
        cout<<"Zweifache Transposition ergibt wieder die Originalmatrix."<<endl;
    }
    else
    {
        cout << "Nach zweifacher Transposition ergibt sich keine Originalmatrix, Fehler in Methode transposition()" << endl;
        exit(EXIT_FAILURE);

    }

    m3 = m3.transposition();
    cout<<"m3= m3.transposition():"<<endl<<m3<<endl;

    m4 = m1 + m3;

    cout<<"m4 = m1+m3:"<<endl<<m4<<endl;;

    m5 = m1 * m2;

    cout<<"m5=m1*m2:"<<endl<<m5<<endl;

    m6 = m2 * m1;

    cout<<"m6=m2*m1:"<<endl<<m6<<endl;

    m7 = m5 * m6;

    cout << "m7=m5*m6:" << endl << m7 << endl;

    Matrix v1(1, 10), v2(10, 1), s;
    for (int i = 0; i < v1.n_spalten(); i++)
        v1.setze_element(0, i, (double)i);
    for (int i = 0; i < v2.n_zeilen(); i++)
        v2.setze_element(i, 0, (double)i);
    s = v1*v2;


    cout << s << endl;

    // (1x1)‐Matrix Konstruktor
    Matrix ew(0.815);
    int e;
    cout << "eine " <<ew.n_zeilen()<<" x "<< ew.n_spalten()<<" Matrix mit Wert:"<<
         ew.lese_element(0, 0, e)<<endl;

    //  Methoden die es zulassen, eine Matrix rechtseitig,
    // bzw. unten durch eine weitere Matrix zu erweitern
    Matrix n1 = (Matrix(1.0).are(Matrix(2.0))).aun((Matrix(3.0)).are(Matrix(4.0)));
    cout << n1 << endl;

    return EXIT_SUCCESS;
}