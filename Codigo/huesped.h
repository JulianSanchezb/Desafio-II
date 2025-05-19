#ifndef HUESPED_H
#define HUESPED_H
#include "reserva.h"



class Huesped{
private:
    float puntuacion;
    float antiguedad;
    int documento;
    Reserva reservas[20];
public:
    void menu();
};

#endif // HUESPED_H
