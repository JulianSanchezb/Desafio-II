#include "fecha.h"
#include <sstream>
#include <iostream>
using namespace std;


Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

Fecha::Fecha(unsigned short int _dia,unsigned short int _mes,unsigned short int _anio){
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

Fecha::Fecha(string _fecha){
    string aux;
    stringstream iss(_fecha);

    getline(iss,aux,'/');
    dia = stoi(aux);

    getline(iss,aux,'/');
    mes = stoi(aux);

    getline(iss,aux,'/');
    anio = stoi(aux);

}

bool Fecha::bisiesto(){
    if (anio % 4 == 0){
        if (anio % 100 != 0){
            return true;
        }else if (anio % 400 == 0){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool Fecha::fechaValida(){

    unsigned short int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(bisiesto()){
        meses[1] = 29;
    }

    if(dia > meses[mes - 1] && anio < 2000){
        return false;
    }

    return true;
}

string Fecha::nombreDia(){
    int y = anio;
    int m = mes;
    int d = dia;

    if (m < 3) {
        m += 12;
        y -= 1;
    }

    int K = y % 100;
    int J = y / 100;

    int h = (d + 13*(m + 1)/5 + K + K/4 + J/4 + 5*J) % 7;

    string dias[] = {
        "Sabado", "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"
    };

    return dias[h];
}

void Fecha::mostrar() const {
    cout << (dia < 10 ? "0" : "") << dia << "/"
         << (mes < 10 ? "0" : "") << mes << "/"
         << anio;
}

//Getters
unsigned short int Fecha::getDia(){
    return dia;
}

unsigned short int Fecha::getMes(){
    return mes;
}

unsigned short int Fecha::getAnio(){
    return anio;
}
//Setters
void Fecha::setDia(unsigned short int _dia){
    dia = _dia;
}

void Fecha::setMes(unsigned short int _mes){
    mes = _mes;
}

void Fecha::setAnio(unsigned short int _anio){
    anio = _anio;
}
