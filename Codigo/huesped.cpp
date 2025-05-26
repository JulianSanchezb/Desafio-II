#include "huesped.h"
#include <iostream>


Huesped::Huesped() {
    puntuacion = "";
    antiguedad = "";
    documento = "";
    count = 0;
    for(int i = 0;i < 365;i++){
        reservas[i] = nullptr;
    }
}

Huesped::Huesped(string _puntuacion, string _antiguedad,string _documento){
    puntuacion = _puntuacion;
    antiguedad = _antiguedad;
    documento = _documento;
    count = 0;
    for(int i = 0;i < 365;i++){
        reservas[i] = nullptr;
    }
}



void Huesped::menu(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2){

    unsigned short int decision;
    do{
        cout<<"MENU"<<endl;
        cout<<"1.Reservar"<<endl;
        cout<<"2.Cancelar reserva"<<endl;
        cout<<"3.salir"<<endl;
        cin>>decision;
    }while((decision>3) && (decision<0));
    switch (decision) {
    case 1:reserva(alojamientos,reservas,tamano1,tamano2,documento);break;
    case 2:break;
    case 3:cout << "Saliendo del menu..." << endl;break;
    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
    }
}

bool Huesped::verificar_valides(string fechaI,unsigned short int noches){
    Fecha fechainiI(fechaI),fechafinalI,fechainicialo,fechafinalo;
    unsigned short int nochesI;
    fechafinalI = fechainiI.sumar_noches(noches);
    for(unsigned short int i = 0;i <365;i++){//verificar si se puede crear un contador para las reservas
        if (reservas[i] != nullptr){
            fechainicialo = reservas[i]->getDate();
            nochesI = reservas[i]->getNoches();
            fechafinalo = fechainicialo.sumar_noches(nochesI);
            if (!(fechafinalI < fechainicialo || fechainiI > fechafinalo)){
                return false;
            }
        }
    }
    return true;
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
