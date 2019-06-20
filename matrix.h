// matrix.h
#include <iostream>
#include <vector>

using namespace std;

/* ---------------------------------------------------------------------------- */
/* PVL Informatik 2 im Sommersemester 2019                                      */
/* Die Klasse Matrix ist zu vervollstaendigen, damit das                        */
/* Hauptprogramm pvl_main.cpp übersetzt und ausgeführt werden kann.             */
/* Es wird die Erstellung einer Datei matrix.cpp mit der Implementiertung       */
/* der enstsprechenden Methoden und Operatoren empfohlen.                       */
/* Bitte beachten Sie auch die zusätzlichen Teilaufgaben, die abhängig von Ihrer*/
/* Maktrikelnummer in Varianten zu lösen sind.                                   */
/* ---------------------------------------------------------------------------- */


// Bei Abgabe hinzufügen: Vorname, Name, Matrikelnummer

class Matrix
{
private:
    // Setzen Sie hier die Datenelemente
    // der Klasse ein
    int zeilen, spalten;
    bool gueltig;
    vector<int> rows;
    vector<int> cols;
    vector<double> vals;
    int istNull(int z, int s);
    int find_position(int z, int s);

public:
    Matrix();
    Matrix(double val);
    Matrix(int zeilen, int spalten);
    Matrix(Matrix &m);				  // Copy-Konstruktur
    ~Matrix();

    Matrix& operator = (const Matrix &m);    // Zuweisungsoperator

    // Methode setze_element(): setzt wert an angegebener Zeile und Spalte
    // Rückgabe 1 wenn erfolgreich, Rückgabe 0 falls Zeile und Spalte ausserhalb
    // des gültigen Bereichs liegt
    int setze_element(int zeile, int spalte, double wert);


    // Methode lese_element(): gibt Wert von angegebener Zeile und Spalte zurück.
    // Falls Zeile und Spalte ausserhalb des gültigen Bereichs liegt, dann Rückgabe von 0
    // und erfolg 0.
    // erfolg signalisiert einen gültigen zurückgegebenen Wert mit 1.
    double lese_element(int zeile, int spalte, int &erfolg);

    // Methode gueltig gibt 0 (für ungültig) zurück, wenn das Matrixobjekt durch eine unzulässige
    // mathematische Operation entstanden ist, bespielsweise durch Addition von Matrizen unterschiedlicher Größe,
    // sonst Rückgabe 1
    int ist_gueltig();

    // Methoden n_zeilen() und n_spalten() geben die jeweilige Anzahl der Zeilen und Spalten zurück
    int n_zeilen();
    int n_spalten();

    // Mathematische Operationen
    Matrix transposition();
    Matrix operator +(Matrix &m);
    Matrix operator *(Matrix &m);

    // Vergleichsoperator
    int operator == (Matrix &m);
//
//    // e3
    Matrix& are(const Matrix &m);
    Matrix& aun(const Matrix &m);
};

ostream& operator <<(ostream &s, Matrix &m);