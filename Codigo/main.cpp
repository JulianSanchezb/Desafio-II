#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Funciones.cpp>
//#include<alojamiento.h>
//#include<anfitrion.h>
//#include<fecha.h>
//#include<huesped.h>
//#include<reserva.h>
using namespace std;

int main() {
    unsigned int alojam = 0,anfitri = 0,huesp = 0, reser = 0;
    cantidadLineas("Alojamientos.txt", alojam, anfitri);
    Alojamiento* alojamientos = new Alojamiento[alojam];
    Anfitrion* anfitriones = new Anfitrion[anfitri];

    crearAnfitriones(alojamientos, anfitriones);
    cantidadLineas("Reservas.txt", reser, huesp);

    Huesped *huespedes =new Huesped[huesp];
    Reserva **reservas = new Reserva*[reser+50];

    crearHuespedes(reservas, huespedes);
    asignarReservasA(alojamientos,reservas,alojam,reser);

    ingresar_sistema(huespedes,anfitriones,reservas,alojamientos,anfitri,huesp,reser,alojam);




    delete[] huespedes;
    delete[] reservas;
    delete[] alojamientos;
    delete[] anfitriones;

    return 0;
}
