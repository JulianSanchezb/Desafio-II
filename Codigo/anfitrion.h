#ifndef ANFITRION_H
#define ANFITRION_H
#include "alojamiento.h"
#include <string>
using namespace std;


class Anfitrion{
private:
    string puntuacion;
    string antiguedad;
    string documento;
    string *alojamientos[20];
    unsigned short int cont = 0;
public:
    Anfitrion(string _puntuacion, string _antiguedad, string *_documento, string _alojamientos);
    void consultaReserva();
    void menu();
    //Getters
    string getPuntuacion();
    string getAntiguedad();
    string getDocumento();
    string* getAlojamiento(int index);
    // Setters
    void setPuntuacion(const string& _puntuacion);
    void setAntiguedad(const string& _antiguedad);
    void setDocumento(const string& _documento);
    void setAlojamiento(int index, string* _alojamiento);
};

#endif // ANFITRION_H
