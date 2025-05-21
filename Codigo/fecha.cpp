#include "fecha.h"

Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 1;
}

Fecha::Fecha(unsigned short int _dia,unsigned short int _mes,unsigned short int _anio){
    dia = _dia;
    mes = _mes;
    anio = _anio;
}

Fecha::bisiesto(){
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

Fecha::fechaValida(){

    unsigned short int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(bisiesto()){
        meses[1] = 29;
    }

    if(dia > meses[mes - 1] && anio < 2000){
        return false;
    }

    return true;
}

Fecha::nombreDia(){
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

    std::string dias[] = {
        "Sábado", "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes"
    };

    return dias[h];
}

Fecha::getDia(){
    return dia;
}

Fecha::getMes(){
    return mes;
}

Fecha::getAnio(){
    return anio;
}
Fecha::setDia(unsigned short int _dia){
    dia = _dia;
}

Fecha::setMes(unsigned short int _mes){
    mes = _mes;
}

Fecha::setAnio(unsigned short int _anio){
    anio = _anio;
}
