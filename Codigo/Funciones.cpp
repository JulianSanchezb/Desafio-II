#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>

using namespace std;

void actualizarpermanentereserva(Reserva **reservas,Huesped* huespedes, unsigned int contR, unsigned int conthu){
    string puntuacion, antiguedad,doc;
    ofstream archivo("Reservas.txt");
    if(!archivo){
        cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    for (unsigned int i = 0; i < contR; i++) {
        if (reservas[i] != nullptr) {
            doc = *(reservas[i]->getDocumento());
            puntuacion = "N/A";
            antiguedad = "N/A";

            for (unsigned int j = 0; j < conthu; j++) {
                if (*(huespedes[j].getDocumento()) == doc) {
                    puntuacion = (huespedes[j].getPuntuacion());
                    antiguedad = (huespedes[j].getAntiguedad());
                    break;
                }
            }
            archivo << reservas[i]->getCodigo() << " "
                    << reservas[i]->getCodigoA() << " "
                    << *(reservas[i]->getDocumento()) << " "
                    << puntuacion  << " "
                    << antiguedad  << " "
                    << reservas[i]->getDate().mostrar() << " "
                    << reservas[i]->getNoches() << " "
                    << reservas[i]->getPago().mostrar() << " "
                    << reservas[i]->getMetodoPago() << " "
                    << reservas[i]->getMonto() <<endl;
        }
    }
    archivo.close();

}

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Alojamiento* alojamientos,Reserva **reservas,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA){
    short int decision;

    bool bandera = false;
    string documento;
    do{
        bandera = false;
        cout<<"----Inicio de sesion----\n\nIngrese el numero que corresponde a su tipo de perfil o si desea salir del programa.\n";
        cout<<"\n1.Anfitrion"<<endl;
        cout<<"2.Huesped"<<endl;
        cout<<"3.Salir del programa."<<endl;
        cin>>decision;
        switch (decision) {
        case 1:
            cout<<"\nIngrese el documento del anfitrion: "<<endl;
            cin >> documento;
            for (unsigned int i =0 ;i < contan;i++ ){
                if (*(anfitriones[i].getDocumento()) == documento){
                    anfitriones[i].menu(huespedes,alojamientos,reservas,conthu,contR,contA);
                    bandera = true;
                    break;
                }
            }
            if (!bandera){
                cout<<"\nLo sentimos, no te encuentras registrado como Anfitrion\n"<<endl;
            }
            break;
        case 2:
            cout<<"\nIngrese el documento del huesped: "<<endl;
            cin >> documento;
            for (unsigned int i =0 ;i < conthu;i++ ){
                if (*(huespedes[i].getDocumento()) == documento){
                    huespedes[i].menu(huespedes,alojamientos,reservas,conthu,contR,contA);
                    bandera = true;
                    break;
                }
            }
            if (!bandera){
                cout<<"\nLo sentimos no te encuentras registrado como huesped\n"<<endl;
            }
            break;
        case 3:cout << "\nSaliendo del menu...\n" << endl;return;
        default:
            cout << "\nOpcion no valida, intente de nuevo.\n" << endl;
        }
    }while(true);

}

void cantidadLineas(string nombre, unsigned int &conta1,unsigned int &conta2){
    ifstream archivo(nombre); // abre y posiciona al final
    string linea,codigo,documento;
    string arr[600];
    bool comprobacion = true;
    if (!archivo) {
        cerr << "\nNo se pudo abrir el archivo.\n";
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
        cerr << "\nNo se pudo abrir el archivo\n" << endl;
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
        alojamientos[contaAlojam] = Alojamiento(nombre, codigo, documentoPtr,(anfitriones[indiceAnfitrion].getPuntuacion()),
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

        reservas[contaReser] = new Reserva(documentoPtr, fechaI, stoi(cantidadN), codigo, codigoA, stoi(metodoP), fechaP, stoi(monto));

        // Asignar la reserva al huésped correcto
        huespedes[indiceHuesped].setReserva(reservas[contaReser]);
        contaReser++;
    }
    archivo.close();
}

void asignarReservasA(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2,unsigned int &contador){
    for(unsigned int i = 0;i < tamano1;i++){
        for(unsigned int j = 0;j < tamano2;j++ ){
            contador++;
            if(j == 0){
                alojamientos[i].setCount(0);
            }
            if(alojamientos[i].getCodigo() == reservas[j]->getCodigoA()){
                alojamientos[i].setReserva(reservas[j]);
            }
        }
    }
}

void asignarReservah(Huesped* huespedes, Reserva** reservas, unsigned int &tamano1, unsigned int &tamano2, unsigned int &contador){
    for(unsigned int i = 0;i < tamano1;i++){
        for(unsigned int j = 0;j < tamano2;j++ ){
            contador++;
            if(j == 0){
                huespedes[i].setCount(0);
            }
            if(*(huespedes[i].getDocumento()) == (reservas[j]->getDocumentoValor())){
                huespedes[i].setReserva(reservas[j]);
            }
        }
    }
}

void actualizarHistorico(Reserva **reservas,unsigned int &tamano,unsigned int &contador){
    Fecha fechai,fechaCorte;
    string fecha;
    unsigned int indice = 0;

    for(unsigned int i = 0;i < tamano;i++){
        contador++;
        if(reservas[i]){
            fechai = reservas[i]->getDate();
            indice = i;
            break;
        }
    }

    do{
        do{
            cout<<"\nIngrese la fecha de corte teniendo en cuenta las que hay activas en el momento \nLa fecha minima es: "<<fechai.mostrar();
            cout<<"\n\nIngrese la fecha en el formato dia/mes/anio\n";
            cin>>fecha;
            fechaCorte = Fecha(fecha);
            if(!fechaCorte.fechaValida()){
                cout<<"\nLO INGRESADO NO ES UNA FECHA VALIDA\nIngrese una fecha nuevamente\n";
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
        contador++;
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

void compactarReservas(Reserva** reservas, unsigned int& tamano,unsigned int &contador) {
    unsigned int nuevaPos = 0;
    for (unsigned int i = 0; i < tamano; ++i) {
        contador++;
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
