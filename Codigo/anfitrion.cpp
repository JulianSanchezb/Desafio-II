#include "anfitrion.h"
#include "alojamiento.h"
#include <iostream>
using namespace std;

Anfitrion::Anfitrion(){
    puntuacion = "";
    antiguedad = "";
    documento = "";
    unsigned int contaAlojamientos = 0;
    for(int i = 0;i < 20;i++){
        alojamientos[i] = nullptr;
    }
}

Anfitrion::Anfitrion(string _puntuacion, string _antiguedad, string _documento) {
    puntuacion = _puntuacion;
    antiguedad = _antiguedad;
    documento = _documento;
    unsigned int contaAlojamientos = 0;
    for(int i = 0;i < 20;i++){
        alojamientos[i] = nullptr;
    }
}

void Anfitrion::imprimir() const {
    cout << "=== Anfitrion ===" << endl;
    cout << "Documento: " << documento << endl;
    cout << "Puntuacion: " << puntuacion << endl;
    cout << "Antigüedad: " << antiguedad << endl;
    cout << "Cantidad de alojamientos: " << contaAlojamientos << endl;
    for (unsigned int i = 0; i < contaAlojamientos; ++i) {
        if (alojamientos[i]) {
            cout << "\nAlojamiento #" << i + 1 << ":" << endl;
            alojamientos[i]->imprimir();  // asumiendo que Alojamiento tiene imprimir()
        }
    }
}

// Getters
string Anfitrion::getPuntuacion() {
    return puntuacion;
}

string Anfitrion::getAntiguedad() {
    return antiguedad;
}

string* Anfitrion::getDocumento() {
    return &documento;
}

Alojamiento* Anfitrion::getAlojamiento(int index) {
    if (index >= 0 && index < 20 && index < contaAlojamientos) {
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

void Anfitrion::setAlojamiento(Alojamiento *_alojamiento) {
    alojamientos[contaAlojamientos] = _alojamiento;
    contaAlojamientos++;
}
