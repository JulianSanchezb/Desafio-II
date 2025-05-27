#ifndef FECHA_H
#define FECHA_H
#include "Funciones.h"
using namespace std;
#include <string>

class Fecha{
private:
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int anio;
public:
    Fecha();    //Constructor por defecto
    Fecha(unsigned short int _dia,unsigned short int _mes,unsigned short int _anio);   //Constructor
    Fecha(string _fecha);
    bool fechaValida();
    string nombreDia();    //Con la formula de Zeller(con division entera)
    bool bisiesto();
    Fecha sumar_noches(unsigned short int noches);
    string nombremes();
    void mostrar() const;
    //Getters
    unsigned short int getDia();
    unsigned short int getMes();
    unsigned short int getAnio();
    //Setters
    void setDia(unsigned short int _dia);
    void setMes(unsigned short int _mes);
    void setAnio(unsigned short int _anio);
    //sobrecarga
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
};

#endif // FECHA_H
