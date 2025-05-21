#include "anfitrion.h"
using namespace std;

Anfitrion::Anfitrion(string _puntuacion, string _antiguedad, string _documento, string _alojamientos) {
    puntuacion = _puntuacion;
    antiguedad = _antiguedad;
    documento = _documento;
    alojamientos[c] = _alojamientos;
    c++;
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

string* Anfitrion::getAlojamiento(int index) {
    if (index >= 0 && index < 20) {
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

void Anfitrion::setAlojamiento(int index, string* _alojamiento) {
    if (index >= 0 && index < 20) {
        alojamientos[index] = _alojamiento;
    }
}
