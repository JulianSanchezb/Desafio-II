#include "anfitrion.h"
#include "alojamiento.h"
#include "huesped.h"
#include "Funciones.h"
#include "FuncionesReserva.h"
#include <iostream>
using namespace std;

Anfitrion::Anfitrion(){
    puntuacion = "";
    antiguedad = "";
    documento = "";
    unsigned short int contaAlojamientos = 0;
    for(int i = 0;i < 100;i++){
        alojamientos[i] = nullptr;
    }
}

Anfitrion::Anfitrion(string _puntuacion, string _antiguedad, string _documento) {
    puntuacion = _puntuacion;
    antiguedad = _antiguedad;
    documento = _documento;
    unsigned short int contaAlojamientos = 0;
    for(int i = 0;i < 100;i++){
        alojamientos[i] = nullptr;
    }
}

void Anfitrion::consultaReserva(unsigned int &contador){
    for (unsigned int i = 0; i < contaAlojamientos; ++i){
        if (alojamientos[i] != nullptr) {
            if(alojamientos[i]->getCount() == 0){
                cout<<"\nNo tiene reservas activas en alojamiento "<<alojamientos[i]->getCodigo()<<"\n";
            }
            for(unsigned short int j = 0; j<alojamientos[i]->getCount();j++){
                contador++;
                if (alojamientos[i]->getReserva(j) != nullptr){
                    (alojamientos[i]->getReserva(j))->mostrar();
                    cout << endl;
                }
            }
        }
    }
    cout<<endl;
}

void Anfitrion::menu(Huesped *huespedes, Alojamiento* alojamiento, Reserva** reservas,unsigned int &tamanoH, unsigned int &tamanoR, unsigned int &tamanoA){
    bool bandera;
    string codigo = "";
    short int decision;
    unsigned int contador = 0;
    do{
        cout<<"\n-----Bienvenido, Anfitrion-----\n\nIngrese el numero de la accion que desea realizar"<<endl;
        cout<<"1.Consultar reservas"<<endl;
        cout<<"2.Cancelar reserva"<<endl;
        cout<<"3.Actualizar historico"<<endl;
        cout<<"4.Salir del menu"<<endl;
        cin>>decision;

        switch (decision) {
        case 1:consultaReserva(contador);
            cout<<"\nSe hicieron "<<contador<<" iteraciones en la ultima funcionalidad\n";
            contador = 0;
            break;
        case 2:
            bandera = false;
            do{
                cout<<"\nIngrese el numero identificador de la reserva que desea cancelar: "<<endl;
                cin >>codigo;
                for (int i = 0; i < contaAlojamientos; ++i) {
                    if(bandera){break;}
                    for(unsigned short int j = 0; j < alojamientos[i]->getCount();j++){
                        contador++;
                        if(alojamientos[i]->getReserva(j) != nullptr){
                            if ((alojamientos[i]->getReserva(j))->getCodigo() == codigo){
                                bandera =  true; // Encontrado
                                break;
                            }
                        }
                    }
                }
            }while(!bandera);
            cancelareserva(huespedes,reservas,alojamiento,tamanoH,tamanoR,tamanoA,codigo,contador);
            cout<<"\nSe hicieron "<<contador<<" iteraciones en la ultima funcionalidad\n";
            contador = 0;
            break;
        case 3:actualizarHistorico(reservas,tamanoR,contador);
            compactarReservas(reservas,tamanoR,contador);

            asignarReservasA(alojamiento,reservas,tamanoA,tamanoR,contador);
            asignarReservah(huespedes,reservas,tamanoH,tamanoR,contador);

            for(unsigned int i = 0;i < ((tamanoA >= tamanoH) ? tamanoA:tamanoH);i++){
                contador++;
                if(i < tamanoA){
                    alojamiento[i].actualizarReservas(contador);
                }
                if(i < tamanoH){
                    huespedes[i].actualizarReservas(contador);
                }
            }
            cout<<"\nSe hicieron "<<contador<<" iteraciones en la ultima funcionalidad\n";
            contador = 0;
            break;
        case 4:cout << "Saliendo del menu..." << endl;break;
        default:
            cout<<"\n!!!OPCION INVALIDA¡¡¡\n";
        }

    }while(decision > 4 || decision < 0);

}

void Anfitrion::imprimir() const {
    cout << "=== Anfitrion ===" << endl;
    cout << "Documento: " << documento << endl;
    cout << "Puntuacion: " << puntuacion << endl;
    cout << "Antigüedad: " << antiguedad << endl;
    cout << "Cantidad de alojamientos: " << contaAlojamientos << endl;
    for (unsigned int i = 0; i < contaAlojamientos; ++i) {
        if (alojamientos[i]) {
            cout << "\nAlojamiento #" << i + 1 << ":" << endl;
            alojamientos[i]->imprimir();  // asumiendo que Alojamiento tiene imprimir()
        }
    }
}

// Getters
string *Anfitrion::getPuntuacion() {
    return &puntuacion;
}

string Anfitrion::getAntiguedad() {
    return antiguedad;
}

string* Anfitrion::getDocumento() {
    return &documento;
}

Alojamiento* Anfitrion::getAlojamiento(unsigned short int index) {
    if (index >= 0 && index < 100 && index < contaAlojamientos) {
        return alojamientos[index];
    }
    return nullptr;
}
unsigned int Anfitrion::getcontaAlojamientos(){
    return contaAlojamientos;
}
// Setters
void Anfitrion::setPuntuacion(const string& _puntuacion) {
    puntuacion = _puntuacion;
}

void Anfitrion::setAntiguedad(const string& _antiguedad) {
    antiguedad = _antiguedad;
}

void Anfitrion::setDocumento(const string& _documento) {
    documento = _documento;
}

void Anfitrion::setAlojamiento(Alojamiento *_alojamiento) {
    alojamientos[contaAlojamientos] = _alojamiento;
    contaAlojamientos++;
}
