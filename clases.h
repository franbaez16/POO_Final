#include <string>
#include <iostream>
#include <vector>

using namespace std;

// ===== ARCHIVO =====
class Archivo{
    private:
    string info;

    public:
    Archivo();
    Archivo(string);

    void grabarInfo(string);
    string getInfo();
    void setInfo(string);
};

// ===== PERSONA =====
class Persona{
    private:
    int dni;
    string nombre;
    string apellido;
    int año_ingreso;

    public:
    Persona();
    Persona(int, string, string, int);

    // getters / setters
    int getDni() const;
    string getNombre() const;
    string getApellido() const;
    int getAnoIngreso() const;

    void setDni(int);
    void setNombre(const string &);
    void setApellido(const string &);
    void setAnoIngreso(int);
};

// ===== PERSONAL =====
class Personal : public Persona {
    private:
    string cargo;

    public:
    Personal();
    Personal(int, string, string, int, string);

    void setCargo(const string &);
    string getCargo() const;
};

// ===== TRANSACCION =====
class Transaccion {
    private:
    float monto;
    int tipo_trans; // 1 = extraccion, 2 = deposito
    int dia;
    int mes;
    int anio;

    public:
    Transaccion();
    Transaccion(float, int, int dia=0, int mes=0, int anio=0);

    // setters:
    void setMonto(float);
    void setTipoTrans(int);
    void setFecha(int dia, int mes, int anio);

    // getters:
    float getMonto() const;
    int getTipo() const;
    int getDia() const;
    int getMes() const;
    int getAnio() const;
};

// ===== CUENTA =====
class Cuenta {
    private:
    int nro_cuenta;
    string tipo_caja; // "Pesos" o "Dolares"
    float saldo;
    vector<Transaccion> historial;
    Archivo archivo; 

    public:
    Cuenta();
    Cuenta(int, string, float);

    // operaciones
    bool realizarTrans(float monto, int tipo, int dia=0, int mes=0, int anio=0);

    // getters / setters
    int getNroCuenta() const;
    string getTipoCaja() const;
    float getSaldo() const;

    void setSaldo(float);
    void setNroCuenta(int);
    void setTipoCaja(const string &);
};

// ===== TARJETA =====
class Tarjeta {
    private:
    string tipo_tarj;
    int limite_credito;

    public:
    Tarjeta();
    Tarjeta(string, int);

    void setTipoTarj(const string &);
    void setLimiteCredito(int);

    string getTipoTarj() const;
    int getLimiteCredito() const;
};

// ===== CLIENTE =====
class Cliente : public Persona {
    private:
    string tipo_cl; // Plata / Oro / Platino
    bool estado; // true = ACTIVO, false = BAJA
    Cuenta cuenta;
    Tarjeta tarjeta;

    public:
    Cliente();
    Cliente(int, string, string, int, string, bool);

    // comportamiento
    void asignarCuenta(const Cuenta &);
    void asignarTarjetaSegunTipo(); // asigna tarjeta según tipo_cl

    // getters / setters
    string getTipoCliente() const;
    bool getEstado() const;
    void setTipoCliente(const string &);
    void setEstado(bool);

    Cuenta& obtenerCuenta();
    Tarjeta& obtenerTarjeta();
};

// ===== BANCO =====
class Banco{
    private:
    string nombre_banco;
    vector<Personal> personal;
    vector<Cliente> clientes;
    Archivo archivo;

    public:
    Banco();
    Banco(string);

    string getNombreBanco() const;
    void setNombreBanco(const string &);
};
