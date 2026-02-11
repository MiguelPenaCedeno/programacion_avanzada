#include <iostream>
#include <string>
using namespace std;

struct edicion {
    string id;
    string fecha_publicacion;
    string tema;
    int tipo_edicion;      
    int cantidad_paginas;
    int estado_edicion;    
    string formato_asignado;
    string editor_asignado;
};

struct formato {
    string nombre_formato;
    int capacidad_maxima;
    int cantidad_formatos;
};

struct editor {
    string nombre;
    string formatos[5];
    int num_formatos;
    int estado_disponibilidad;
    int tipos_edicion;
};

void registrarDatosIniciales(edicion ediciones[], int &nEdiciones, formato formatos[],
int &nFormatos, editor editores[], int &nEditores);

bool seleccionarEditor(editor editores[], int nEditores,
string nombreFormato, int tipoEdicion, string &nombreEditor);

int iniciarProduccion(edicion ediciones[], int nEdiciones,
formato formatos[], int nFormatos, editor editores[], int nEditores);

int main() {
    edicion Ediciones[30];
    formato Formatos[10];
    editor Editores[5];

    int nEdiciones = 0;
    int nFormatos = 0;
    int nEditores = 0;

    registrarDatosIniciales(Ediciones, nEdiciones,Formatos, nFormatos, Editores, nEditores);

    int descartadas = iniciarProduccion(Ediciones, nEdiciones, Formatos, nFormatos, Editores, nEditores);

    cout << "Total de ediciones descartadas: " << descartadas << endl;

    return 0;
}

void registrarDatosIniciales(edicion ediciones[], int &nEdiciones,formato formatos[], int &nFormatos, editor editores[], int &nEditores) {

    int opcion = 0;

    do {
        cout << "MENU REGISTRO INICIAL" << endl;
        cout << "1. Registrar nueva edicion" << endl;
        cout << "2. Registrar nuevo formato editorial" << endl;
        cout << "3. Registrar nuevo editor" << endl;
        cout << "0. Terminar registro" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            if (nEdiciones >= 30) {
            cout << "Ya se alcanzo el limite de 30 ediciones." << endl;
            continue;
            }

            cout << "Ingrese el ID de la edicion: ";
            cin >> ediciones[nEdiciones].id;

            cout << "Ingrese la fecha de publicacion (dd/mm/aaaa): ";
            cin >> ediciones[nEdiciones].fecha_publicacion;

            cout << "Ingrese el tema principal: ";
            cin >> ediciones[nEdiciones].tema;

            cout << "Por favor seleccione el tipo de edicion." << endl;
            cout << "1. Impresa" << endl;
            cout << "2. Digital" << endl;
            cout << "Opcion: ";
            cin >> ediciones[nEdiciones].tipo_edicion;

        while (ediciones[nEdiciones].tipo_edicion != 1 &&
                   ediciones[nEdiciones].tipo_edicion != 2) {
                cout << "Tipo invalido, intente de nuevo (1 impresa, 2 digital): ";
                cin >> ediciones[nEdiciones].tipo_edicion;
            }

            cout << "Ingrese el numero estimado de paginas: ";
            cin >> ediciones[nEdiciones].cantidad_paginas;

            while (ediciones[nEdiciones].cantidad_paginas < 1) {
                cout << "No puede ser menor a 1, intente de nuevo: ";
                cin >> ediciones[nEdiciones].cantidad_paginas;
            }

            ediciones[nEdiciones].estado_edicion = 1;
            ediciones[nEdiciones].formato_asignado = "";
            ediciones[nEdiciones].editor_asignado = "";

            nEdiciones++;

    } else if (opcion == 2) {
        if (nFormatos >= 10) {
            cout << "Ya se alcanzo el limite de 10 formatos." << endl;
             continue;
        }

            cout << "Nombre del formato: ";
            cin >> formatos[nFormatos].nombre_formato;

            cout << "Capacidad maxima de paginas: ";
            cin >> formatos[nFormatos].capacidad_maxima;
            while (formatos[nFormatos].capacidad_maxima < 1) {
                cout << "Capacidad invalida, intente de nuevo: ";
                cin >> formatos[nFormatos].capacidad_maxima;
            }

            cout << "Cantidad de formatos disponibles: ";
            cin >> formatos[nFormatos].cantidad_formatos;
            while (formatos[nFormatos].cantidad_formatos < 0) {
                cout << "Cantidad invalida, intente de nuevo: ";
                cin >> formatos[nFormatos].cantidad_formatos;
            }

            nFormatos++;

        } else if (opcion == 3) {
            if (nEditores >= 5) {
                cout << "Ya se alcanzo el limite de 5 editores." << endl;
                continue;
            }

            cout << "Nombre del editor: ";
            cin >> editores[nEditores].nombre;

            cout << "Cuantos formatos puede manejar este editor (max 5): ";
            cin >> editores[nEditores].num_formatos;
            if (editores[nEditores].num_formatos > 5)
                editores[nEditores].num_formatos = 5;
            if (editores[nEditores].num_formatos < 0)
                editores[nEditores].num_formatos = 0;

            for (int i = 0; i < editores[nEditores].num_formatos; i++) {
                cout << "Nombre del formato " << (i + 1) << ": ";
                cin >> editores[nEditores].formatos[i];
            }

            cout << "Estado de disponibilidad (1 disponible, 0 no disponible): ";
            cin >> editores[nEditores].estado_disponibilidad;
            while (editores[nEditores].estado_disponibilidad != 0 &&
                   editores[nEditores].estado_disponibilidad != 1) {
                cout << "Valor invalido, ingrese 1 o 0: ";
                cin >> editores[nEditores].estado_disponibilidad;
            }

            cout << "Tipos de edicion que puede supervisar:" << endl;
            cout << "1. Impresa" << endl;
            cout << "2. Digital" << endl;
            cout << "3. Ambas" << endl;
            cout << "Opcion: ";
            cin >> editores[nEditores].tipos_edicion;
            while (editores[nEditores].tipos_edicion < 1 ||
                   editores[nEditores].tipos_edicion > 3) {
                cout << "Opcion invalida, intente de nuevo: ";
                cin >> editores[nEditores].tipos_edicion;
            }

            nEditores++;
        }

    } while (opcion != 0);
}

bool seleccionarEditor(editor editores[], int nEditores,string nombreFormato, int tipoEdicion,
 string &nombreEditor) {

    for (int i = 0; i < nEditores; i++) {
    if (editores[i].estado_disponibilidad == 1) {

            bool tipoOK = false;
            if (editores[i].tipos_edicion == 3) {
                tipoOK = true;
            } else if (editores[i].tipos_edicion == tipoEdicion) {
                tipoOK = true;
            }

            if (!tipoOK) {
                continue;
            }

            bool manejaFormato = false;
            for (int j = 0; j < editores[i].num_formatos; j++) {
                if (editores[i].formatos[j] == nombreFormato) {
                    manejaFormato = true;
                    break;
                }
            }

            if (manejaFormato) {
                nombreEditor = editores[i].nombre;
                editores[i].estado_disponibilidad = 0;
                return true;
            }
        }
    }

    return false;
}

int iniciarProduccion(edicion ediciones[], int nEdiciones,formato formatos[], int nFormatos,
    editor editores[], int nEditores) {

    int descartadas = 0;

    for (int i = 0; i < nEdiciones; i++) {
        if (ediciones[i].estado_edicion != 1) {
        continue;
        }

        int paginas = ediciones[i].cantidad_paginas;

        int indiceFormato = -1;
        int mejorCapacidad = 0;

        for (int j = 0; j < nFormatos; j++) {
            if (formatos[j].cantidad_formatos > 0 &&
                formatos[j].capacidad_maxima >= paginas) {

                if (indiceFormato == -1 ||
                formatos[j].capacidad_maxima < mejorCapacidad) {

                    indiceFormato = j;
                    mejorCapacidad = formatos[j].capacidad_maxima;
                }
            }
        }

        if (indiceFormato == -1) {
            ediciones[i].estado_edicion = 3;
            descartadas++;
            continue;
        }

        string nombreEditor;
        bool okEditor = seleccionarEditor(editores, nEditores,formatos[indiceFormato].nombre_formato, ediciones[i].tipo_edicion,
        nombreEditor);

        if (!okEditor) {
            ediciones[i].estado_edicion = 3;
            descartadas++;
            continue;
        }

        ediciones[i].estado_edicion = 2;
        ediciones[i].formato_asignado = formatos[indiceFormato].nombre_formato;
        ediciones[i].editor_asignado = nombreEditor;
        formatos[indiceFormato].cantidad_formatos--;
    }

    return descartadas;
}
