#include <iostream>
#include <string>

using namespace std;

struct Edicion {
    char codigo[30];
    char fecha_publicacion[10];
    char tema_principal[30];
    char tipo_edicion;
    int cantidad_paginas;
    int estado; // 1 para pendiente, 2 para produccion,
    // 3 para descartada

};

struct Formato {
    char nombre[30];
    int capacidad;
    int cantidad_formatos;
};

struct Editor {
    char nombre[30];
    Formato formatos[5];
    int estado;
    char tipo_edicion;

};

void registrarDatosIniciales ();

bool seleccionarEditor();


int main () {

    Edicion ediciones[30];
    Formato formatos[10];
    Editor editores[5];
    int menu;

    do {
        cout << "Bienvenido al programa de gestion de ediciones editoriales";
        cout << "\nIngrese 1 para registrar los datos iniciales\n";
        cout << "Ingrese 2 para seleccionar un editor disponible\n";
        cout << "Ingrese 3 para iniciar produccion";
        cout << "\nIngrese su eleccion: ";
        cin >> menu;

        switch (menu) {
            case 1: 
            registrarDatosIniciales();
            break;

            case 2:

        }
    } while (menu != 0);
}