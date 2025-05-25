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
    Reserva *reservas[365];
    unsigned short int count = 0;
public:
    Alojamiento();//Constructor por defecto
    Alojamiento(const string& _nombre, const string& _codigo, string* _documento,
                bool _tipo, const string& _ubicacion, const string& _direccion,
                unsigned int _precio, const string& _amenidades);
    //
    bool disponibilidad(const string& fechaInicio,unsigned short int noches, const string& municipio);

    //metodo para filtrar por puntuacion y por coste maximo
    //void
    void imprimir() const;

    //Getters
    string getNombre();
    string getCodigo();
    string* getDocumento() const;
    bool getTipo();
    string getUbicacion();
    string getDireccion();
    unsigned int getPrecio();
    string getAmenidades();
    Reserva *getReserva(int index);
    unsigned short int getCount() const;

    //Setters
    void setNombre(const string& _nombre);
    void setCodigo(const string& _codigo);
    void setDocumento(string *_documento);
    void setTipo(const bool &_tipo);
    void setUbicacion(const string &_ubicacion);
    void setDireccion(const string& _direccion);
    void setPrecio(unsigned int _precio);
    void setAmenidades(const string& _amenidades);
    void setReserva(Reserva* _reserva);
};

#endif // ALOJAMIENTO_H
