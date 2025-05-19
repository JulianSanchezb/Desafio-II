#ifndef FECHA_H
#define FECHA_H

class Fecha{
private:
    unsigned short int dia;
    unsigned short int mes;
    unsigned short int anio;
public:
    fec(unsigned short int dia,unsigned short int mes,unsigned short int anio);
    bool fechaValida();
    unsigned short int nombreDia(); //Con la formula de Zeller(con division entera)
    bool bisiesto();
};

#endif // FECHA_H
