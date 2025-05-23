#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>

using namespace std;

void cantidadLineas(string nombre, unsigned int &alojam,unsigned int &anfitri){
    ifstream archivo(nombre); // abre y posiciona al final
    string linea,codigo,documento;
    string arr[100];
    bool comprobacion = true;
    if (!archivo) {
        cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }
    while (getline(archivo,linea)){
        alojam ++;
        stringstream iss(linea);
        iss >>codigo >>nombre>>documento;

        if(alojam == 1){
            arr[0] =  documento;
            anfitri++;
        }

        for(unsigned short int i = 0 ; i < 100 ; i++){
            if(arr[i] == ""){break;}

            if(documento == arr[i]){
                comprobacion = false;
                break;
            }
        }
        if(comprobacion){
            arr[anfitri] = documento;
            anfitri++;
        }else{
            comprobacion = true;
        }
    }
    archivo.close();
}

void crearAlojamientos(Alojamiento* alojamientos, Anfitrion* anfitriones,const unsigned int &alojam, const unsigned int &anfitri) {
    fstream archivo("Alojamientos.txt");
    string linea;
    if (!archivo) {
        cerr << "No se pudo abrir el archivo" << endl;
        return;
    }

    string codigo,nombre, documento, puntuacion, antiguedad, tipo, ubicacion, direccion, amenidades, precio;
    unsigned int contaAlojam = 0,contaAnfitri = 0;
    Alojamiento ptr = nullptr;
    bool bandera = true;

    while (getline(archivo, linea)) {
        stringstream iss(linea);
        iss >> codigo >> nombre >> documento >> puntuacion >> antiguedad >> tipo >> ubicacion >> direccion >> precio >> amenidades;

        if(contaAnfitri == 0){
            anfitriones[contaAnfitri] = Anfitrion(puntuacion, antiguedad, documento);
            bandera = false;
            contaAnfitri++;
        }
        for(int i = 0;i < contaAnfitri ;i++){
            if(documento == anfitriones[i].getDocumento()){
                bandera = false;
                contaAnfitri++;
                break;
            }
        }

        if(bandera){
            anfitriones[contaAnfitri] = Anfitrion(puntuacion, antiguedad, documento);
            contaAnfitri++;
        }
        alojamientos[contaAlojam] = Alojamiento(nombre,codigo, &(anfitriones[c].getDocumento()),
                                                stoi(tipo), ubicacion, direccion, stoi(precio), amenidades, nullptr);

        ptr = alojamientos[contaAlojam];

        contaAlojam++;
        bandera = true;
    }


    archivo.close();
}

