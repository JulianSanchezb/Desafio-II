#include "huesped.h"
#include "reserva.h"
#include "alojamiento.h"
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
    contador++;
}
int Huesped::contador = 0;

void Huesped::menu(Huesped *huespedes, Alojamiento* alojamientos,Reserva** reservas, unsigned int &tamano2,
                   unsigned int &contR, unsigned int &contA){
    unsigned int contador = 0;
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
        case 1:reserva(alojamientos,reservas,huespedes,contA,contR,tamano2,documento,contador);
            cout<<"\nSe hicieron "<<contador<<" iteraciones en la ultima funcionalidad\n";
            cout<<"La memoria usada por concepto de objetos creado es: "<<(Alojamiento::getContador())+(Anfitrion::getContador())+(Huesped::getContador())+(Reserva::getContador())<<" bytes\n\n";
            contador = 0;
                break;
        case 2:
            do{
                bandera = false;
                cout<<"RECUERDA: en tu comprobante hay un numero identificador 100001,100002,..."<<endl;
                cout<<"\nIngresa el numero identificador del reserva que deseas: "<<endl;
                cin >>codigo;
                for (int i = 0; i < count; ++i) {
                    contador++;
                    if(getReserva(i) != nullptr){
                        if (getReserva(i)->getCodigo() == codigo){
                            bandera =  true; // Encontrado
                            break;
                        }
                    }
                }
            }while(!bandera);
            cancelareserva(huespedes,reservas,alojamientos,tamano2,contR,contA,codigo,contador);
            cout<<"\nSe hicieron "<<contador<<" iteraciones en la ultima funcionalidad\n";
            cout<<"La memoria usada por concepto de objetos creado es: "<<(Alojamiento::getContador())+(Anfitrion::getContador())+(Huesped::getContador())+(Reserva::getContador())<<" bytes\n\n";
            contador = 0;
            break;
        case 3:cout << "\nSaliendo del menu...\n" << endl;break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }while((decision>3) || (decision<0));
}

bool Huesped::verificar_valides(string fechaI, unsigned short int noches, unsigned int &contador){
    Fecha fechainiI(fechaI),fechafinalI,fechainicialo,fechafinalo;
    unsigned short int nochesI;
    fechafinalI = fechainiI.sumar_noches(noches);
    for(unsigned short int i = 0;i <365;i++){//verificar si se puede crear un contador para las reservas
        contador++;
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


void Huesped::actualizarReservas(unsigned int &contador){
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

int Huesped::getContador() {
    return sizeof(Huesped)*contador;
}
