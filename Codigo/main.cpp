#include <iostream>
#include <Funciones.cpp>

using namespace std;

int main() {
    unsigned int alojam = 0,anfitri = 0,huesp = 0, reser = 0;

    cantidadLineas("Alojamientos.txt", alojam, anfitri);

    Alojamiento* alojamientos = new Alojamiento[alojam];
    Anfitrion* anfitriones = new Anfitrion[anfitri];

//verificar el tamano de la reserva problema al crear algo nuevo

    crearAnfitriones(alojamientos, anfitriones);
    cantidadLineas("Reservas.txt", reser, huesp);

    Huesped *huespedes =new Huesped[huesp];
    Reserva **reservas = new Reserva*[reser+50];

    crearHuespedes(reservas, huespedes);
    asignarReservasA(alojamientos,reservas,alojam,reser);

    ingresar_sistema(huespedes,anfitriones,alojamientos,reservas,anfitri,huesp,reser,alojam);

    actualizarpermanentereserva(reservas,huespedes,reser,huesp);

    delete[] huespedes;
    delete[] reservas;
    delete[] alojamientos;
    delete[] anfitriones;

    return 0;
}
