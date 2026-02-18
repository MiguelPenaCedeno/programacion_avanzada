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

void inicializarArchivo(char nombre[], int maxEquipos) {
    // Implementar la función para inicializar el archivo con registros vacíos
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
    }
    archivo.close();
}

void registrarEquipo(char nombre[], int maxEquipos) {
    // Implementar la función para registrar un equipo
    int codigo;
    cout << "Ingrese el codigo del equipo (1 - " << maxEquipos  << "): ";
    cin >> codigo;

    if (codigo < 0 || codigo > maxEquipos) {
        cout << "El codigo ingresado es invalido";
        return;
    }

    fstream archivo(nombre, ios::binary | ios::in | ios::out);

    archivo.seekg(codigo * sizeof(equipo), ios::beg);

    equipo posicion_codigo;
    archivo.read(reinterpret_cast<char*>(&posicion_codigo), sizeof(equipo));

    if (posicion_codigo.codigo == -1) {
        cout << "La posicion ingresada ya esta ocupada :( ";
        return;
    }

    equipo nuevo;
    nuevo.codigo = codigo;

    cout << "Ingrese la descripción del equipo: ";
    cin.ignore ();
    cin.getline(nuevo.descripcion, 30);

    cout << "Ingrese el año de fabricación del equipo (en numeros): ";
    cin >> nuevo.anioFabricacion;

    cout << "Ingrese el tipo de equipo ('L' Portatil / 'D' Escritorio / 'S' Servidor)";
    cin >> nuevo.tipo;
    while (nuevo.tipo != 'L' && nuevo.tipo != 'D' &&  nuevo.tipo != 'S' ) {
        cout << "El valor ingresado no es válido" << endl;
        cout << "Ingrese el tipo de equipo nuevamente ('L' Portatil / 'D' Escritorio / 'S' Servidor)";
        cin >> nuevo.tipo;
    }

    cout << "Ingrese el estado del equipo";
    cin >> nuevo.estado;

    cout << "Ingrese el estado del equipo (0 si está fuera de uso / 1 si está en servicio)";
    cin >> nuevo.operativo;

    archivo.seekp(codigo * sizeof(equipo), ios::beg);
    archivo.write(reinterpret_cast<char*>(&nuevo), sizeof(equipo));

    cout << "El equipo ha sido registrado exitosamente";
    archivo.close();

}

void consultarEquipo (char nombre[], int maxEquipos) {
    int codigo;
    cout << "Ingrese el codigo del equipo que desea consultar: ";
    cin >> codigo;

    while (codigo < 0 || codigo >= maxEquipos) {
        cout << "Codigo inválido, ingreselo nuevamente: ";
        cin >> codigo;    
    }

    ifstream archivo(nombre, ios::binary);

    archivo.seekg(codigo * sizeof(equipo), ios::beg);

    equipo consulta;

    archivo.read(reinterpret_cast<char*>(&consulta), sizeof(equipo));

    while (consulta.codigo == -1) {
        cout << "No existe aún un equipo con ese codigo, intente nuevamente: ";
        cin >> consulta.codigo;
    } 
    if (consulta.codigo != -1) {
        cout << "El equipo con el codigo " << consulta.codigo << " tiene los siguientes atributos: "<< endl;
        cout << "1. Descripción: " << consulta.descripcion << endl;
        cout << "2. Año de fabricación: " << consulta.anioFabricacion << endl;
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
        }
        cout << "4. Estado: " << consulta.estado << endl;
        if (consulta.operativo) {
            cout << "5. Disponibilidad: El equipo está operativo";
        } else {
            cout << "5. Disponibilidad: El equipo no está operativo"; 
        }
    }
    archivo.close();
}

void cambiarEstado(char nombre[], int maxEquipos) {
    int codigo;

    cout << "Ingresa el codigo del equipo: ";
    cin >> codigo;

    while (codigo < 0 || codigo >= maxEquipos) {
        cout << "El codigo que ha introducido no se corresponde con un registro, ingreselo nuevamente: ";
        cin >> codigo;
    }

    fstream archivo(nombre, ios::binary | ios::in | ios::out);

    archivo.seekg(codigo * sizeof(equipo), ios::beg);

    equipo cambio;
    archivo.read(reinterpret_cast<char*>(&cambio), sizeof(equipo));

    if (cambio.codigo == -1) {
        cout << "Ese ID no contiene vehiculo.\n";
        archivo.close();
        return;
    }

    cambio.operativo = !cambio.operativo;

    archivo.seekp(codigo * sizeof(equipo), ios::beg);
    archivo.write(reinterpret_cast<char*>(&cambio), sizeof(equipo));

    cout << "Estado cambiado.\n";

    archivo.close();
}


void listarEquipos(char nombre[], int maxEquipos) {
    
    ifstream archivo (nombre, ios::binary);

    equipo equipo[maxEquipos];
    for (int i = 0; i < maxEquipos; i++) {
        archivo.read(reinterpret_cast<char*>(&equipo[i]), sizeof(equipo));
    }

    for (int i = 0; i < maxEquipos; i++) {
        cout << "Equipo con codigo " << i << ": " << endl;
        cout << equipo[i].descripcion << endl;
        cout << equipo[i].anioFabricacion << endl;
        switch (equipo[i].tipo) {
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
        cout << equipo[i].estado << endl;
        if (equipo[i].operativo) {
            cout << "Disponibilidad: El equipo está operativo";
        } else {
            cout << "Disponibilidad: El equipo no está operativo";  
        }
    }   
    archivo.close();
}

void marcarFueradeUso(char nombre[], int maxEquipos) {
    int codigo;
    cout << "Ingrese el codigo del equipo que desea marcar como fuera de uso: ";
    cin >> codigo;



}
    // Implementar la función para marcar un equipo como fuera de uso


int main () {

    char archivo[20] = "equipos.bin";
    int maxEquipos = 0;
    int menu = 0;

    inicializarArchivo(archivo,maxEquipos);

    cout << "MENU" << endl;
    
    cout << "Oprima '1' si desea registrar un equipo nuevo." << endl;
    cout << "Oprima '2' si desea consultar un equipo por su código." << endl;
    cout << "Oprima '3' si desea actualizar el estado del equipo. " << endl;
    cout << "Oprima '4' si desea listar los equipos operativos." << endl;
    cout << "Oprima '5' si desea marcar un equipo como fuera de uso. " << endl;
    cout << "A continuación elija la opción que necesite ejecutar: ";
    cin >> menu;
    
    cout << "Ingrese la cantidad maxima de equipos: ";
    cin >> maxEquipos;
do {
    switch (menu) {
        case 1:
            
            registrarEquipo(archivo, maxEquipos);   
            break;
        case 2:
            consultarEquipo(archivo, maxEquipos); 
            cout << "Consulta realizada exitosamente!" << endl;
            break;
        case 3:
            cambiarEstado(archivo, maxEquipos);
            cout << "Estado del equipo cambiado exitosamente!" << endl;
            break;
        case 4:
            listarEquipos(archivo, maxEquipos);
            cout << "Equipos listados exitosamente!" << endl;
            break;
        case 5: 
            marcarFueradeUso(archivo, maxEquipos);
            break;
    }
    cout << "MENU" << endl;
    
    cout << "Oprima '1' si desea registrar un equipo nuevo." << endl;
    cout << "Oprima '2' si desea consultar un equipo por su código." << endl;
    cout << "Oprima '3' si desea actualizar el estado del equipo. " << endl;
    cout << "Oprima '4' si desea listar los equipos operativos." << endl;
    cout << "Oprima '5' si desea marcar un equipo como fuera de uso. " << endl;
    cout << "A continuación elija la opción que necesite ejecutar: ";
    
    cin >> menu;
    } while (menu != 0);
return 0;
}