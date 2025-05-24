#ifndef FECHA_H
#define FECHA_H
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
    void mostrar() const;
    //Getters
    unsigned short int getDia();
    unsigned short int getMes();
    unsigned short int getAnio();
    //Setters
    void setDia(unsigned short int _dia);
    void setMes(unsigned short int _mes);
    void setAnio(unsigned short int _anio);
};

#endif // FECHA_H
