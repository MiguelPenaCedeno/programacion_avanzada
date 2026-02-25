#include <iostream>
using namespace std;

void intercambiar(float *med1, float *med2, float *med3) {
     *med3 = *med1 + *med2 + *med3; // si med1 = 1, med2 = 2 y med3 = 3, entonces med3 = 6
    *med1 = *med3 - *med1 - *med2; // ahora med1 = 6 - 1 - 2 = 3    
    *med2 = *med3 - *med1 - *med2; // ahora med2 = 6 - 3 - 2 = 1
    *med3 = *med3 - *med1 - *med2; // ahora med3 = 6 - 3 - 1 = 2
 // entonces al final pasan de ser 1, 2, 3 a ser 3, 1, 2
}

float calcularPromedio(float **p1, float **p2, float **p3) {
    float suma = **p1 + **p2 + **p3;
    return suma / 3;
}

void ajustarPromedio(float *promedio, float ***factorCorreccion) {
    *promedio = *promedio * ***factorCorreccion;
}

int main() {
    float medicion1, medicion2, medicion3;
    float factor;

    cout << "Ingrese la medicion 1: ";
    cin >> medicion1;
    cout << "Ingrese la medicion 2: ";
    cin >> medicion2;
    cout << "Ingrese la medicion 3: ";
    cin >> medicion3;
    cout << "Ingrese factor de correccion: ";
    cin >> factor;

    cout << "\nValores originales:" << endl;
    cout << "medicion1 = " << medicion1 << endl;
    cout << "medicion2 = " << medicion2 << endl;
    cout << "medicion3 = " << medicion3 << endl;

    float *p1 = &medicion1;
    float *p2 = &medicion2;
    float *p3 = &medicion3;

    float **pp1 = &p1;
    float **pp2 = &p2;
    float **pp3 = &p3;

    float *pfactor       = &factor;
    float **ppfactor     = &pfactor;
    float ***pppfactor   = &ppfactor;

    intercambiar(p1, p2, p3);

    float promedio = calcularPromedio(pp1, pp2, pp3);

    ajustarPromedio(&promedio, pppfactor);

    cout << "\nValores despues del intercambio:" << endl;
    cout << "medicion1 = " << medicion1 << endl;
    cout << "medicion2 = " << medicion2 << endl;
    cout << "medicion3 = " << medicion3 << endl;

    cout << "Promedio ajustado: " << promedio << endl;

    return 0;
}
