#include "clases.h"
#include <iostream>
using namespace std;

int main() {
    Banco bancoA("Banco UCC");
    int respuesta = 0;

    while (true) {
        //MENU
        cout<<"MENU BANCO"<<endl;
        cout<<"1. Alta de cliente"<<endl;
        cout<<"2. Registrar transaccion"<<endl;
        cout<<"3. Mostrar todos los clientes"<<endl;
        cout<<"4. Mostrar transacciones de un cliente"<<endl;
        cout<<"5. Guardar clientes en archivov"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<"Ingrese una opcion (1-6): "<<endl;
        cin>>respuesta;

        if (respuesta == 1) {
            int dni, anioIngreso;
            string nombre, apellido, tipoCliente;
            cout<<"Ingrese DNI: "; cin >> dni; cin.ignore();
            cout<<"Ingrese nombre: "; getline(cin, nombre); //getline para leer espacios. Si se guardara solo como cin>>variable, lee la primera palabra lo q no sirve para, por ej, Martinez Lolo
            cout<<"Ingrese apellido: "; getline(cin, apellido); 
            cout<<"Ingrese año de ingreso: "; cin >> anioIngreso; cin.ignore();//cin.ignore Ignora el salto de linea q se define(endl;) evitando que el campo no quede vacio
            cout<<"Ingrese tipo de cliente (Plata/Oro/Platino): "; getline(cin, tipoCliente);

            Cliente nuevo(dni, nombre, apellido, anioIngreso, tipoCliente, true);
            bancoA.altaCliente(nuevo);
        }
        else if (respuesta == 2) {
            int dni, tipo, dia, mes, anio;
            float monto;
            cout << "Ingrese DNI del cliente: "; cin >> dni;
            cout << "Ingrese monto: "; cin >> monto;
            cout << "Ingrese tipo de transaccion (1-Extraccion, 2-Deposito): "; cin >> tipo;
            cout << "Ingrese fecha (dia mes anio): "; cin >> dia >> mes >> anio;
            bancoA.registrarTransaccion(dni, monto, tipo, dia, mes, anio);
        }
        else if (respuesta == 3) {
            bancoA.mostrarCliente();
        }
        else if (respuesta == 4) {
            int dni, mes=0, anio=0;
            cout << "Ingrese DNI del cliente: "; cin >> dni;
            cout << "Ingrese mes (0 para usar todos): "; cin >> mes;
            cout << "Ingrese anio (0 para usar todos): "; cin >> anio;
            bancoA.mostrarTransacciones(dni, mes, anio);
        }
        else if (respuesta == 5) {
            bancoA.guardarClientes();
            cout << "Clientes guardados en archivo"<<endl;
        }
        else if (respuesta == 6) {
            cout << "Saliendo del programa..."<<endl;
            break;
        }
        else {
            cout << "Opcion invalida, intente nuevamente"<<endl;
        }
    }

    return 0;
}
