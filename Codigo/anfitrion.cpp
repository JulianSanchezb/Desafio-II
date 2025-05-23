#include "anfitrion.h"
using namespace std;

Anfitrion::Anfitrion(string _puntuacion, string _antiguedad, string _documento) {
    puntuacion = _puntuacion;
    antiguedad = _antiguedad;
    documento = _documento;
    for(int i = 0;i < 20;i++){
        alojamientos[i] = nullptr;
    }
}

// Getters
string Anfitrion::getPuntuacion() {
    return puntuacion;
}

string Anfitrion::getAntiguedad() {
    return antiguedad;
}

string Anfitrion::getDocumento() {
    return documento;
}

Alojamiento* Anfitrion::getAlojamiento(int index) {
    if (index >= 0 && index < 20 && index < c) {
        return alojamientos[index];
    }
    return nullptr;
}
// Setters
void Anfitrion::setPuntuacion(const string& _puntuacion) {
    puntuacion = _puntuacion;
}

void Anfitrion::setAntiguedad(const string& _antiguedad) {
    antiguedad = _antiguedad;
}

void Anfitrion::setDocumento(const string& _documento) {
    documento = _documento;
}

void Anfitrion::setAlojamiento(int index, Alojamiento *_alojamiento) {
    if (index >= 0 && index < 20) {
        alojamientos[index] = _alojamiento;
    }
}
