#include "clases.h"
#include <iostream>
#include <sstream>

// ===== ARCHIVO =====
Archivo::Archivo() : info("") {}
Archivo::Archivo(string _info) : info(_info) {}
void Archivo::grabarInfo(string _info){
    // completar
}
string Archivo::getInfo(){ return info; }
void Archivo::setInfo(string s){ info = s; }


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

