#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Producto {
    int codigo;
    char nombre [30];
    float precio;
    int cantidad;
};

void registrarProductos(Producto* p, int n_productos) {

for (int i = 0; i < n_productos; i++) {
 
    cout << "Producto # " << i + 1 << "\n";

    cout << "Codigo: ";
    cin >> (p + i) -> codigo;

    cout << "Nombre: ";
    cin.ignore();
    cin.getline ((p + i) -> nombre, 30);


    cout << "Precio: ";
    cin >> (p + i) -> precio;

    cout << "Cantidad: ";
    cin >> (p + i) -> cantidad;

    }
};

void modificarCantidad(Producto** pp) {

    int codigo;
    int nueva_cantidad;

    cout << "Ingrese el codigo del producto al que le gustaria modificar la cantidad: ";
    cin >> codigo;

    for (int i = 0; i < 5; i++) {
        if ((*pp + i) -> codigo == codigo) {
            cout << "Ingrese la nueva cantidad: ";
            cin >> ((*pp + i) -> cantidad);
            cout << "Cantidad modificada exitosamente!\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
};

void mostrarProductos(Producto* p, int n_productos) {
    for (int i = 0; i < n_productos; i++) {
        cout << "Producto # " << i + 1 << ": " << endl;
        cout << "codigo: " << (p + i) -> codigo << "\n";
        cout << "nombre: " << (p + i) -> nombre << "\n";
        cout << "precio: " << (p + i) -> precio << "\n";
        cout << "cantidad: " << (p + i) -> cantidad << "\n";
    }
}

int main () {

Producto productos[5];

Producto* p = productos;

Producto** pp = &p;

int n_productos;

int menu;


cout << "Ingrese el numero de la accion que le gustaria realizar" << endl;
cout << "1 para registrar productos\n";
cout << "2 para modificar la cantidad de un producto \n";
cout << "3 para mostrar todos los productos\n";
cout << "Introduzca su eleccion: ";

cin >> menu;
int registrados = 0;

while (menu >= 0 || menu <= 3) {
    
    switch (menu) {

        case 1:
        cout << "Ingrese la cantidad de productos que le gustaria registrar: ";
        cin >> n_productos;
        
        registrarProductos(p, n_productos);
        cout << "Producto registrado exitosamente!\n";
        registrados++;
        break;

        case 2:
        modificarCantidad(pp);

        break;

        case 3:
        mostrarProductos(p, n_productos);
        cout << "Todos los productos mostrados exitosamente!\n";
        break;
        }

cout << "Ingrese el numero de la accion que le gustaria realizar" << endl;
cout << "1 para registrar productos\n";
cout << "2 para modificar la cantidad de un producto \n";
cout << "3 para mostrar todos los productos\n";
cout << "0 para salir\n";
cout << "Introduzca su eleccion: ";
cin >> menu;

    }
    return 0;
    
}