#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <string>
using namespace std;

class Huesped;
class Anfitrion;
class Reserva;
class Alojamiento;

void actualizarpermanentereserva(Reserva **reservas,Huesped* huespedes, unsigned int contR, unsigned int conthu,unsigned int &contador);

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Alojamiento* alojaminetos,Reserva **reservas,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA);

void cantidadLineas(string nombre, unsigned int &conta1, unsigned int &conta2, unsigned int &contador);

void crearAnfitriones(Alojamiento* alojamientos, Anfitrion* anfitriones, unsigned int &contador);

void crearHuespedes(Reserva** reservas, Huesped* huespedes, unsigned int &contador);

void asignarReservasA(Alojamiento* alojamientos, Reserva** reservas, unsigned int &tamano1, unsigned int &tamano2, unsigned int &contador);

void asignarReservah(Huesped* huespedes,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2,unsigned int &contador);

void actualizarHistorico(Reserva **reservas, unsigned int &tamano, unsigned int &contador);

void compactarReservas(Reserva** reservas, unsigned int& tamano, unsigned int &contador);

void actualizarHistorico(Reserva **reservas,unsigned int &tamano);

#endif // FUNCIONES_H
