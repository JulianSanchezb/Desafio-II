#include "alojamiento.h"
#include <iostream>

//Constructor por defecto
Alojamiento::Alojamiento() {
    nombre = "";
    codigo = "";
    documento = nullptr;
    tipo = false;
    ubicacion = "";
    direccion = "";
    precio = 0;
    amenidades = "";
    count = 0;
    for (int i = 0; i < 20; i++) {
        reservas[i] = nullptr;
    }
}

// Constructor
Alojamiento::Alojamiento(const string& _nombre, const string& _codigo, string* _documento,
                         bool _tipo, const string& _ubicacion, const string& _direccion,
                         unsigned int _precio, const string& _amenidades) {
    nombre = _nombre;
    codigo = _codigo;
    documento = _documento;  // Guardamos el puntero, no el valor
    tipo = _tipo;
    ubicacion = _ubicacion;
    direccion = _direccion;
    precio = _precio;
    amenidades = _amenidades;
    count = 0;
    for (int i = 0; i < 20; i++) {
        reservas[i] = nullptr;
    }

}


bool Alojamiento::disponibilidad(const string& fechaInicio,unsigned short int noches, const string& municipio){
    if(ubicacion != municipio){
        return false;
    }
    for(unsigned short int i=0; i<count ;i++){
        if (reservas[i] != nullptr) {
            if(!(reservas[i]->verificarFecha(fechaInicio,noches))){
                return false;
            }
        }
    }
    return true;
}

void Alojamiento::imprimir() const {
    cout << "=== Alojamiento ===" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Documento del propietario: " << (documento ? *documento : "N/A") << endl;
    cout << "Tipo: " << (tipo ? "Casa" : "Departamento") << endl;
    cout << "Ubicacion: " << ubicacion << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Precio: " << precio << endl;
    cout << "Amenidades: " << amenidades << endl;
}

void Alojamiento::actualizarReservas(){
    unsigned short int c = 0;
    for(unsigned short int i = count;i < 365; i++){
        if(reservas[i] == nullptr){
            c++;
        }else{
            reservas[i] = nullptr;
        }
        if(c == 10){
            break;
        }
    }
}

string Alojamiento::getNombre()  {
    return nombre;
}

string Alojamiento::getCodigo()  {
    return codigo;
}

string* Alojamiento::getDocumento() const {
    return documento;
}

bool Alojamiento::getTipo()  {
    return tipo;
}

string Alojamiento::getUbicacion()  {
    return ubicacion;
}

string Alojamiento::getDireccion()  {
    return direccion;
}

unsigned int Alojamiento::getPrecio()  {
    return precio;
}

string Alojamiento::getAmenidades()  {
    return amenidades;
}


Reserva* Alojamiento::getReserva(int index) {
    if (index >= 0 && index < 20 && index < count) {
        return reservas[index];
    }
    return nullptr;
}

unsigned short int Alojamiento::getCount() const {
    return count;
}

//Setters
void Alojamiento::setNombre(const string& _nombre){
    nombre = _nombre;
}

void Alojamiento::setCodigo(const string& _codigo){
    codigo = _codigo;
}

void Alojamiento::setDocumento(string *_documento){
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

void Alojamiento::setReserva(Reserva *_reserva) {
    if(count < 365){
        reservas[count] = _reserva;
        count++;
    }else{
        cout<<"\nEXCEDIO LA CANTIDAD DE RESERVAS PERMITIDA\n";
    }
}

void Alojamiento::setCount(unsigned short int _count){
    count = _count;
}
