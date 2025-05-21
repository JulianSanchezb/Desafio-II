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
    unsigned int n = 0;
    n = cantidadLineas("Alojamientos.txt");

    Alojamiento *alojamientos[n];

    Anfitrion anfitriones[n];

    crearAlojamientos(&alojamientos,&anfitriones);

    Huesped huespedes[n];

    Reserva *reservas = new Reserva[1000];


    unsigned short int entrada;
    cout<<"BIENVENIDO A UDEA STAY  \nEs usted Anfitrion o Huesped \n1. Anfitrion \n2. Huesped"<<endl;
    cin >> entrada;
    while(entrada > 2 && entrada < 1){
        cout<<"El numero ingresado no tiene accion: \nEs usted Anfitrion o Huesped \n1. Anfitrion \n2. Huesped"<<endl;
        cin >> entrada;
    }
    if(entrada == 1){

    }else{

    }


    return 0;
}
