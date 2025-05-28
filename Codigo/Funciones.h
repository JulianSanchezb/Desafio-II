#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <string>
using namespace std;

class Huesped;
class Anfitrion;
class Reserva;
class Alojamiento;

void actualizarpermanentereserva(Reserva **reservas,Huesped* huespedes, unsigned int contR, unsigned int conthu);

void comentario(string codigoR);

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Alojamiento* alojaminetos,Reserva **reservas,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA);

void cantidadLineas(string nombre, unsigned int &conta1,unsigned int &conta2);

void crearAnfitriones(Alojamiento* alojamientos, Anfitrion* anfitriones);

void crearHuespedes(Reserva** reservas, Huesped* huespedes);

void asignarReservasA(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2);

void asignarReservah(Huesped* huespedes,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2);

void actualizarHistorico(Reserva **reservas, unsigned int &tamano);

void compactarReservas(Reserva** reservas, unsigned int& tamano);

bool usofiltro(Alojamiento &alojamientos, unsigned int precio, float puntuacion, unsigned short decision);

void reserva(Alojamiento* alojamientos, Reserva** reservas, Huesped *huespedes, unsigned int &tamano1, unsigned int &tamano2, unsigned int &tamanoH, string &documento);

void actualizarHistorico(Reserva **reservas,unsigned int &tamano);

void cancelareserva(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento* alojamientos,unsigned short int &decision,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA,string &documento,string &codigo);

#endif // FUNCIONES_H
