#ifndef RESERVA_H
#define RESERVA_H
#include "fecha.h"
#include "huesped.h"
#include <string>
using namespace std;

class Reserva{
private:
    Huesped persona;
    Fecha date;
    int noches;
    string codigo;
    string *codigoA; //Codigo alojamiento
    bool metodoPago;
    Fecha pago;
    unsigned int monto;
    string comentario;
public:
    bool verificarFecha();
    void comprobante();

    // Getters
    Huesped getPersona();   //Hay que verificarlos
    Fecha getDate();    //Hay que verificarlos
    int getNoches();
    string getCodigo();
    string* getCodigoA();
    bool getMetodoPago();
    Fecha getPago();
    unsigned int getMonto();
    string getComentario();

    // Setters
    void setPersona(const Huesped& _persona);   //Hay que verificarlos
    void setDate(const Fecha& _date);   //Hay que verificarlos
    void setNoches(int _noches);
    void setCodigo(const string& _codigo);
    void setCodigoA(string* _codigoA);
    void setMetodoPago(bool _metodoPago);
    void setPago(const Fecha& _pago);
    void setMonto(unsigned int _monto);
    void setComentario(const string& _comentario);
};

#endif // RESERVA_H
