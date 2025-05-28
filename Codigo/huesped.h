#ifndef HUESPED_H
#define HUESPED_H
#include <string>
using namespace std;

class Reserva;
class Anfitrion;
class Alojamiento;

class Huesped{
private:
    string puntuacion;
    string antiguedad;
    string documento;
    unsigned short int count = 0;
    Reserva *reservas[365];
public:
    Huesped(); // Constructor por defecto
    Huesped(string _puntuacion, string _antiguedad, string _documento);
    void menu(Huesped *huespedes, Alojamiento* alojamientos,Reserva** reservas, unsigned int &tamano2,
              unsigned int &contR, unsigned int &contA);
    //opcion de metodo de verificar si no tiene reserva en la fecha indicada
    bool verificar_valides(string fechaI,unsigned short int noche);
    void imprimir() const;

    void cancelReserva(unsigned int index);

    void actualizarReservas();

    // Getters
    string getPuntuacion();
    string getAntiguedad();
    string* getDocumento();
    const string* getDocumento() const;
    Reserva *getReserva(int index);

    unsigned short int getCount();

    // Setters
    void setPuntuacion(const string& _puntuacion);
    void setAntiguedad(const string& _antiguedad);
    void setDocumento(const string& _documento);
    void setReserva(Reserva* _reserva);
    void setCount(unsigned short _count);
};

#endif // HUESPED_H
