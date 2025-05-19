#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include "anfitrion.h"
#include "reserva.h"
#include <string>
using namespace std;

class Alojamiento{
private:
    string nombre;
    int *codigo;
    Anfitrion dueño;
    string ubicacion;
    bool tipo;
    string direccion;
    unsigned int precio;
    string amenidades[10];
    Reserva reservas[20];
public:

};

#endif // ALOJAMIENTO_H
