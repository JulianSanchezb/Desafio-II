#include "alojamiento.h"
/*
Alojamiento::Alojamiento(){
    nombre = "";
    codigo = NULL;
    documento = NULL;
    tipo = false;
    ubicacion = "";
    direccion = "";
    precio = 0;
    amenidades = "";
    reservas[] = NULL;
    unsigned short int count = 0;
}*/

Alojamiento::Alojamiento(string _nombre, string *_codigo, string *_documento, bool _tipo,string _ubicacion,
                         string _direccion, unsigned int _precio, string _amenidades, Reserva *_reservas) {
    nombre = _nombre;
    codigo = _codigo;
    documento = _documento;
    tipo = _tipo;
    ubicacion = _ubicacion;
    direccion = _direccion;
    precio = _precio;
    amenidades = _amenidades;
    reservas[count] = _reservas;
    count++;
}

string Alojamiento::getNombre(){
    return nombre;
}

string Alojamiento::getCodigo(){
    return codigo;
}

string& Alojamiento::getDocumento() {
    return documento;
}

const string& Alojamiento::getDocumento() const {
    return documento;
}


bool Alojamiento::getTipo(){
    return tipo;
}

string Alojamiento::getUbicacion(){
    return ubicacion;
}

string Alojamiento::getDireccion(){
    return direccion;
}

unsigned int Alojamiento::getPrecio(){
    return precio;
}

string Alojamiento::getAmenidades(){
    return amenidades;
}

//Reserva getReservas();  Falta getter de reservas
//Setters
void Alojamiento::setNombre(const string& _nombre){
    nombre = _nombre;
}

void Alojamiento::setCodigo(const string& _codigo){
    codigo = _codigo;
}

void Alojamiento::setDocumento(const string& _documento){
    documento = _documento;
}

void Alojamiento::setTipo(const bool& _tipo){
    tipo = _tipo;
}


void Alojamiento::setUbicacion(const string& _ubicacion){
    ubicacion = _ubicacion;
}

void Alojamiento::setDireccion(const string &_direccion){
    direccion = _direccion;
}

void Alojamiento::setPrecio(unsigned int _precio){
    precio = _precio;
}

void Alojamiento::setAmenidades(const string& _amenidades){
    amenidades = _amenidades;
}

