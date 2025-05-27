#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>

using namespace std;

string obtenerFechaActual() {
    // Obtener el tiempo actual
    time_t t = time(nullptr);
    tm* tiempoLocal = localtime(&t);

    // Extraer día, mes y año
    int dia = tiempoLocal->tm_mday;
    int mes = tiempoLocal->tm_mon + 1; // tm_mon empieza en 0 (enero)
    int anio = tiempoLocal->tm_year + 1900;

    // Convertir a string con formato dd/mm/aaaa
    ostringstream fechaFormateada;
    if (dia < 10) fechaFormateada << "0";
    fechaFormateada << dia << "/";

    if (mes < 10) fechaFormateada << "0";
    fechaFormateada << mes << "/";

    fechaFormateada << anio;

    return fechaFormateada.str();
}

string aMinuscula(string &str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

bool Sintaxisvalida(const string& municipio) {
    for (char c : municipio) {
        if (!isalpha(c) && c != ' ') {
            cout<<"El municipio ingresado posee caracteres invalidos (en caso de ser ñ usar n)"<<endl;
            return false;
        }
    }
    return true;
}

bool municipioexiste(Alojamiento* alojamientos,unsigned int &tamano,string &municipio){
    string departamento,auxmun,aux;
    for(unsigned int i = 0; i<tamano;i++){
        aux = alojamientos[i].getUbicacion();
        stringstream iss(aux);

        getline(iss,departamento,'-');
        getline(iss,auxmun,'-');

        if(municipio == auxmun){
            return true;
        }
    }
    cout<<"\nLo sentimos actualmente no hay ningun alojamiento disponible en este municipio"<<endl;
    return false;
}

string codigoR(string codigo){
    unsigned int codigopr;
    codigopr = stoi(codigo);
    codigopr += 1;
    return to_string(codigopr);
}

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento* alojamientos,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA){
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
                    anfitriones[i].menu(reservas,huespedes,alojamientos,contR,conthu,contA);
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
                    huespedes[i].menu(alojamientos,reservas,contA,contR);
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
    string arr[100];
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

void asignarReservasA(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2){
    for(unsigned int i = 0;i < tamano1;i++){
        for(unsigned int j = 0;j < tamano2;j++ ){

            if(j == 0){
                alojamientos[i].setCount(0);
            }
            if(alojamientos[i].getCodigo() == reservas[j]->getCodigoA()){
                alojamientos[i].setReserva(reservas[j]);
            }

        }
    }
}

void asignarReservah(Huesped* huespedes,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2){

    for(unsigned int i = 0;i < tamano1;i++){
        for(unsigned int j = 0;j < tamano2;j++ ){

            if(j == 1){
                huespedes[i].setCount(0);
            }
            if(*(huespedes[i].getDocumento()) == (reservas[j]->getDocumentoValor())){
                huespedes[i].setReserva(reservas[j]);
            }

        }
    }
}


void actualizarHistorico(Reserva **reservas,unsigned int &tamano){
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
            cout<<"\nIngrese la fecha de corte teniendo en cuenta las que hay activas en el momento \nLa fecha minima es: "; fechai.mostrar();cout<<"\n\nIngrese la fecha en el formato dia/mes/anio\n";
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

bool usofiltro(Alojamiento& alojamientos){
    unsigned short int decision;
    unsigned int precio;
    float puntuacion;
    bool retorno;
    do{
        cout<<"\nEscoja la opcion que desee: "<<endl;
        cout<<"0. Filtrar por valor maximo y puntuacion minima "<<endl;
        cout<<"1. Filtar unicamento por puntuacion minima"<<endl;
        cout<<"2. Filtrar unicamento por valor maximo"<<endl;
        cin >> decision;
    }while((decision < 0) || (decision > 2));
    switch (decision) {
    case 0:
        cout<<"\nIngrese el valor maximo"<<endl;
        cin>>precio;
        cout<<"\nIngrese la puntuacion minima"<<endl;
        do{
            cout<<"Entre 0.0-5.0"<<endl;
            cin>>puntuacion;
        }while((puntuacion<0.0) && (puntuacion>5.0) );
        retorno = alojamientos.filtro(puntuacion,precio,0);
        if(retorno){
          cout<<"El alojamiento corresponde al ------"<<alojamientos.getCodigo()<<endl;
        }
    break;
    case 1:
        cout<<"Ingrese la puntuacion minima"<<endl;
        do{
            cout<<"Entre 0.0-5.0"<<endl;
            cin>>puntuacion;
        }while((puntuacion<0.0) && (puntuacion>5.0) );
        retorno = alojamientos.filtro(puntuacion,0,1);
        if(retorno){
            cout<<"El alojamiento corresponde al ------"<<alojamientos.getCodigo()<<endl;
        }
    break;
    case 2:
        cout<<"Ingrese el valor maximo"<<endl;
        cin>>precio;
        retorno = alojamientos.filtro(0.0,precio,2);
        if(retorno){
            cout<<"El alojamiento corresponde al ------"<<alojamientos.getCodigo()<<endl;
        }
    break;
    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
    }
    return retorno;

}

void reserva(Alojamiento* alojamientos,Reserva** reservas,unsigned int &tamano1, unsigned int &tamano2,string &documento){
    string fecha,municipio,codigo;//veroicar el tamano del arreglo
    unsigned short int noches,decision,contador = 200;
    unsigned int monto;
    bool bandera = false,metodo;
    string* arr = new string[contador];
    Fecha nuevfecha;
    string* ptrdocumento = &documento;
    contador = 0;
    do{
    cout<<"\nPorfavor ingresar una fecha en formato dia/mes/anio: "<<endl;
    cin>>fecha;
    nuevfecha = Fecha(fecha);
    }while(!nuevfecha.fechaValida());

    do{
        cout<<"\nPorfavor ingresar un municipio: "<<endl;
        cin>>municipio;
        municipio = aMinuscula(municipio);
    }while(!Sintaxisvalida(municipio)||!municipioexiste(alojamientos,tamano1,municipio) );

    cout<<"\nPorfavor ingresar una cantidad de noches: "<<endl;
    cin>> noches;

    for(unsigned int i = 0; i<tamano1;i++){
        if(alojamientos[i].disponibilidad(fecha,noches,municipio)){
            cout<<"\n-----El alojamiento corresponde al ------ \n==========="<<alojamientos[i].getCodigo()<<"============"<<endl;
            arr[contador] = alojamientos[i].getCodigo();
            bandera = true;
            contador++;
        }
    }
    if(bandera == false){
        cout<<"\nLo sentimos no tenemos alojamientos disponibles\n"<<endl;
        return;
    }
    string* arr2 = new string[contador];
    for (int i = 0; i < contador; ++i) {
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;


    cout<<"\nDeseas filtrar por valor maximo, puntuacion minima?"<<endl;
    do{
        cout<<"1. para si \n0. para no"<<endl;
        cin >> decision;
    }while(decision != 0 && decision != 1);
    bandera = false;
    if(decision == 1){
        delete[] arr;
        arr = new string[contador];
        contador = 0;
        for(unsigned int i = 0; i<tamano1;i++){
            if(alojamientos[i].disponibilidad(fecha,noches,municipio)){
                if(usofiltro(alojamientos[i])){
                    arr[contador] = alojamientos[i].getCodigo();
                    bandera = true;
                    contador++;
                }
            }
        }
        if(bandera == false){
            cout<<"\nLo sentimos no tenemos alojamientos disponibles\n"<<endl;
            return;
        }
        string* arr2 = new string[contador];
        for (int i = 0; i < contador; ++i) {
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr = arr2;
    }
    for (unsigned short int i =0;i<contador;i++){

    }
    bandera = false;
    cout<<"\nQue alojamiento ha sido de su agrado?"<<endl;
    do{
        cout<<"\nRECUERDE: abajo de cada alojamiento hay un numero identificador 100001,100002,..."<<endl;
        cout<<"\nIngrese el numero identificador del alojamiento que desee: "<<endl;
        cin >>codigo;
        for (int i = 0; i < contador; ++i) {
            if (arr[i] == codigo) {
                bandera =  true; // Encontrado
            }
        }
    }while(!bandera);
    delete[] arr;
    contador = 0;
    for(unsigned int i = 0;i<tamano1;i++){
        if(alojamientos[i].getCodigo() == codigo){
            contador = i;
        }
    }
    monto = alojamientos[contador].getPrecio()* noches;
    cout<<"\nEl total de su reserva es de: $"<< monto <<endl;
    cout<<"\nPor que metodo desea pagar? \n0.PSE \n1.TCREDITO"<<endl;
    cin>>metodo;

    reservas[tamano2] = new Reserva(ptrdocumento, fecha, noches,codigoR(reservas[tamano2-1]->getCodigo()),codigo,metodo,obtenerFechaActual(),monto); // Asegúrate de tener este constructor
    alojamientos[contador].setReserva(reservas[tamano2]);        // Agrega la reserva al alojamiento
    reservas[tamano2]->comprobante(nuevfecha.sumar_noches(noches));
    tamano2++;
}

