#include "reserva.h"

Reserva::Reserva() {}

// Getters
Huesped Reserva::getPersona() { //Hay que verificarlo
    return persona;
}

Fecha Reserva::getDate() {  //Hay que verificarlo
    return date;
}

int Reserva::getNoches() {
    return noches;
}

string Reserva::getCodigo() {
    return codigo;
}

string* Reserva::getCodigoA() {
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

const char* Reserva::getComentario() {
    return comentario;
}

// Setters
void Reserva::setPersona(const Huesped& _persona) {
    persona = _persona;
}

void Reserva::setDate(const Fecha& _date) {
    date = _date;
}

void Reserva::setNoches(int _noches) {
    noches = _noches;
}

void Reserva::setCodigo(const string& _codigo) {
    codigo = _codigo;
}

void Reserva::setCodigoA(string* _codigoA) {
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
