#include <string>
#include <iostream>

using namespace std;

// ===== ARCHIVO =====
class Archivo{
    private: // atributos
    string info;

    public: // metodos
    Archivo(string);

    void grabarInfo(string);
};

// ===== PERSONA =====
class Persona{
    private: // atributos
    int dni;
    string nombre;
    string apellido;
    int año_ingreso;

    public: // metodos
    Persona(int, string, string, int);
};



// ===== PERSONAL =====
class Personal : public Persona {
    private: // atributos
    string cargo;

    public: // metodos
    Personal(int, string, string, int, string);
};



// ===== TRANSACCION =====
class Transaccion {
    private: // atributos
    float monto;
    int tipo_trans;

    public: // metodos
    Transaccion(float, int);

    // - setters:
    void setMonto(float);
    void setTipoTrans(int);

    // - getters:
    float getMonto();
    int getTipo();
};



// ===== CUENTA =====
class Cuenta {
    private: // atributos
    int nro_cuenta;
    string tipo_caja;
    float saldo;
    Transaccion transaccion;
    Archivo archivo;

    public: // metodos
    Cuenta(int, string, float);

    void realizarTrans(float, int);
};



// ===== TARJETA =====
class Tarjeta {
    private: // atributos
    string tipo_tarj;
    int limite_credito;

    public: // metodos
    Tarjeta(string, int);
};



// ===== CLIENTE =====
class Cliente : public Persona {
    private: // atributos
    string tipo_cl;
    bool estado;
    Cuenta cuenta;
    Tarjeta tarjeta;

    public: // metodos
    Cliente(int, string, string, int, string, bool);

    
};



// ===== BANCO =====
class Banco{
    private: // atributos
    string nombre_banco;
    Personal personal;
    Cliente cliente;
    Archivo archivo;

    public: // metodos
    Banco(string);
};