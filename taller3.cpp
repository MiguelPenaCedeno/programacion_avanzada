#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct equipo {
    int codigo;
    char descripcion[40];  
    int anioFabricacion;
    char tipo;
    char estado[30];
    bool operativo;
};

// Funcion para poder inicializar el archivo y ademas ponerle registros vacios pa evitar errores de lectura

void inicializarArchivo(char nombre[], int maxEquipos) {
    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo) {
        archivo.open(nombre, ios::binary | ios::out);
        equipo vacio;
        vacio.codigo = -1;
        vacio.descripcion[0] = '\0';
        vacio.anioFabricacion = 0;
        vacio.tipo = ' ';
        vacio.estado[0] = '\0';
        vacio.operativo = false;
        for (int i = 0; i < maxEquipos; i++) {
            archivo.write(reinterpret_cast<char*>(&vacio), sizeof(equipo));
        }
        archivo.close();
    } else {
        archivo.close();    
    }
}

// Funcion pa registrar un nuevo equipo, con validaciones de codigo y tipo, y evitando sobreescribir registros existentes

void registrarEquipo(char nombre[], int maxEquipos) {

    int codigo;
    cout << "Ingrese el codigo del equipo (1 - " << maxEquipos  << "): ";
    cin >> codigo;

    if (codigo < 1 || codigo > maxEquipos) {
        cout << "El codigo ingresado es invalido\n";
        return;
    }

    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    archivo.seekg((codigo - 1) * sizeof(equipo), ios::beg);

    equipo posicion_codigo;
    archivo.read(reinterpret_cast<char*>(&posicion_codigo), sizeof(equipo));

    if (posicion_codigo.codigo != -1) {
        cout << "La posicion ingresada ya esta ocupada :( \n";
        archivo.close();
        return;
    }

    equipo nuevo;
    nuevo.codigo = codigo;

    cout << "Ingrese la descripcion del equipo: ";
    cin.ignore();
    cin.getline(nuevo.descripcion, 40);

    cout << "Ingrese el año de fabricacion del equipo (en numeros): ";
    cin >> nuevo.anioFabricacion;

    cout << "Ingrese el tipo de equipo ('L' Portatil / 'D' Escritorio / 'S' Servidor): ";
    cin >> nuevo.tipo;
    while (nuevo.tipo != 'L' && nuevo.tipo != 'D' &&  nuevo.tipo != 'S' ) {
        cout << "El valor ingresado no es valido\n";
        cout << "Ingrese el tipo de equipo nuevamente ('L' Portatil / 'D' Escritorio / 'S' Servidor): ";
        cin >> nuevo.tipo;
    }

    cout << "Ingrese el estado del equipo: ";
    cin.ignore();
    cin.getline(nuevo.estado, 30);

    cout << "Ingrese el estado del equipo (0 si esta fuera de uso / 1 si esta en servicio): ";
    int op;
    cin >> op;
    nuevo.operativo = (op == 1);

    archivo.seekp((codigo - 1) * sizeof(equipo), ios::beg);
    archivo.write(reinterpret_cast<char*>(&nuevo), sizeof(equipo));

    cout << "El equipo ha sido registrado exitosamente\n";
    archivo.close();
}



// funcion que simplemente consulta un equipo por su codigo

void consultarEquipo (char nombre[], int maxEquipos) {
    int codigo;
    cout << "Ingrese el codigo del equipo que desea consultar: ";
    cin >> codigo;

    while (codigo < 1 || codigo > maxEquipos) {
        cout << "Codigo invalido, ingreselo nuevamente: ";
        cin >> codigo;    
    }

    ifstream archivo(nombre, ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    archivo.seekg((codigo - 1) * sizeof(equipo), ios::beg);

    equipo consulta;
    archivo.read(reinterpret_cast<char*>(&consulta), sizeof(equipo));

    if (consulta.codigo == -1) {
        cout << "No existe aun un equipo con ese codigo.\n";
        archivo.close();
        return;
    }

    cout << "El equipo con el codigo " << consulta.codigo << " tiene los siguientes atributos: "<< endl;
    cout << "1. Descripcion: " << consulta.descripcion << endl;
    cout << "2. Año de fabricacion: " << consulta.anioFabricacion << endl;
    switch (consulta.tipo) {
        case 'L':
            cout << "3. Tipo de equipo: Portatil" << endl;
            break;
        case 'D':
            cout << "3. Tipo de equipo: Escritorio" << endl;
            break;
        case 'S':
            cout << "3. Tipo de equipo: Servidor" << endl;
            break;
        default:
            cout << "3. Tipo de equipo: Desconocido" << endl;
            break;
    }
    cout << "4. Estado: " << consulta.estado << endl;
    if (consulta.operativo) {
        cout << "5. Disponibilidad: El equipo esta operativo\n";
    } else {
        cout << "5. Disponibilidad: El equipo no esta operativo\n"; 
    }
    archivo.close();
}

// funcino para modificar el estado del equipo en cuestion


void cambiarEstado(char nombre[], int maxEquipos) {
    int codigo;

    cout << "Ingresa el codigo del equipo: ";
    cin >> codigo;

    while (codigo < 1 || codigo > maxEquipos) {
        cout << "El codigo que ha introducido no se corresponde con un registro, ingreselo nuevamente: ";
        cin >> codigo;
    }

    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    archivo.seekg((codigo - 1) * sizeof(equipo), ios::beg);

    equipo cambio;
    archivo.read(reinterpret_cast<char*>(&cambio), sizeof(equipo)); 

    if (cambio.codigo == -1) {
        cout << "Ese ID no contiene equipo.\n";
        archivo.close();
        return;
    }

    if (!cambio.operativo) {
        cout << "No se puede modificar el estado de un equipo que no esta operativo.\n";
        archivo.close();
        return;
    }

    cout << "Estado actual: " << cambio.estado << endl;
    cout << "Ingrese el nuevo estado del equipo: ";
    cin.ignore();
    cin.getline(cambio.estado, 30);

    archivo.seekp((codigo - 1) * sizeof(equipo), ios::beg);
    archivo.write(reinterpret_cast<char*>(&cambio), sizeof(equipo));

    cout << "Estado cambiado.\n";

    archivo.close();
}

// funcion que unicamente muestra los equipos que estan operativos, con su codigo y descripcion

void listarEquipos(char nombre[], int maxEquipos) {
    ifstream archivo (nombre, ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    equipo reg;
    for (int i = 0; i < maxEquipos; i++) {
        archivo.read(reinterpret_cast<char*>(&reg), sizeof(equipo));
        if (!archivo) break;

        if (reg.codigo != -1 && reg.operativo) {
            cout << "Equipo con codigo " << reg.codigo << ": " << endl;
            cout << reg.descripcion << endl;
            cout << reg.anioFabricacion << endl;
            switch (reg.tipo) {
                case 'L':
                    cout << "Tipo de equipo: Portatil" << endl;
                    break;
                case 'D':
                    cout << "Tipo de equipo: Escritorio" << endl;
                    break;
                case 'S':
                    cout << "Tipo de equipo: Servidor" << endl;
                    break;
            }
            cout << reg.estado << endl;
            if (reg.operativo) {
                cout << "Disponibilidad: El equipo esta operativo\n";
            } else {
                cout << "Disponibilidad: El equipo no esta operativo\n";  
            }
        }
    }
    archivo.close();
}

// funcion para pasar a false el booleano de operativo y marcar el equipo como fuera de uso 

void marcarFueradeUso(char nombre[], int maxEquipos) {
    int codigo;
    cout << "Ingrese el codigo del equipo que desea marcar como fuera de uso: ";
    cin >> codigo;

    while (codigo < 1 || codigo > maxEquipos) {
        cout << "Codigo invalido, ingreselo nuevamente: ";
        cin >> codigo;
    }

    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    archivo.seekg((codigo - 1) * sizeof(equipo), ios::beg);

    equipo reg;
    archivo.read(reinterpret_cast<char*>(&reg), sizeof(equipo));

    if (reg.codigo == -1) {
        cout << "No existe un equipo con ese codigo.\n";
        archivo.close();
        return;
    }

    if (!reg.operativo) {
        cout << "El equipo ya estaba fuera de uso.\n";
        archivo.close();
        return;
    }

    reg.operativo = false;

    archivo.seekp((codigo - 1) * sizeof(equipo), ios::beg);
    archivo.write(reinterpret_cast<char*>(&reg), sizeof(equipo));

    cout << "Equipo marcado como fuera de uso.\n";
    archivo.close();
}

int main () {
    char archivoNombre[20] = "equipos.bin";
    int maxEquipos;
    int menu;

    cout << "Ingrese la cantidad maxima de equipos: ";
    cin >> maxEquipos;

    inicializarArchivo(archivoNombre, maxEquipos);

    do {
        cout << "\nMENU" << endl;
        cout << "Oprima '1' si desea registrar un equipo nuevo." << endl;
        cout << "Oprima '2' si desea consultar un equipo por su codigo." << endl;
        cout << "Oprima '3' si desea actualizar el estado del equipo. " << endl;
        cout << "Oprima '4' si desea listar los equipos operativos." << endl;
        cout << "Oprima '5' si desea marcar un equipo como fuera de uso. " << endl;
        cout << "Oprima '0' para salir." << endl;
        cout << "A continuacion elija la opcion que necesite ejecutar: ";
        cin >> menu;

        switch (menu) {
            case 1:
                registrarEquipo(archivoNombre, maxEquipos);   
                break;
            case 2:
                consultarEquipo(archivoNombre, maxEquipos); 
                break;
            case 3:
                cambiarEstado(archivoNombre, maxEquipos);
                break;
            case 4:
                listarEquipos(archivoNombre, maxEquipos);
                break;
            case 5: 
                marcarFueradeUso(archivoNombre, maxEquipos);
                break;
            case 0:
                cout << "Saliendo del programa" << endl;
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    } while (menu != 0);

    return 0;
}
