#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
    return (c = stoi(cantidad));
}
