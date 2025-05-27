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



void Huesped::menu(){

    unsigned short int decision;
    do{
        cout<<"MENU"<<endl;
        cout<<"1.Reservar"<<endl;
        cout<<"2.Cancelar reserva"<<endl;
        cout<<"3.salir"<<endl;
        cin>>decision;
    }while((decision>3) && (decision<0));
    switch (decision) {
    case 1:;break;
    case 2:break;
    case 3:cout << "Saliendo del menu..." << endl;break;
    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
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

void Huesped::actualizarReservas(){
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

unsigned short Huesped::getCount(){
    return count;
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

void Huesped::setCount(unsigned short int _count){
    count = _count;
}
