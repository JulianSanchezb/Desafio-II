#include "huesped.h"
#include "reserva.h"
#include "Funciones.h"
#include "FuncionesReserva.h"
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

void Huesped::menu(Huesped *huespedes, Alojamiento* alojamientos,Reserva** reservas, unsigned int &tamano2,
                   unsigned int &contR, unsigned int &contA){

    bool bandera;
    unsigned short int decision;
    string codigo;
    do{
        cout<<"\n-----Bienvenido, Huesped-----\n\nIngrese el numero de la accion que desea realizar"<<endl;
        cout<<"1.Reservar"<<endl;
        cout<<"2.Cancelar reserva"<<endl;
        cout<<"3.salir"<<endl;
        cin>>decision;
        switch (decision) {
        case 1:reserva(alojamientos,reservas,huespedes,contA,contR,tamano2,documento);break;
        case 2:
            do{
                bandera = false;
                cout<<"RECUERDA: en tu comprobante hay un numero identificador 100001,100002,..."<<endl;
                cout<<"\nIngresa el numero identificador del reserva que deseas: "<<endl;
                cin >>codigo;
                for (int i = 0; i < count; ++i) {
                    if(getReserva(i) != nullptr){
                        if (getReserva(i)->getCodigo() == codigo){
                            bandera =  true; // Encontrado
                            break;
                        }
                    }
                }
            }while(!bandera);
            cancelareserva(huespedes,reservas,alojamientos,tamano2,contA,contR,codigo);
            break;
        case 3:cout << "\nSaliendo del menu...\n" << endl;break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }while((decision>3) || (decision<0));
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

void Huesped:: cancelReserva(unsigned int index) {
    if (index < count && reservas[index] != nullptr) {
        reservas[index] = nullptr;
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
            reservas[i]->mostrar();
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
            c = 0;
        }
        if(c == 20){
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
    if (index >= 0 && index < 365 && index < count) {
        return reservas[index];
    }
    return nullptr;
}

unsigned short int Huesped::getCount(){
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
