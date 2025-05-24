#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>

using namespace std;

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

void crearHuespedes(Reserva* reservas, Huesped* huespedes){
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
        reservas[contaReser] = Reserva(documentoPtr, fechaI, stoi(cantidadN), codigo, codigoA, stoi(metodoP), fechaP, stoi(monto));

        // Asignar la reserva al huésped correcto
        huespedes[indiceHuesped].setReserva(&reservas[contaReser]);
        contaReser++;
    }
    archivo.close();
}

void asignarReservasA(Alojamiento* alojamientos,Reserva* reservas,unsigned int &tamano1, unsigned int &tamano2){
    for(int i = 0;i < tamano1;i++){
        for(int j = 0;j < tamano2;j++ ){
            if(alojamientos[i].getCodigo() == reservas[j].getCodigoA()){
                alojamientos[i].setReserva(&reservas[j]);
            }
        }
    }
}




