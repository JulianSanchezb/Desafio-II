#ifndef RESERVA_H
#define RESERVA_H
#include "fecha.h"
#include "huesped.h"
#include <string>
using namespace std;

class Huesped;

class Reserva{
private:
    string *documento;
    Fecha date;
    unsigned short int noches;
    string codigo;
    string codigoA; //Codigo alojamiento
    bool metodoPago;
    Fecha pago;
    unsigned int monto;
    string comentario;
public:
    Reserva();  //Constructor por defecto
    Reserva(string* _documento,string _fechaI,unsigned short int _noches,string _codigo,
            string _codigoA,bool _metodoPago,string _fechaP,unsigned int _monto);       //Constructor

    bool verificarFecha();
    int valor_reserva();
    void comprobante();
    void mostrar() const;

    // Getters
    string* getDocumento() const;   //Hay que verificarlos
    string getDocumentoValor() const;
    Fecha getDate();    //Hay que verificarlos
    unsigned short int getNoches();
    string getCodigo();
    string getCodigoA();
    bool getMetodoPago();
    Fecha getPago();
    unsigned int getMonto();
    string getComentario();

    // Setters
    void setDocumento(string *_documento);   //Hay que verificarlos
    void setDate(const string& _date);   //Hay que verificarlos
    void setNoches(int _noches);
    void setCodigo(const string& _codigo);
    void setCodigoA(string _codigoA);
    void setMetodoPago(bool _metodoPago);
    void setPago(const Fecha& _pago);
    void setMonto(unsigned int _monto);
    void setComentario(const string& _comentario);
};

#endif // RESERVA_H
