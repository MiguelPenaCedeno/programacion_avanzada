#include <iostream>
#include <cstring>
#include <fstream>
#include <string>


// Ejercicio: "Palabras con letras duplicadas no consecutivas"
// Tienes un archivo llamado palabras.txt. Cada linea contiene una sola palabra sin espacios
// Tu tarea es:
// 1. Leer todas las lineas del archivo
// 2. Verificar si alguna letra aparece mas de una vez, aunque no sea consecutiva
// 3. Si la palabra tiene al menos una letra duplicada, escribela en un archivo llamado duplicadas.txt

bool tieneDuplicados(char palabra[]);

    //lectura = archivo.getline(palabra, 100);

using namespace std;

int main() {

    ofstream archivo("palabras.txt");

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return 0;
    }

    archivo << "autonomia" << endl;
    archivo << "teclado" << endl;
    archivo << "banana" << endl;
    archivo << "sol" << endl;
    archivo << "computadora" << endl;
    archivo.close();

    char palabra[100];

    ifstream entrada("palabras.txt");
    ofstream salida("duplicadas.txt");  

    while(entrada.getline(palabra, 100)) {
        if (tieneDuplicados(palabra)) {
            salida << palabra << endl;
        }  
    }


    ifstream lectura("duplicadas.txt");
    while(lectura.getline(palabra, 100)) {
        cout << palabra << endl;
    }

    entrada.close();
    salida.close();

    return 0;

}


bool tieneDuplicados(char palabra[]) {
    for (int i = 0; i < strlen(palabra); i++) {
        for(int j = i + 1; j < strlen(palabra); j++) {
            if(palabra[i] == palabra[j])
            return true;
        }
    }
    return false;
}