#include "reserva.h"
#include "huesped.h"
#include <iostream>

Reserva::Reserva()
    : documento(nullptr),
    date(),        // Llama al constructor por defecto de Fecha
    noches(0),
    codigo(""),
    codigoA(""),
    metodoPago(false),
    pago(),        // Llama al constructor por defecto de Fecha
    monto(0),
    comentario("") {
}

Reserva::Reserva(string* _documento,string _fechaI,unsigned short int _noches,string _codigo, string _codigoA,bool _metodoPago,string _fechaP,unsigned int _monto)
    : documento(_documento),
    date(_fechaI),        // Llama al constructor con string de Fecha
    noches(_noches),
    codigo(_codigo),
    codigoA(_codigoA),
    metodoPago(_metodoPago),
    pago(_fechaP),        // Llama al constructor con string de Fecha
    monto(_monto),
    comentario("") {
}

void Reserva::mostrar() const {
    cout << "Documento: " << (documento ? *documento : "N/A") << endl;
    cout << "Fecha de reserva: ";
    date.mostrar();  // Supongo que Fecha tiene método mostrar()
    cout << endl;

    cout << "Noches: " << noches << endl;
    cout << "Codigo reserva: " << codigo << endl;
    cout << "Codigo alojamiento: " << codigoA << endl;
    cout << "Metodo de pago: " << (metodoPago ? "Tarjeta" : "Efectivo") << endl;

    cout << "Fecha de pago: ";
    pago.mostrar();
    cout << endl;

    cout << "Monto: $" << monto << endl;
    cout << "Comentario: " << comentario << endl;
}

// Getters
string* Reserva::getDocumento() const {
    return documento;
}

string Reserva::getDocumentoValor() const {
    return *documento;
}

Fecha Reserva::getDate() {  //Hay que verificarlo
    return date;
}

unsigned short int Reserva::getNoches() {
    return noches;
}

string Reserva::getCodigo() {
    return codigo;
}

string Reserva::getCodigoA() {
    return codigoA;
}

bool Reserva::getMetodoPago() {
    return metodoPago;
}

Fecha Reserva::getPago() {
    return pago;
}

unsigned int Reserva::getMonto() {
    return monto;
}

string Reserva::getComentario() {
    return comentario;
}

// Setters
void Reserva::setDocumento(string *_documento){
    documento = _documento;
}

void Reserva::setDate(const string &_date) {
    date = _date;
}

void Reserva::setNoches(int _noches) {
    noches = _noches;
}

void Reserva::setCodigo(const string& _codigo) {
    codigo = _codigo;
}

void Reserva::setCodigoA(string _codigoA) {
    codigoA = _codigoA;
}

void Reserva::setMetodoPago(bool _metodoPago) {
    metodoPago = _metodoPago;
}

void Reserva::setPago(const Fecha& _pago) {
    pago = _pago;
}

void Reserva::setMonto(unsigned int _monto) {
    monto = _monto;
}

void Reserva::setComentario(const string& _comentario) {
    if (_comentario.length() > 1000) {
        comentario = _comentario.substr(0, 1000); // cortar a 1000 caracteres
    } else {
        comentario = _comentario;
    }
}
