#include <iostream>
#include <string>
#include "clases.h"

using namespace std;


// ===== ARCHIVO =====
Archivo::Archivo(string _info){
    info = _info;
}

void Archivo::grabarInfo(string _info){
    // no tengo idea como grabar la info en el archivo txt
}

// ===== PERSONA =====
Persona::Persona(int _dni, string _nombre, string _apellido, int _añoIngreso){
    dni = _dni;
    nombre = _nombre;
    apellido = _apellido;
    año_ingreso = _añoIngreso;
}


// ===== PERSONAL =====
Personal::Personal(int _dni, string _nombre, string _apellido, int _añoIngreso, string _cargo): Persona(_dni, _nombre, _apellido, _añoIngreso){
    cargo = _cargo;
}


// ===== TRANSACCION =====
Transaccion::Transaccion(float _monto, int _tipoT){
    monto = _monto;
    tipo_trans = _tipoT;
}

// - setters:
void Transaccion::setMonto(float _monto){
    monto = _monto;
}
void Transaccion::setTipoTrans(int _tipoT){
    tipo_trans = _tipoT;
}

// - getters:
float Transaccion::getMonto(){
    return monto;
}
int Transaccion::getTipo(){
    return tipo_trans;
}


// ===== CUENTA =====
Cuenta::Cuenta(int _nroCuenta, string _tipoCaja, float _saldo){
    nro_cuenta = _nroCuenta;
    tipo_caja = _tipoCaja;
    saldo = _saldo;
}

void Cuenta::realizarTrans(float _monto, int _tipo){
    Transaccion trans(_monto, _tipo);
    if (trans.getTipo() == 1) {
        saldo = saldo - trans.getMonto();
    }
    else if (trans.getTipo() == 2){
        saldo = saldo + trans.getMonto();
    }
    else {
        cout << "Tipo de transaccion no valida." << endl;
    }

    string _info = to_string(nro_cuenta) + "," + to_string(trans.getTipo()) + "," + to_string(trans.getMonto());
    Archivo archivo(_info);
} 


// ===== TARJETA =====
Tarjeta::Tarjeta(string _tipoTarj, int _limiteCred){
    tipo_tarj = _tipoTarj;
    limite_credito = _limiteCred;
}


// ===== CLIENTE =====
Cliente::Cliente(int _dni, string _nombre, string _apellido, int _añoIngreso, string _tipoCl, bool _estado): Persona(_dni, _nombre, _apellido, _añoIngreso){
    tipo_cl = _tipoCl;
    estado = _estado;
}





// ===== BANCO =====
Banco::Banco(string _nombreBanco){
    nombre_banco = _nombreBanco;
}

