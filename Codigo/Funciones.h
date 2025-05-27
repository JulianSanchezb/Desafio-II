#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;

class Huesped;
class Anfitrion;
class Reserva;
class Alojamiento;

void ingresar_sistema(Huesped *huespedes, Anfitrion *anfitriones, Reserva **reservas, Alojamiento *alojamientos, unsigned int &contan, unsigned int &conthu, unsigned int contR, unsigned int contal);

void cantidadLineas(string nombre, unsigned int &conta1,unsigned int &conta2);

void crearAnfitriones(Alojamiento* alojamientos, Anfitrion* anfitriones);

void crearHuespedes(Reserva** reservas, Huesped* huespedes);

void asignarReservasA(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2);

void asignarReservah(Huesped* huespedes,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2);

void actualizarHistorico(Reserva **reservas,unsigned int tamano);

void compactarReservas(Reserva** reservas, unsigned int& tamano);


#endif // FUNCIONES_H
