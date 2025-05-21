#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <alojamiento.h>
#include <anfitrion.h>
#include <huesped.h>
#include <reserva.h>

using namespace std;

unsigned int cantidadLineas(string nombre){
    ifstream archivo( nombre, ios::ate); // abre y posiciona al final

    if (!archivo) {
        cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    streampos tamanio = archivo.tellg(); // tamaño total
    string linea;
    char ch;

    for (streamoff i = tamanio - 1; i >= 0; --i) {
        archivo.seekg(i);
        archivo.get(ch);

        if (ch == '\n' && i != tamanio - 1) {
            break;
        }

        linea.insert(linea.begin(), ch);

        if (i == 0) break;  // evita underflow
    }

    unsigned int c = 0;
    string cantidad;
    istringstream iss(linea);
    iss >> cantidad;
    cantidad.erase(0,1);
    archivo.close();

    return (c = stoi(cantidad));
}

void crearAlojamientos(Alojamiento *alojamientos,Anfitrion *anfitriones){
    fstream archivo;
    string linea;
    archivo.open("Alojamientos.txt");
    if(!archivo){
        cerr<<"No se pudo abrir "<<endl;
        return nullptr;
    }
    string codigo, documento, puntuacion, antiguedad, tipo, ubicacion, direccion, amenidades, precio;

    unsigned int c = 0;

    while(getline(archivo,linea)){
        stringstream iss(linea);
        iss << codigo << documento <<puntuacion << antiguedad << tipo << ubicacion << direccion << precio << amenidades;

        anfitriones[c] = Anfitrion(puntuacion,antiguedad,documento,nullptr);

        alojamientos[c] = new Alojamiento(codigo,*(anfitriones[c].getDocumento()),stoi(tipo),ubicacion,direccion,stoi(precio),amenidades,nullptr);

        anfitriones[c].setCodigo();

    }
}


