#ifndef FECHA_H
#define FECHA_H
#include <string>
using namespace std;

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
    string nombreDia() const;    //Con la formula de Zeller(con division entera)
    bool bisiesto();
    string sumar_noches(unsigned short int noches);
    string nombremes() const;
    string mostrar() const;
    //Getters
    unsigned short int getDia() const;
    unsigned short int getMes() const;
    unsigned short int getAnio() const;
    //Setters
    void setDia(unsigned short int _dia);
    void setMes(unsigned short int _mes);
    void setAnio(unsigned short int _anio);
    //sobrecarga
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
};

#endif // FECHA_H
