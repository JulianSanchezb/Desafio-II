#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include<alojamiento.h>
//#include<anfitrion.h>
//#include<fecha.h>
//#include<huesped.h>
//#include<reserva.h>
using namespace std;

int main() {
    unsigned short int n = 0;
    ifstream archivo;
    string linea;
    archivo.open("Alojamientos.txt",ios::ate);
    if(!archivo){
        cerr<<"No se pudo abrir "<<endl;
        return -1;
    }/*
    while(getline(archivo,linea)){
        Alojamiento *alojamientos[n];
    }
    Anfitrion anfitriones[n];

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

    }*/
    getline(archivo,linea);
    archivo.close();
    cout<<linea;

    return 0;
}
