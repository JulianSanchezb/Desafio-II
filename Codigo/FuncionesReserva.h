#ifndef FUNCIONESRESERVA_H
#define FUNCIONESRESERVA_H
#include <iostream>
using namespace std;

class Huesped;
class Alojamiento;
class Anfitrion;
class Reserva;

string obtenerFechaActual();

string aMinuscula(string &str);

bool Sintaxisvalida(const string& municipio);

bool municipioexiste(Alojamiento* alojamientos,unsigned int &tamano,string &municipio);

bool huespedDisponible(Huesped* huespedes, unsigned int tamano, const string& documento, const string& fecha, unsigned short int noches);

string codigoR(string codigo);

void comentario(string codigoR);

bool usofiltro(Alojamiento& alojamientos,unsigned int precio,float puntuacion,unsigned short int decision);

void reserva(Alojamiento* alojamientos,Reserva** reservas,Huesped* huespedes,
             unsigned int &tamano1, unsigned int &tamano2,unsigned int &tamanoH,string &documento);

void cancelareserva(Huesped *huespedes,Reserva **reservas,Alojamiento* alojamientos,unsigned int &conthu,unsigned int &contA,
                    unsigned int &contR,string &codigo);

#endif // FUNCIONESRESERVA_H
