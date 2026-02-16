#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Vehiculo {
    int id;
    char marca[30];
    int anio;
    bool estado;
};

void inicializarArchivo(char nombre[], int maxVeh) {
    fstream file(nombre, ios::binary | ios::in | ios::out);

    if (!file) {
        file.open(nombre, ios::binary | ios::out);

        Vehiculo vacio;
        vacio.id = -1;
        memset(vacio.marca, 0, 30);
        vacio.anio = 0;
        vacio.estado = false;

        for (int i = 0; i < maxVeh; i++) {
            file.write(reinterpret_cast<char*>(&vacio), sizeof(Vehiculo));
        }

        cout << "Archivo inicializado.\n";
    }

    file.close();
}

void registrarVehiculo(char nombre[], int maxVeh) {
    int id;
    cout << "ID (0-" << maxVeh - 1 << "): ";
    cin >> id;

    if (id < 0 || id >= maxVeh) {
        cout << "ID invalido\n";
        return;
    }

    fstream file(nombre, ios::binary | ios::in | ios::out);

    file.seekg(id * sizeof(Vehiculo), ios::beg);

    Vehiculo v;
    file.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

    if (v.id != -1) {
        cout << "Ese ID ya esta ocupado.\n";
        return;
    }

    Vehiculo nuevo;
    nuevo.id = id;

    cout << "Marca: ";
    cin.ignore();
    cin.getline(nuevo.marca, 30);

    cout << "Año: ";
    cin >> nuevo.anio;

    nuevo.estado = true;

    file.seekp(id * sizeof(Vehiculo), ios::beg);
    file.write(reinterpret_cast<char*>(&nuevo), sizeof(Vehiculo));

    cout << "Vehiculo registrado.\n";

    file.close();
}

void consultarVehiculo(char nombre[], int maxVeh) {
    int id;
    cout << "ID: ";
    cin >> id;

    if (id < 0 || id >= maxVeh) {
        cout << "ID invalido\n";
        return;
    }

    ifstream file(nombre, ios::binary);

    file.seekg(id * sizeof(Vehiculo), ios::beg);

    Vehiculo v;
    file.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

    if (v.id == -1) {
        cout << "No existe un vehiculo con ese ID.\n";
    } else {
        cout << "\n--- Vehiculo ---\n";
        cout << "ID: " << v.id << "\n";
        cout << "Marca: " << v.marca << "\n";
        cout << "Año: " << v.anio << "\n";
        cout << "Estado: " << (v.estado ? "Disponible" : "En uso") << "\n\n";
    }

    file.close();
}

void cambiarEstado(char nombre[], int maxVeh) {
    int id;
    cout << "ID: ";
    cin >> id;

    if (id < 0 || id >= maxVeh) {
        cout << "ID invalido\n";
        return;
    }

    fstream file(nombre, ios::binary | ios::in | ios::out);

    file.seekg(id * sizeof(Vehiculo), ios::beg);

    Vehiculo v;
    file.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

    if (v.id == -1) {
        cout << "Ese ID no contiene vehiculo.\n";
        return;
    }

    v.estado = !v.estado;

    file.seekp(id * sizeof(Vehiculo), ios::beg);
    file.write(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

    cout << "Estado cambiado.\n";

    file.close();
}

void mostrarDisponibles(char nombre[], int maxVeh) {
    ifstream file(nombre, ios::binary);

    Vehiculo v;

    cout << "\n--- Vehiculos Disponibles ---\n";

    for (int i = 0; i < maxVeh; i++) {
        file.seekg(i * sizeof(Vehiculo), ios::beg);
        file.read(reinterpret_cast<char*>(&v), sizeof(Vehiculo));

        if (v.id != -1 && v.estado) {
            cout << "ID " << v.id
                 << " | Marca: " << v.marca
                 << " | Año: " << v.anio << "\n";
        }
    }

    file.close();
}

int main() {
    char archivo[20] = "vehiculos.dat";
    int maxVehiculos = 200;

    inicializarArchivo(archivo, maxVehiculos);

    int op;
    do {
        cout << "\nMENU\n"
             << "1. Registrar\n"
             << "2. Consultar\n"
             << "3. Cambiar estado\n"
             << "4. Mostrar disponibles\n"
             << "5. Salir\n"
             << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: registrarVehiculo(archivo, maxVehiculos); break;
            case 2: consultarVehiculo(archivo, maxVehiculos); break;
            case 3: cambiarEstado(archivo, maxVehiculos); break;
            case 4: mostrarDisponibles(archivo, maxVehiculos); break;
        }

    } while (op != 5);

    return 0;
}