#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;

class Huesped;
class Anfitrion;
class Reserva;
class Alojamiento;

string obtenerFechaActual();

string aMinuscula(string &str);

bool Sintaxisvalida(const string& municipio);

bool municipioexiste(Alojamiento* alojamientos,unsigned int &tamano,string &municipio);

string codigoR(string codigo);

void actualizarpermanentereserva(Reserva **reservas,Huesped* huespedes, unsigned int contR, unsigned int conthu);

void comentario(string codigoR);

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento* alojaminetos,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA);

void cantidadLineas(string nombre, unsigned int &conta1,unsigned int &conta2);

void crearAnfitriones(Alojamiento* alojamientos, Anfitrion* anfitriones);

void crearHuespedes(Reserva** reservas, Huesped* huespedes);

void asignarReservasA(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2);

void asignarReservah(Huesped* huespedes,Reserva* reservas,unsigned int &tamano1, unsigned int &tamano2);

bool usofiltro(Alojamiento &alojamientos);

void reserva(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2,string &documento);
//void actualizarHistorico(Reserva **reservas,unsigned int tamano);
bool puedecancelar(Huesped* huespedes, Anfitrion* anfitriones,
                   unsigned int& contan, unsigned int& conthu,
                   string& documento, string& codigo, unsigned short int& decision);

void cancelareserva(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento* alojamientos,unsigned short int &decision,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA,string &documento,string &codigo);

#endif // FUNCIONES_H
