#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#include "anfitrion.h"
#include "reserva.h"
#include <string>
using namespace std;

class Alojamiento{
private:
    string nombre;
    string codigo;
    string *documento;
    bool tipo;
    string ubicacion;
    string direccion;
    unsigned int precio;
    string amenidades;
    Reserva *reservas[20];
    unsigned short int count = 0;
public:
    Alojamiento();
    Alojamiento(string _nombre, string _codigo, string *_documento, bool _tipo, string _ubicacion,
                string _direccion, unsigned int _precio, string _amenidades, Reserva *_reservas);
    //
    void disponibilidad();
    //


    //Getters
    string getNombre();
    string getCodigo();
    string &getDocumento();
    const string &getDocumento();
    bool getTipo();
    string getUbicacion();
    string getDireccion();
    unsigned int getPrecio();
    string getAmenidades();
    //Reserva getReservas();  Falta getter de reservas
    //Setters
    void setNombre(const string& _nombre);
    void setCodigo(const string& _codigo);
    void setDocumento(const string& _documento);
    void setTipo(const bool &_tipo);
    void setUbicacion(const string &_ubicacion);
    void setDireccion(const string& _direccion);
    void setPrecio(unsigned int _precio);
    void setAmenidades(const string& _amenidades);
    //Reserva setReservas();  Falta setter de reservas
};

#endif // ALOJAMIENTO_H
