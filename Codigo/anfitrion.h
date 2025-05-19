#ifndef ANFITRION_H
#define ANFITRION_H
#include "alojamiento.h"



class Anfitrion{
private:
    float puntuacion;
    float antiguedad;
    int documento;
    Alojamiento alojamientos[20];
public:
    void consultaReserva();
    void menu();
};

#endif // ANFITRION_H
