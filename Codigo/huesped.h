#ifndef HUESPED_H
#define HUESPED_H
#include "reserva.h"
#include <string>
using namespace std;

class Reserva;

class Huesped{
private:
    string puntuacion;
    string antiguedad;
    string documento;
    unsigned int count = 0;
    Reserva *reservas[365];
public:
    Huesped(); // Constructor por defecto
    Huesped(string _puntuacion, string _antiguedad, string _documento);
    void menu();
    void imprimir() const;

    // Getters
    string getPuntuacion();
    string getAntiguedad();
    string* getDocumento();
    const string* getDocumento() const;
    Reserva *getReserva(int index);
    // Setters
    void setPuntuacion(const string& _puntuacion);
    void setAntiguedad(const string& _antiguedad);
    void setDocumento(const string& _documento);
    void setReserva(Reserva* _reserva);
};

#endif // HUESPED_H
