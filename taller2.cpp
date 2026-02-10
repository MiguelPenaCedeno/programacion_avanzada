#include <iostream>
#include <cstring>
#include <string>

using namespace std;

//la funcion cuenta la longitud de una cadena char
//recorre hasta encontrar el caracter fin de cadena \0
int longitudCadena(char texto[]) {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
    }
    return i;
}

//suma el total de caracteres de todas las frases de un grupo
int contarCaracteresGrupo(char frases[][100], int nFrases) {
    int total = 0;
    for (int frase = 0; frase < nFrases; frase++) {
        total += longitudCadena(frases[frase]);
    }
    return total;
}

//devuelve la posicion de la frase mas larga del grupo
int indiceFraseMasLarga(char frases[][100], int nFrases) {
    int indice = 0;
    int mayor = (nFrases > 0) ? longitudCadena(frases[0]) : 0;

    for (int frase = 1; frase < nFrases; frase++) {
        int len = longitudCadena(frases[frase]);
        if (len > mayor) {
            mayor = len;
            indice = frase;
        }
    }
    return indice;
}

int main() {
    int nGrupos;
    int nFrasesPorGrupo;

    cout << "Cuantos grupos deseas registrar? ";
    cin >> nGrupos;

    cout << "Cuantas frases por grupo? ";
    cin >> nFrasesPorGrupo;

    cin.ignore(10000, '\n');

    if (nGrupos <= 0 || nFrasesPorGrupo <= 0) {
        cout << "Valores invalidos. Deben ser mayores que 0." << endl;
        return 0;
    }

    char textos[10][50][100];

    if (nGrupos > 10 || nFrasesPorGrupo > 50) {
        cout << "Excede el limite permitido (max 10 grupos, 50 frases por grupo)." << endl;
        return 0;
    }

    for (int grupo = 0; grupo < nGrupos; grupo++) {
        cout << endl;
        cout << "Grupo " << (grupo + 1) << ":" << endl;

        for (int frase = 0; frase < nFrasesPorGrupo; frase++) {
            cout << "Frase " << (frase + 1) << ": ";
            cin.getline(textos[grupo][frase], 100);
        }
    }

    cout << endl;
    cout << "Resultados:" << endl;

    int grupoMayorTexto = 0;
    int mayorTotal = -1;

    for (int grupo = 0; grupo < nGrupos; grupo++) {
        int indice = indiceFraseMasLarga(textos[grupo], nFrasesPorGrupo);
        int total = contarCaracteresGrupo(textos[grupo], nFrasesPorGrupo);

        cout << endl;
        cout << "Grupo " << (grupo + 1) << endl;
        cout << "Frase mas larga: " << textos[grupo][indice] << endl;
        cout << "Total de caracteres: " << total << endl;

        if (total > mayorTotal) {
            mayorTotal = total;
            grupoMayorTexto = grupo;
        }
    }

    cout << endl;
    cout << "El grupo que aporta mas texto es el grupo " << (grupoMayorTexto + 1)
         << " con " << mayorTotal << " caracteres." << endl;

    return 0;
}