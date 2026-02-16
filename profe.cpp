#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void leerArchivo(string nomA, char palabras[][100], int &nPalabras) {
    ifstream archivo(nomA);
    while(archivo.getline(palabras[nPalabras], 100)) {
        nPalabras++;
    }
    archivo.close();
}

void validarDups(string nomB, char palabras[][100], int nPalabras) {
    ofstream salida(nomB);
    for (int i = 0; i < nPalabras; i++) {
        bool dup = false;
        int l = strlen(palabras[i]);
        for (int j = 0; j < l; j++) {
            for (int k = j + 1; k < l; k++) {
                if (palabras[i][j] == palabras[i][k]) {
                    dup = true;
                    break;
                }
            }
        }
        if (dup) {
            salida << palabras[i] << endl;
        }
    }
    salida.close();
}

int main( ) {
    char palabras[20][100] = {" "};
    int nPalabras = 0;
    leerArchivo("palabras.txt", palabras, nPalabras);
    validarDups("duplicadas.txt", palabras, nPalabras);
    return 0;

}