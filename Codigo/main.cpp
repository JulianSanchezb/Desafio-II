#include <iostream>
#include <Funciones.cpp>

using namespace std;

int main() {
    unsigned int alojam = 0,anfitri = 0,huesp = 0, reser = 0,contador = 0;

    cantidadLineas("Alojamientos.txt", alojam, anfitri,contador);

    Alojamiento* alojamientos = new Alojamiento[alojam];
    Anfitrion* anfitriones = new Anfitrion[anfitri];

//verificar el tamano de la reserva problema al crear algo nuevo

    crearAnfitriones(alojamientos, anfitriones,contador);
    cantidadLineas("Reservas.txt", reser, huesp,contador);

    Huesped *huespedes =new Huesped[huesp];
    Reserva **reservas = new Reserva*[reser+50];

    crearHuespedes(reservas, huespedes,contador);
    asignarReservasA(alojamientos,reservas,alojam,reser,contador);

    cout<<"Se hicieron "<<contador<<" iteraciones en la lectura de datos y se usa el tipo de dato streamstring "<<reser + alojam<<endl;
    cout<<"La memoria usada por concepto de objetos creados es: "<<(Alojamiento::getContador())+(Anfitrion::getContador())+(Huesped::getContador())+(Reserva::getContador())<<" bytes\n\n";

    contador = 0;

    ingresar_sistema(huespedes,anfitriones,alojamientos,reservas,anfitri,huesp,reser,alojam);

    actualizarpermanentereserva(reservas,huespedes,reser,huesp,contador);
    cout<<"Se hicieron "<<contador<<" iteraciones en la escritura de datos en los txt"<<endl;
    cout<<"La memoria usada por concepto de objetos creados es: "<<(Alojamiento::getContador())+(Anfitrion::getContador())+(Huesped::getContador())+(Reserva::getContador())<<" bytes\n\n";

    delete[] huespedes;
    delete[] reservas;
    delete[] alojamientos;
    delete[] anfitriones;

    return 0;
}
