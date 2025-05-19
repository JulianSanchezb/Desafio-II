#ifndef RESERVA_H
#define RESERVA_H
#include "fecha.h"
#include "huesped.h"


class Reserva{
private:
    Huesped persona;
    Fecha date;
    int noches;
    int codigo;
    int codigoA; //Codigo alojamiento
    bool metodoPago;
    Fecha pago;
    unsigned int monto;
    char comentario[1000];
public:
    bool verificarFecha();
    void comprobante();
};

#endif // RESERVA_H
