#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>
#include "Funciones.h"

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
            cout<<"El municipi ingresado posee caracteres invalidos (en caso de ser ñ usar n)"<<endl;
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
    cout<<"Lo sentimos actualmente no hay ningun alojamiento disponible en este municipio"<<endl;
    return false;
}

string codigoR(string codigo){
    unsigned int codigopr;
    codigopr = stoi(codigo);
    codigopr += 1;
    return to_string(codigopr);
}

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

void comentario(string codigoR){
    string comentario;
    unsigned short int contador;
    cout<<"Que deseas comentar/preguntar al anfitrion?" <<endl;
    do{
        contador = 0;
        cout<<"Recuerda tienes maximo 1000 caracteres no te preocupes si te pasas te lo recordare "<<endl;
        getline(cin >> ws, comentario);
        for (char c : comentario) {
            if (c != ' ') {
                contador++;
            }
        }
    }while(contador>1000);
    ofstream archivo("Comentarios.txt", ios::app);
    if(!archivo){
        cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    archivo<<codigoR << " "<< comentario <<endl;
    archivo.close();
}

void ingresar_sistema(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento* alojaminetos,unsigned int &contan,unsigned int &conthu,unsigned int &contR,unsigned int &contA){
    unsigned short int decision;
    bool bandera = false;
    string documento;
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
               anfitriones[i].menu();
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
                huespedes[i].menu(huespedes,anfitriones,alojaminetos,reservas,contan,conthu,contR,contA);
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
            if(huespedes[i].getDocumento() == reservas[j]->getDocumento()){
                huespedes[i].setReserva(reservas[j]);
            }
        }
    }
}

bool usofiltro(Alojamiento& alojamientos){
    unsigned short int decision;
    unsigned int precio;
    float puntuacion;
    bool retorno;
    do{
        cout<<"0. Filtrar por valor maximo y puntuacion minima "<<endl;
        cout<<"1. Filtar unicamento por puntuacion minima"<<endl;
        cout<<"2. Filtrar unicamento por valor maximo"<<endl;
        cout<<"QUE DESEA?: "<<endl;
        cin >> decision;
    }while((decision < 0) && (decision > 2));
    switch (decision) {
    case 0:
        cout<<"Ingrese el valor maximo"<<endl;
        cin>>precio;
        cout<<"Ingrese la puntuacion minima"<<endl;
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
    unsigned short int noches,decision,contador = 200,valor;
    unsigned int monto;
    bool bandera = false;
    string* arr = new string[contador];
    Fecha nuevfecha;
    string* ptrdocumento = &documento;
    contador = 0;
    do{
    cout<<"porfavor ingresar una fecha en formato dia/mes/anio: "<<endl;
    cin>>fecha;
    nuevfecha = Fecha(fecha);
    }while(!nuevfecha.fechaValida());

    do{
        cout<<"porfavor ingresar un municipio: "<<endl;
        cin>>municipio;
        municipio = aMinuscula(municipio);
    }while(!Sintaxisvalida(municipio)||!municipioexiste(alojamientos,tamano1,municipio) );

    cout<<"Porfavor ingresar una cantidad de noches: "<<endl;
    cin>> noches;

    for(unsigned int i = 0; i<tamano1;i++){
        if(alojamientos[i].disponibilidad(fecha,noches,municipio)){
            cout<<"El alojamiento corresponde al ------"<<alojamientos[i].getCodigo()<<endl;
            arr[contador] = alojamientos[i].getCodigo();
            bandera = true;
            contador++;
        }
    }
    if(bandera == false){
        cout<<"Lo sentimos no tenemos alojamientos disponibles"<<endl;
        return;
    }
    string* arr2 = new string[contador];
    for (int i = 0; i < contador; ++i) {
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;


    cout<<"Deseas filtrar por valor maximo, puntuacion minima?"<<endl;
    do{
        cout<<"1. para si \n 0. para no"<<endl;
        cin >> decision;
    }while(decision != 0 && decision != 1);
    bandera = false;
    if(decision == 1){
        delete[] arr;
        arr = new string[contador];
        contador = 0;
        for(unsigned int i = 0; i<tamano1;i++){
            if(alojamientos[i].disponibilidad(fecha,noches,municipio)){//cambiar en arr i agregar solo los indices
                if(usofiltro(alojamientos[i])){
                    arr[contador] = alojamientos[i].getCodigo();
                    bandera = true;
                    contador++;
                }
            }
        }
        if(bandera == false){
            cout<<"Lo sentimos no tenemos alojamientos disponibles"<<endl;
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
    cout<<"Que alojamiento a sido de su agrado?"<<endl;
    do{
        cout<<"RECUERDA: abajo de cada alojamiento hay un numero identificador 100001,100002,..."<<endl;
        cout<<"ingresa el numero identificador del alojamiento que deseas: "<<endl;
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
    cout<<"El total de su reserva es de: "<< monto <<endl;
    do{
        cout<<"por que metodo desa pagar? \n0.PSE \n1.TCREDITO"<<endl;
        cin>>valor;
    }while((valor != 0) && (valor != 1));

    string codigoRe = codigoR(reservas[tamano2-1]->getCodigo());
    cout<<"Desea agregar un comentario/pregunta al anfitrion? \n1.para si \n2.para no"<<endl;
    cin >> decision;
    if(decision == 1){
        comentario(codigoRe);
    }

    reservas[tamano2] = new Reserva(ptrdocumento, fecha, noches,codigoRe,codigo,valor,obtenerFechaActual(),monto); // Asegúrate de tener este constructor
    alojamientos[contador].setReserva(reservas[tamano2]);        // Agrega la reserva al alojamiento
    reservas[tamano2 ]->comprobante(nuevfecha.sumar_noches(noches));
    tamano2++;
}

bool puedecancelar(Huesped* huespedes, Anfitrion* anfitriones,
                   unsigned int& contan, unsigned int& conthu,
                   string& documento, string& codigo, unsigned short int& decision) {
    bool bandera = false;

    if (decision == 1) { // Anfitrión
        for (unsigned int i = 0; i < contan; i++) {
            if (*(anfitriones[i].getDocumento()) == documento) {
                unsigned int cantAlojamientos = anfitriones[i].getcontaAlojamientos();
                for (unsigned int k = 0; k < cantAlojamientos; k++) {
                    Alojamiento* aloj = anfitriones[i].getAlojamiento(k);
                    if (aloj != nullptr) {
                        unsigned int cantReservas = aloj->getCount();
                        for (unsigned int j = 0; j < cantReservas; j++) {
                            Reserva* r = aloj->getReserva(j);
                            if (r != nullptr && r->getCodigo() == codigo) {
                                bandera = true;
                                break;
                            }
                        }
                    }
                    if (bandera) break;
                }
            }
            if (bandera) break;
        }
    } else { // Huésped
        for (unsigned int i = 0; i < conthu; i++) {
            if (*(huespedes[i].getDocumento()) == documento) {
                unsigned int cantReservas = huespedes[i].getcount();
                for (unsigned int j = 0; j < cantReservas; j++) {
                    Reserva* r = huespedes[i].getReserva(j);
                    if (r != nullptr && r->getCodigo() == codigo) {
                        bandera = true;
                        break;
                    }
                }
            }
            if (bandera) break;
        }
    }
    return bandera;
}


void cancelareserva(Huesped *huespedes,Anfitrion *anfitriones,Reserva **reservas,Alojamiento* alojamientos,
                    unsigned short int &decision,unsigned int &contan,unsigned int &conthu,unsigned int &contR,
                    unsigned int &contA,string &documento,string &codigo){
    if((puedecancelar(huespedes,anfitriones,contan,conthu,documento,codigo,decision))){
        for(unsigned int i = 0; i < conthu; i++) {
            Huesped& h = huespedes[i];
            for (unsigned int j = 0; j < conthu; j++) {
                Reserva* r = h.getReserva(j);
                if (r != nullptr && r->getCodigo() == codigo) {
                    // Cancelar en el huésped
                    h.cancelReserva(j);  // Debes implementar este método

                    // Cancelar en alojamiento asociado
                    string codAloj = r->getCodigoA(); // código del alojamiento
                    for (unsigned int a = 0; a < contA; a++) {
                        if (alojamientos[a].getCodigo() == codAloj) {
                            alojamientos[a].cancelareserva(codigo);
                            break;
                        }
                    }

                    // Cancelar en arreglo global
                    for (unsigned int m = 0; m < contR; m++) {
                        if (reservas[m] != nullptr && reservas[m]->getCodigo() == codigo) {
                            delete reservas[m];
                            reservas[m] = nullptr;
                            break;
                        }
                    }

                    cout << "Reserva cancelada con exito.\n";
                    return;
                }
            }
        }
    }
}
