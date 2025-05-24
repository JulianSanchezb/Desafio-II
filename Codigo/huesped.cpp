#include "huesped.h"
#include <iostream>
Huesped::Huesped() {
    puntuacion = "";
    antiguedad = "";
    documento = "";
    count = 0;
    for(int i = 0;i < 20;i++){
        reservas[i] = nullptr;
    }
}

Huesped::Huesped(string _puntuacion, string _antiguedad,string _documento){
    puntuacion = _puntuacion;
    antiguedad = _antiguedad;
    documento = _documento;
    count = 0;
    for(int i = 0;i < 20;i++){
        reservas[i] = nullptr;
    }
}

void Huesped::imprimir() const {
    cout << "Documento: " << documento << endl;
    cout << "Antigüedad: " << antiguedad << endl;
    cout << "Puntuación: " << puntuacion << endl;
    cout << "Cantidad de reservas: " << count << endl;

    for (unsigned int i = 0; i < count; ++i) {
        if (reservas[i] != nullptr) {
            cout << "Reserva #" << i + 1 << ":" << endl;
            reservas[i]->mostrar();  // Asegúrate de tener este método en Reserva
            cout << "-----------------------------" << endl;
        }
    }
}

// Getters
string Huesped::getPuntuacion() {
    return puntuacion;
}

string Huesped::getAntiguedad() {
    return antiguedad;
}

string* Huesped::getDocumento() {
    return &documento;
}

const string* Huesped::getDocumento() const {
    return &documento;
}

Reserva* Huesped::getReserva(int index) {
    if (index >= 0 && index < 20 && index < count) {
        return reservas[index];
    }
    return nullptr;
}

// Setters
void Huesped::setPuntuacion(const string& _puntuacion) {
    puntuacion = _puntuacion;
}

void Huesped::setAntiguedad(const string& _antiguedad) {
    antiguedad = _antiguedad;
}

void Huesped::setDocumento(const string& _documento) {
    documento = _documento;
}

void Huesped::setReserva(Reserva *_reserva) {
    reservas[count] = _reserva;
    count++;
}
