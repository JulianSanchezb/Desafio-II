#ifndef ANFITRION_H
#define ANFITRION_H
#include <string>
using namespace std;

class Alojamiento;
class Reserva;
class Huesped;

class Anfitrion{
private:
    string puntuacion;
    string antiguedad;
    string documento;
    Alojamiento *alojamientos[100];
    unsigned short int contaAlojamientos = 0;
public:
    Anfitrion();    //Constructor por defecto
    Anfitrion(string _puntuacion, string _antiguedad, string _documento);
    void consultaReserva(unsigned int &contador);
    void menu(Huesped *huespedes, Alojamiento* alojamientos,Reserva** reservas, unsigned int &tamanoH, unsigned int &tamanoR,unsigned int &tamanoA);
    void imprimir() const;
    //Getters
    string* getPuntuacion();
    string getAntiguedad();
    string* getDocumento();      // Devuelve puntero directo al string documento
    Alojamiento *getAlojamiento(unsigned short index);
    unsigned int getcontaAlojamientos();
    // Setters
    void setPuntuacion(const string& _puntuacion);
    void setAntiguedad(const string& _antiguedad);
    void setDocumento(const string& _documento);
    void setAlojamiento(Alojamiento* _alojamiento);
};

#endif // ANFITRION_H
