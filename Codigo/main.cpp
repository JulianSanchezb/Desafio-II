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
    Reserva *reservas = new Reserva[reser];

    crearHuespedes(reservas, huespedes);

    asignarReservasA(alojamientos,reservas,alojam,reser);

    unsigned short int entrada;
    cout<<"BIENVENIDO A UDEA STAY  \nEs usted Anfitrion o Huesped \n1. Anfitrion \n2. Huesped"<<endl;
    cin >> entrada;
    while(entrada > 2 && entrada < 0){
        cout<<"El numero ingresado no tiene accion: \nEs usted Anfitrion o Huesped \n1. Anfitrion \n2. Huesped"<<endl;
        cin >> entrada;
    }
    if(entrada == 1){

    }else if(entrada == 0){
        for(int i = 0; i < anfitri;i++){
            anfitriones[i].imprimir();
        }
        cout<<"\n\n---------------------Alojamientos---------------------";
        for(int i = 0; i < huesp;i++){
            alojamientos[i].imprimir();
        }
    }
    delete[] alojamientos;
    delete[] anfitriones;

    return 0;
}
