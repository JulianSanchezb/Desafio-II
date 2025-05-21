#ifndef HUESPED_H
#define HUESPED_H
#include "reserva.h"
#include <string>
using namespace std;


class Huesped{
private:
    string puntuacion;
    string antiguedad;
    string documento;
    Reserva reservas[20];
public:
    Huesped(); // Constructor por defecto

    void menu();

    // Getters
    string getPuntuacion();
    string getAntiguedad();
    string getDocumento();
    //Falta getter de reservas
    // Setters
    void setPuntuacion(const string& _puntuacion);
    void setAntiguedad(const string& _antiguedad);
    void setDocumento(const string& _documento);
    //Falta setter de reservas
};

#endif // HUESPED_H
