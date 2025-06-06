#include "FuncionesReserva.h"
#include <iostream>
#include <alojamiento.h>
#include <anfitrion.h>
#include <reserva.h>
#include <huesped.h>
#include <sstream>
#include <fstream>
#include <ctime>
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

bool municipioexiste(Alojamiento* alojamientos,unsigned int &tamano,string &municipio,unsigned int &contador){
    string departamento,auxmun,aux;
    for(unsigned int i = 0; i<tamano;i++){
        contador++;
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

bool huespedDisponible(Huesped* huespedes, unsigned int tamano, const string& documento, const string& fecha, unsigned short int noches,unsigned int &contador) {
    for (unsigned int i = 0; i < tamano; ++i) {
        contador++;
        if (*(huespedes[i].getDocumento()) == documento) {
            return huespedes[i].verificar_valides(fecha, noches,contador);
        }
    }
    return false; // huésped no encontrado o no disponible
}

string codigoR(string codigo){
    unsigned int codigopr;
    codigopr = stoi(codigo);
    codigopr += 1;
    return to_string(codigopr);
}

void comentario(string codigoR){
    string comentario;
    unsigned short int contador;
    cout<<"Que deseas comentar/preguntar al anfitrion?" <<endl;
    do{
        contador = 0;
        cout<<"Recuerda tienes maximo 1000 caracteres; pero no te preocupes, si te pasas, te lo recordare "<<endl;
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

bool usofiltro(Alojamiento& alojamientos,unsigned int precio,float puntuacion,unsigned short int decision){

    bool retorno = false;

    switch (decision) {
    case 1:
        retorno = alojamientos.filtro(puntuacion,precio,0);
        return retorno;
    case 2:
        retorno = alojamientos.filtro(puntuacion,0,1);
        return retorno;
    case 3:
        retorno = alojamientos.filtro(0.0,precio,2);
        return retorno;
    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
    }
    return retorno;
}

void reserva(Alojamiento* alojamientos,Reserva** reservas,Huesped* huespedes,
             unsigned int &tamano1, unsigned int &tamano2,unsigned int &tamanoH,string &documento,unsigned int &contadoriteraciones){

    string fecha,municipio,codigo;//veroicar el tamano del arreglo
    unsigned short int noches,decision,contador = 200,valor;
    unsigned int monto;
    bool bandera = false;
    string* arr = new string[contador];
    Fecha nuevfecha;
    string* ptrdocumento = &documento;
    contador = 0;

    do{
        cout<<"\nPorfavor ingresar un municipio: "<<endl;
        cin>>municipio;
        municipio = aMinuscula(municipio);
    }while(!Sintaxisvalida(municipio)||!municipioexiste(alojamientos,tamano1,municipio,contadoriteraciones) );

    cout<<"\nPorfavor ingresar una cantidad de noches: "<<endl;
    cin>> noches;

    do{
        cout<<"\nPorfavor ingresar una fecha en formato dia/mes/anio: "<<endl;
        cin>>fecha;
        nuevfecha = Fecha(fecha);
        bandera = huespedDisponible(huespedes,tamanoH,documento,fecha,noches,contadoriteraciones);
        string fechah = obtenerFechaActual();
        Fecha hoy(fechah);
        if(!nuevfecha.fechaValida() ||  !bandera){
            cout<<"Fecha invalida por formato o tiene una reserva activa en dicha fecha"<<endl;
        }
        if(nuevfecha < hoy){
            cout<<"Fecha invalida debe ser mayor a la fecha de hoy: "<<fechah<<endl;
            bandera = false;
        }
    }while(!nuevfecha.fechaValida() ||  !bandera);

    for(unsigned int i = 0; i < tamano1;i++){
        contadoriteraciones++;
        if(alojamientos[i].disponibilidad(fecha,noches,municipio,contadoriteraciones)){
            alojamientos[i].imprimir();
            cout<<"\n-----El alojamiento corresponde al codigo: ------ \n==========="<<alojamientos[i].getCodigo()<<"============"<<endl;
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
        contadoriteraciones ++;
        arr2[i] = arr[i];
    }
    delete[] arr;
    arr = arr2;

    cout<<"\nDeseas filtrar por valor maximo, puntuacion minima?"<<endl;
    do{
        cout<<"1. para si \n2. para no"<<endl;
        cin >> decision;
    }while(decision != 2 && decision != 1);

    bandera = false;

    unsigned int precio = 0;
    float puntuacion = 0;

    if(decision == 1){
        do{
            cout<<"\nEscoja la opcion que desee: "<<endl;
            cout<<"1. Filtrar por valor maximo y puntuacion minima "<<endl;
            cout<<"2. Filtar unicamente por puntuacion minima"<<endl;
            cout<<"3. Filtrar unicamente por valor maximo"<<endl;
            cin >> decision;
        }while((decision < 1) || (decision > 3));
        switch (decision) {
        case 1:
            cout<<"\nIngrese el valor maximo"<<endl;
            cin>>precio;
            cout<<"\n\nIngrese la puntuacion minima"<<endl;
            do{
                cout<<"Entre 0.0-5.0"<<endl;
                cin>>puntuacion;
            }while((puntuacion < 0.0) || (puntuacion > 5.0) );

            break;
        case 2:
            cout<<"Ingrese la puntuacion minima"<<endl;
            do{
                cout<<"Entre 0.0-5.0"<<endl;
                cin>>puntuacion;
            }while((puntuacion<0.0) && (puntuacion>5.0) );

            break;
        case 3:
            cout<<"\nIngrese el valor maximo"<<endl;
            cin>>precio;

            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

        delete[] arr;
        arr = new string[contador];
        contador = 0;
        for(unsigned int i = 0; i < tamano1;i++){
            contadoriteraciones ++;
            if(alojamientos[i].disponibilidad(fecha,noches,municipio,contadoriteraciones)){//cambiar en arr i agregar solo los indices
                if(usofiltro(alojamientos[i],precio,puntuacion,decision)){
                    arr[contador] = alojamientos[i].getCodigo();
                    alojamientos[i].imprimir();
                    cout<<"\n-----El alojamiento corresponde al codigo: ------ \n==========="<<alojamientos[i].getCodigo()<<"============"<<endl;
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
            contadoriteraciones ++;
            arr2[i] = arr[i];
        }
        delete[] arr;
        arr = arr2;
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
        contadoriteraciones ++;
        if(alojamientos[i].getCodigo() == codigo){
            contador = i;
        }
    }
    monto = alojamientos[contador].getPrecio()* noches;

    cout<<"\nEl total de su reserva es de: $"<< monto <<endl;
    do{
        cout<<"\nPor que metodo desea pagar? \n1.PSE \n2.TCREDITO"<<endl;
        cin>>valor;
    }while((valor != 1) && (valor != 2));
    valor -= 1;
    string codigoRe = codigoR(reservas[tamano2-1]->getCodigo());
    cout<<"\nDesea agregar un comentario/pregunta al anfitrion? \n1.para si \n2.para no"<<endl;
    cin >> decision;
    if(decision == 1){
        comentario(codigo);
    }

    reservas[tamano2] = new Reserva(ptrdocumento, fecha, noches,codigoRe,codigo,valor,obtenerFechaActual(),monto);

    alojamientos[contador].setReserva(reservas[tamano2]);// Agrega la reserva al alojamiento

    reservas[tamano2 ]->comprobante(nuevfecha.sumar_noches(noches));

    tamano2++;
}

void cancelareserva(Huesped *huespedes,Reserva **reservas,Alojamiento* alojamientos,unsigned int &conthu,unsigned int &contR,
                    unsigned int &contA,string &codigo,unsigned int &contador){
    string codAloj = "";
    bool bandera = false;
    unsigned int size = contR;
    if (contA > size) size = contA;

    for(unsigned int i = 0; i < conthu; i++) {
        Huesped& h = huespedes[i];
        for(unsigned int j = 0;j < h.getCount();j++){
            contador++;
            Reserva* r = h.getReserva(j);
            if (r != nullptr && r->getCodigo() == codigo){
                // Cancelar en el huésped
                h.cancelReserva(j);
                // Cancelar en alojamiento asociado
                codAloj = r->getCodigoA(); // código del alojamiento
                bandera  = true;
                break;
            }
        }
        if(bandera) {break;}
    }
    for(unsigned int i = 0;i < size;i++){
        contador++;
        if(i < contA){
            if (alojamientos[i].getCodigo() == codAloj) {
                alojamientos[i].cancelareserva(codigo,contador);
            }
        }
        // Cancelar en arreglo global
        if(i < contR){
            if (reservas[i] != nullptr && reservas[i]->getCodigo() == codigo) {
                delete reservas[i];
                reservas[i] = nullptr;
            }
        }
    }
    cout << "\nReserva cancelada con exito.\n";
    return;
}
