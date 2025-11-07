#include "clases.h"
#include <iostream>
#include <sstream>
#include <fstream>

// ===== ARCHIVO =====
Archivo::Archivo(){
    nombre_archivo="";
}
Archivo::Archivo(string nombre){
nombre_archivo=nombre;

}
void Archivo::grabarInfo(string texto){
    ofstream archivo(nombre_archivo, ios::app); //abre el archivo o lo crea si no lo esta.
    if (archivo.is_open()){
        archivo<<texto<<endl;
        archivo.close();
        cout<<"Info guardada en "<<nombre_archivo<<endl;
    }else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
    
}
string Archivo::getNombreArchivo()const{
    return nombre_archivo;
}
void Archivo::setNombreArchivo(const string &n){
    nombre_archivo=n;
}


// ===== PERSONA =====
Persona::Persona() : dni(0), nombre(""), apellido(""), año_ingreso(0) {}
Persona::Persona(int _dni, string _nombre, string _apellido, int _añoIngreso){
    dni = _dni;
    nombre = _nombre;
    apellido = _apellido;
    año_ingreso = _añoIngreso;
}

int Persona::getDni() const { return dni; }
string Persona::getNombre() const { return nombre; }
string Persona::getApellido() const { return apellido; }
int Persona::getAnoIngreso() const { return año_ingreso; }

void Persona::setDni(int d){ dni = d; }
void Persona::setNombre(const string &n){ nombre = n; }
void Persona::setApellido(const string &a){ apellido = a; }
void Persona::setAnoIngreso(int y){ año_ingreso = y; }


// ===== PERSONAL =====
Personal::Personal() : Persona(), cargo("") {}
Personal::Personal(int _dni, string _nombre, string _apellido, int _añoIngreso, string _cargo)
    : Persona(_dni, _nombre, _apellido, _añoIngreso){
    cargo = _cargo;
}

void Personal::setCargo(const string &c){ cargo = c; }
string Personal::getCargo() const { return cargo; }


// ===== TRANSACCION =====
Transaccion::Transaccion() : monto(0.0f), tipo_trans(0), dia(0), mes(0), anio(0) {}
Transaccion::Transaccion(float _monto, int _tipoT, int _dia, int _mes, int _anio){
    monto = _monto;
    tipo_trans = _tipoT;
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

// - setters:
void Transaccion::setMonto(float _monto){ monto = _monto; }
void Transaccion::setTipoTrans(int _tipoT){ tipo_trans = _tipoT; }
void Transaccion::setFecha(int d, int m, int a){ dia = d; mes = m; anio = a; }

// - getters:
float Transaccion::getMonto() const { return monto; }
int Transaccion::getTipo() const { return tipo_trans; }
int Transaccion::getDia() const { return dia; }
int Transaccion::getMes() const { return mes; }
int Transaccion::getAnio() const { return anio; }


// ===== CUENTA =====
Cuenta::Cuenta() : nro_cuenta(0), tipo_caja(""), saldo(0.0f), archivo() {}
Cuenta::Cuenta(int _nroCuenta, string _tipoCaja, float _saldo)
    : nro_cuenta(_nroCuenta), tipo_caja(_tipoCaja), saldo(_saldo), archivo() {}

bool Cuenta::realizarTrans(float _monto, int _tipo, int dia, int mes, int anio){
    Transaccion trans(_monto, _tipo, dia, mes, anio);

    if (trans.getTipo() == 1) { // extraccion
        if (_monto > saldo) {
            cout << "Saldo insuficiente en cuenta " << nro_cuenta << endl;
            return false;
        }
        saldo -= trans.getMonto();
    }
    else if (trans.getTipo() == 2){ // deposito
        saldo += trans.getMonto();
    }
    else {
        cout << "Tipo de transaccion no valida." << endl;
        return false;
    }
    //guardar transaccion en archivo
    Archivo archivo("transacciones.txt");
    string linea= to_string(nro_cuenta)+ "," + 
                  tipo_caja + "," +
                  to_string(_monto)+ "," +
                  to_string(dia)+ "/" + to_string(mes)+ "/" + to_string(anio);
archivo.grabarInfo(linea);
cout<<"Se registro la transaccion de manera correcta"<<endl;
    return true;
} 

int Cuenta::getNroCuenta() const { return nro_cuenta; }
string Cuenta::getTipoCaja() const { return tipo_caja; }
float Cuenta::getSaldo() const { return saldo; }

void Cuenta::setSaldo(float s){ saldo = s; }
void Cuenta::setNroCuenta(int n){ nro_cuenta = n; }
void Cuenta::setTipoCaja(const string &t){ tipo_caja = t; }


// ===== TARJETA =====
Tarjeta::Tarjeta() : tipo_tarj("N/A"), limite_credito(0) {}
Tarjeta::Tarjeta(string _tipoTarj, int _limiteCred){
    tipo_tarj = _tipoTarj;
    limite_credito = _limiteCred;
}

void Tarjeta::setTipoTarj(const string &t){ tipo_tarj = t; }
void Tarjeta::setLimiteCredito(int l){ limite_credito = l; }

string Tarjeta::getTipoTarj() const { return tipo_tarj; }
int Tarjeta::getLimiteCredito() const { return limite_credito; }


// ===== CLIENTE =====
Cliente::Cliente() : Persona(), tipo_cl("Plata"), estado(true), cuenta(), tarjeta() {}
Cliente::Cliente(int _dni, string _nombre, string _apellido, int _añoIngreso, string _tipoCl, bool _estado)
    : Persona(_dni, _nombre, _apellido, _añoIngreso), tipo_cl(_tipoCl), estado(_estado), cuenta(), tarjeta() {
    // asigno tarjeta si corresponde
    asignarTarjetaSegunTipo();
}

void Cliente::asignarCuenta(const Cuenta &c){
    cuenta = c;
}

void Cliente::asignarTarjetaSegunTipo(){
    if (tipo_cl == "Plata" || tipo_cl == "plata") {
        tarjeta = Tarjeta("Sin tarjeta", 0);
    } else if (tipo_cl == "Oro" || tipo_cl == "oro") {
        tarjeta = Tarjeta("Credix", 250000);
    } else if (tipo_cl == "Platino" || tipo_cl == "platino") {
        tarjeta = Tarjeta("Premium", 500000);
    } else { // por defecto
        tarjeta = Tarjeta("Sin tarjeta", 0);
    }
}

string Cliente::getTipoCliente() const { return tipo_cl; }
bool Cliente::getEstado() const { return estado; }
void Cliente::setTipoCliente(const string &t){ tipo_cl = t; asignarTarjetaSegunTipo(); }
void Cliente::setEstado(bool e){ estado = e; }

Cuenta& Cliente::obtenerCuenta(){ return cuenta; }
Tarjeta& Cliente::obtenerTarjeta(){ return tarjeta; }


// ===== BANCO =====
Banco::Banco() : nombre_banco("Banco"), personal(), clientes(), archivo() {}
Banco::Banco(string _nombreBanco) : nombre_banco(_nombreBanco), personal(), clientes(), archivo() {}

string Banco::getNombreBanco() const { return nombre_banco; }
void Banco::setNombreBanco(const string &n){ nombre_banco = n; }
void Banco::altaCliente(const Cliente &nuevo){
    clientes.push_back(nuevo); //psuh back simplemente es agregar al final-->como clientes es un vector podemos agregar nuevos(Alta de clientes) x lo que los mismos
    //se van a sumar a la lista de clientes ya registrados en el banco.
    cout<<"Nuevo Cliente agregado al banco"<<endl;}
void Banco::registrarTransaccion(int dni, float monto, int tipo_trans, int dia, int mes,int anio){
    bool encontrado=false;
    for (Cliente &cli:clientes) {
        if (cli.getDni()==dni) {
            encontrado=true;

            Cuenta &cuenta=cli.obtenerCuenta();
            bool exito=cuenta.realizarTrans(monto, tipo_trans, dia, mes, anio);
if(exito){
    cout<< "Transaccion registrada para el cliente con DNI " << dni << endl;
}else{
    cout << "No se pudo realizar la transaccion (saldo insuficiente o error)" << endl;}
   break;}
}
if (!encontrado){cout << "No se encontro un cliente con el DNI que se ingreso" << endl;}
}


// ===== LISTADO DE CLIENTES =====
void Banco::mostrarCliente(){
    if (clientes.size()==0)
    {
      cout<<"No hay clientes registrados en el banco"<<endl;
      return;
    }

cout<<"Listado de clientes del banco"<<endl;
for (int i = 0; i < clientes.size(); i++)
{
    cout<<"Cliente Nº "<<i+1<<endl;
    cout<<"DNI: "<<clientes[i].getDni()<<endl;
    cout<<"Nombre: "<<clientes[i].getNombre()<<" "<< clientes[i].getApellido()<<endl;
    cout<<"Tipo: "<<clientes[i].getTipoCliente() << endl;
    if (clientes[i].getEstado()) {
        cout<< "Estado: Activo"<<endl;
        }else{
        cout<<"Estado: Baja"<< endl;
        }
    cout<<"Saldo actual: $"<<clientes[i].obtenerCuenta().getSaldo()<<endl;
}}
// ===== LISTADO DE CLIENTES POR DNI =====
void Banco::mostrarClienteporDNI(int dni){
    if (clientes.size()==0) {
        cout<<"No hay clientes registrados en el banco"<<endl;
        return;
    }

    bool encontrado = false;
    for (int i = 0; i < clientes.size(); i++) {
        if (clientes[i].getDni()==dni) {
            encontrado=true;
            cout<<"Cliente Nº"<<i+1<<endl;
            cout<<"DNI: "<<clientes[i].getDni()<<endl;
            cout<< "Nombre: "<<clientes[i].getNombre()<<" "<<clientes[i].getApellido() << endl;
            cout << "Tipo: " << clientes[i].getTipoCliente()<<endl;
            if (clientes[i].getEstado()) {
                cout<<"Estado: Activo"<<endl;
            }else{
                cout<<"Estado: Baja"<<endl;
            }
            cout<< "Saldo actual: $"<< clientes[i].obtenerCuenta().getSaldo()<<endl;
            break;
        }
    }

    if (!encontrado)
        cout << "No se encontro un cliente con DNI " << dni << endl;
}

void Banco::mostrarTransacciones(int dni, int mes = 0, int anio = 0) const {
    bool encontrado = false;

    // Buscar el cliente por DNI
    for (const Cliente &cliente : clientes) {
        if (cliente.getDni() == dni) {
            encontrado = true;
            cout << "Transacciones del cliente " << cliente.getNombre() << " " 
                 << cliente.getApellido() <<endl;

            ifstream archivo("transacciones.txt");
            if (!archivo.is_open()) {
                cout << "No se pudo abrir el archivo de transacciones" << endl;
                return;
            }

            string linea;
            string nroCuentaStr = to_string(cliente.obtenerCuenta().getNroCuenta());

            while (getline(archivo, linea)) {
                // Verificar que la linea corresponda a la cuenta del cliente
                if (linea.find(nroCuentaStr) != string::npos) {
                    // Extraer la fecha (ultimo campo, después de la ultima coma)
                    size_t posUltimaComa = linea.rfind(',');
                    if (posUltimaComa == string::npos) continue; // si la linea no cumple con el formato que se pide, se ignora y se continua para evitar que el programa de error
                    string fechaStr = linea.substr(posUltimaComa + 1);

                    // Separar día, mes y año
                    int dia, mesLinea, anioLinea;
                    if (sscanf(fechaStr.c_str(), "%d/%d/%d", &dia, &mesLinea, &anioLinea) != 3)
                        continue;

                    // Filtrar por mes y año 
                    if ((mes != 0 && mesLinea != mes) || (anio != 0 && anioLinea != anio))
                        continue;

                    cout<<linea<<endl;
                }
            }

            archivo.close();
            break;
        }
    }

    if (!encontrado)
        cout << "No se encontro un cliente con DNI " << dni << endl;
}

void Banco::guardarClientes() const{
    Archivo archivo("clientes.txt");
    for(const Cliente &c : clientes) {
        string linea = to_string(c.getDni()) + "," +
                       c.getNombre() + " " + c.getApellido() + "," +
                       c.getTipoCliente() + "," +
                       to_string(c.getAnoIngreso()) + "," +
                       (c.getEstado() ? "Activo" : "Baja");
        archivo.grabarInfo(linea);
    }
}
