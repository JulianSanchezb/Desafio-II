#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>
#include <fecha.h>

using namespace std;

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento *alojamientos,unsigned int &contan,unsigned int &conthu,unsigned int contR,unsigned int contal){
    unsigned short int decision;
    bool bandera = false;
    string line,documento;
    do{
        cout<<"Inicio de sesion"<<endl;
        cout<<"1.Anfitrion"<<endl;
        cout<<"2.Huesped"<<endl;
        cout<<"3.salir"<<endl;
        cin>>decision;
    }while((decision>3) && (decision<0));


    switch (decision) {
    case 1:
        cout<<"ingrese el documento del anfitrion: "<<endl;
        cin >> documento;
        for (unsigned int i =0 ;i < contan;i++ ){
            if (*(anfitriones[i].getDocumento()) == documento){
               anfitriones[i].menu(reservas,huespedes,alojamientos,contR,conthu,contal);
                bandera = true;
                break;
            }
        }
        if (!bandera){
            cout<<"Lo sentimos no te encuentras registrado como Anfitrion"<<endl;
        }
    break;
    case 2:
        cout<<"ingrese el documento del huesped: "<<endl;
        cin >> documento;
        for (unsigned int i =0 ;i < conthu;i++ ){
            if (*(huespedes[i].getDocumento()) == documento){
                huespedes[i].menu();
                bandera = true;
                break;
            }
        }
        if (!bandera){
            cout<<"Lo sentimos no te encuentras registrado como huesped"<<endl;
        }
    break;
    case 3:cout << "Saliendo del menu..." << endl;break;
    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
    }
}

void cantidadLineas(string nombre, unsigned int &conta1,unsigned int &conta2){
    ifstream archivo(nombre); // abre y posiciona al final
    string linea,codigo,documento;
    string arr[100];
    bool comprobacion = true;
    if (!archivo) {
        cerr << "No se pudo abrir el archivo.\n";
    }
    while (getline(archivo,linea)){
        conta1 ++;
        stringstream iss(linea);
        iss >>codigo >>nombre>>documento;

        if(conta1 == 1){
            arr[0] =  documento;
            conta2++;
        }

        for(unsigned short int i = 0 ; i < 100 ; i++){
            if(arr[i] == ""){break;}

            if(documento == arr[i]){
                comprobacion = false;
                break;
            }
        }
        if(comprobacion){
            arr[conta2] = documento;
            conta2++;
        }else{
            comprobacion = true;
        }
    }
    archivo.close();
}

void crearAnfitriones(Alojamiento* alojamientos, Anfitrion* anfitriones) {
    fstream archivo("Alojamientos.txt");
    string linea;
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        return;
    }

    string codigo, nombre, documento, puntuacion, antiguedad, tipo, ubicacion, direccion, amenidades, precio;
    unsigned int contaAlojam = 0, contaAnfitri = 0;
    string* documentoPtr = nullptr;

    while (getline(archivo, linea)) {
        stringstream iss(linea);
        iss >> codigo >> nombre >> documento >> puntuacion >> antiguedad >> tipo >> ubicacion >> direccion >> precio >> amenidades;

        int indiceAnfitrion = -1;

        // Buscar si el anfitrión ya existe
        for (int i = 0; i < contaAnfitri; i++) {
            if (documento == *(anfitriones[i].getDocumento())) {
                documentoPtr = anfitriones[i].getDocumento();
                indiceAnfitrion = i;
                break;
            }
        }

        // Si no existe, crearlo
        if (indiceAnfitrion == -1) {
            anfitriones[contaAnfitri] = Anfitrion(puntuacion, antiguedad, documento);
            documentoPtr = anfitriones[contaAnfitri].getDocumento();
            indiceAnfitrion = contaAnfitri;
            contaAnfitri++;
        }

        // Crear alojamiento
        alojamientos[contaAlojam] = Alojamiento(nombre, codigo, documentoPtr,
                                                stoi(tipo), ubicacion, direccion, stoi(precio), amenidades);

        // Asignar el alojamiento al anfitrión correcto
        anfitriones[indiceAnfitrion].setAlojamiento(&alojamientos[contaAlojam]);

        contaAlojam++;
    }
    archivo.close();
}

void crearHuespedes(Reserva** reservas, Huesped* huespedes){
    fstream archivo("Reservas.txt");
    string linea;
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        return;
    }

    string codigo, codigoA, documento, puntuacion, antiguedad, fechaI, cantidadN, fechaP, metodoP, monto;
    unsigned int contaReser = 0, contaHuesp = 0;
    string* documentoPtr = nullptr;

    while (getline(archivo, linea)) {
        stringstream iss(linea);
        iss >> codigo >> codigoA >> documento >> puntuacion >> antiguedad >> fechaI >> cantidadN >> fechaP >> metodoP >> monto;

        int indiceHuesped = -1;

        // Buscar si el huésped ya existe
        for (int i = 0; i < contaHuesp; i++) {
            if (documento == *(huespedes[i].getDocumento())) {
                documentoPtr = huespedes[i].getDocumento();
                indiceHuesped = i;
                break;
            }
        }

        // Si no existe, crearlo
        if (indiceHuesped == -1) {
            huespedes[contaHuesp] = Huesped(puntuacion, antiguedad, documento);
            documentoPtr = huespedes[contaHuesp].getDocumento();
            indiceHuesped = contaHuesp;
            contaHuesp++;
        }

        // Crear reserva
        Reserva *ptr = new Reserva(documentoPtr, fechaI, stoi(cantidadN), codigo, codigoA, stoi(metodoP), fechaP, stoi(monto));
        reservas[contaReser] = ptr;

        // Asignar la reserva al huésped correcto
        huespedes[indiceHuesped].setReserva(reservas[contaReser]);
        contaReser++;
    }
    archivo.close();
}

void asignarReservasA(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2){
    for(int i = 0;i < tamano1;i++){
        for(int j = 0;j < tamano2;j++ ){
            if(alojamientos[i].getCodigo() == reservas[j]->getCodigoA()){
                alojamientos[i].setReserva(reservas[j]);
            }
        }
    }
}

void asignarReservah(Huesped* huespedes,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2){
    for(int i = 0;i < tamano1;i++){
        for(int j = 0;j < tamano2;j++ ){
            if(*(huespedes[i].getDocumento()) == (reservas[j]->getDocumentoValor())){
                huespedes[i].setReserva(reservas[j]);
            }
        }
    }
}

void actualizarHistorico(Reserva **reservas,unsigned int tamano){
    Fecha fechai,fechaCorte;
    string fecha;
    unsigned int indice = 0;
    for(unsigned int i = 0;i < tamano;i++){
        if(reservas[i]){
            fechai = reservas[i]->getDate();
            indice = i;
            break;
        }
    }
    do{
        do{
            cout<<"\nIngrese la fecha de corte teniendo en cuenta las que hay activas en el momento \nLa fecha minima es: "; fechai.mostrar();cout<<"\nIngrese la fecha con el formato d/m/aaaa\n";
            cin>>fecha;
            fechaCorte = Fecha(fecha);
            if(!fechaCorte.fechaValida()){
                cout<<"\nLO INGRESADO NO ES UNA FECHA VALIDA, INGRESE UNA FECHA NUEVAMENTE\n";
            }
        }while(!fechaCorte.fechaValida());
        if(fechai > fechaCorte){
            cout<<"\nLA FECHA INGRESADA ES ANTERIOR A LA DISPONIBLE\nIngrese una fecha nuevamente\n";
        }
    }while(fechai > fechaCorte);

    ofstream archivo("Historico reservas.txt",ios::app);
    if(!archivo){
        cerr<<"\nEl archivo "<<"Historico reservas.txt"<<"no se puedo abrir\n";
        return;
    }

    for(unsigned int i = indice;i < tamano;i++){
        if(reservas[i]){
            if(reservas[i]->getDate() < fechaCorte){
                archivo <<reservas[i]->getCodigo()<<" "<<reservas[i]->getCodigoA()<<" "<<reservas[i]->getDocumentoValor()<<" "
                        <<(reservas[i]->getDate()).getDia()<<"/"<<(reservas[i]->getDate()).getMes()<<"/"<<(reservas[i]->getDate()).getAnio()<<" "
                        <<reservas[i]->getNoches()<<" "<<(reservas[i]->getPago()).getDia()<<"/"<<(reservas[i]->getPago()).getMes()<<"/"<<(reservas[i]->getPago()).getAnio()<<" "
                        <<reservas[i]->getMetodoPago()<<" "<<reservas[i]->getMonto()<<endl;
                delete reservas[i];
                reservas[i] = nullptr;
            }else{
                break;
            }
        }
    }
    archivo.close();
}

void compactarReservas(Reserva** reservas, unsigned int& tamano) {
    unsigned int nuevaPos = 0;

    for (unsigned int i = 0; i < tamano; ++i) {
        if (reservas[i] != nullptr) {
            if (i != nuevaPos) {
                reservas[nuevaPos] = reservas[i];
                reservas[i] = nullptr;
            }
            ++nuevaPos;
        }
    }
    tamano = nuevaPos;
}



