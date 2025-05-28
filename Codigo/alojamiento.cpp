#include "alojamiento.h"
#include <iostream>
#include <sstream>
#include <string>

//Constructor por defecto
Alojamiento::Alojamiento() {
    nombre = "";
    codigo = "";
    documento = nullptr;
    puntuacion = nullptr;
    tipo = false;
    ubicacion = "";
    direccion = "";
    precio = 0;
    amenidades = "";
    count = 0;
    for (int i = 0; i < 365; i++) {
        reservas[i] = nullptr;
    }
}

// Constructor
Alojamiento::Alojamiento(const string& _nombre, const string& _codigo, string* _documento,string* _puntuacion,
                         bool _tipo, const string& _ubicacion, const string& _direccion,
                         unsigned int _precio, const string& _amenidades) {
    nombre = _nombre;
    codigo = _codigo;
    documento = _documento;    // Guardamos el puntero, no el valor
    puntuacion = _puntuacion;
    tipo = _tipo;
    ubicacion = _ubicacion;
    direccion = _direccion;
    precio = _precio;
    amenidades = _amenidades;
    count = 0;
    for (int i = 0; i < 365; i++) {
        reservas[i] = nullptr;
    }
    contador++;

}

int Alojamiento::contador = 0;

bool Alojamiento::disponibilidad(const string& fechaInicio,unsigned short int noches, const string& municipio,unsigned int &contador){
    string aux,ubi;
    aux = ubicacion;
    stringstream iss(aux);

    getline(iss,aux,'-');
    getline(iss,ubi,'-');
    if(ubi != municipio){
        return false;
    }
    for(unsigned short int i=0; i<count ;i++){
        contador++;
        if (reservas[i] != nullptr) {
            if(!(reservas[i]->verificarFecha(fechaInicio,noches))){
                return false;
            }
        }
    }

    return true;
}

bool Alojamiento::filtro(float puntuacionusu, unsigned int coste,unsigned short int decision){
    float puntuacionanfi;
    puntuacionanfi = stof(*puntuacion);
    if(decision == 0){
        if((puntuacionanfi >= puntuacionusu) && (precio <= coste)){
            return true;
        }
    }else if(decision == 1){
        if(puntuacionanfi>= puntuacionusu){
            return true;
        }
    }else if(decision == 2){
        if(precio<= coste){
            return true;
        }
    }
    return false;
}

void Alojamiento::imprimir() const {
    cout << "\n=== Alojamiento ===\n" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Codigo: " << codigo << endl;
    cout << "Documento del propietario: " << (documento ? *documento : "N/A") << endl;
    cout << "Puntuacion: "<<*puntuacion<<endl;
    cout << "Tipo: " << (tipo ? "Casa" : "Departamento") << endl;
    cout << "Ubicacion: " << ubicacion << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Precio: " << precio << endl;
    cout << "Amenidades: " << amenidades << endl;
}


void Alojamiento::cancelareserva(const string& codigo,unsigned int &contador) {
    for (unsigned short int i = 0; i < count; ++i) {
        contador++;
        if (reservas[i] != nullptr && reservas[i]->getCodigo() == codigo) {
            reservas[i] = nullptr;
            return;
        }
    }
}

void Alojamiento::actualizarReservas(unsigned int &contador){
    unsigned short int c = 0;
    for(unsigned short int i = count;i < 365; i++){
        contador++;
        if(reservas[i] == nullptr){
            c++;
        }else{
            reservas[i] = nullptr;
            c = 0;
        }
        if(c == 20){
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


Reserva* Alojamiento::getReserva(unsigned short int index) {
    if (index >= 0 && index < 365 && index < count) {
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

int Alojamiento::getContador() {
    return contador;
}
