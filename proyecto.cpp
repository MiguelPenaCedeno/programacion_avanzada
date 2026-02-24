#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Equipo {
    int codigo_equipo;
    char nombre[30];
    char laboratorio[30];

};

struct Usuario {
    int codigo_usuario;
    char nombre_completo[40];
    char programa_academico[40];
    int semestre;
};

struct SesionUso{
    int codigo_sesion;
    int codigo_equipo;
    int codigo_usuario;
    char fecha[10];
    int duracion;
    char observaciones[30];
    char penalizacion[30];
};

void cargarEquipos(char nombre[]);


int main () {
int menu;

char archivoNombre[30] = "equipos.bin";

Usuario usuarios[10];

Equipo equipos[50];

SesionUso sesiones[50];


cout << "Ingrese la opcion que le gustaria ejecutar: ";
cin >> menu;

do {
    switch (menu) {

        case 1:

        cargarEquipos();
        cout << "Equipos cargados exitosamente!";
        break;

        case 2:

        cargarUsuarios();
        cout << "Usuarios cargados exitosamente!";
        break;

        case 3:
        consultarEstado;
        break;

        case 4:

        programarSesion();
        cout << "Sesion programada exitosamente!";
        break;

        case 5:

        registrarCierre();
        cout << "Cierre de sesión registrado exitosamente!";
        break;

        case 6:
        generarInforme();
        cout << "Informe generado exitosamente!";

        case 7: 
        generarRanking();
        break;

        default:
        cout << "El valor ingresado no coincide con un valor valido."
        break;

    }
} while (menu != 0);

}

void cargarEquipos(char nombre[]) {

    cout << "Ingrese el nombre del archivo que desea cargar:";
    cin >> nombre;

    
    fstream archivo(nombre, ios::binary | ios::in | ios::out);


};