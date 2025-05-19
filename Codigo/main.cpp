#include <iostream>
using namespace std;

int main() {

    unsigned short int entrada;
    cout<<"BIENVENIDO A UDEA STAY  \nEs usted Anfitrion o Huesped \n1. Anfitrion \n2. Huesped"<<endl;
    cin >> entrada;
    while(entrada > 2 && entrada < 1){
        cout<<"El numero ingresado no tiene accion: \nEs usted Anfitrion o Huesped \n1. Anfitrion \n2. Huesped"<<endl;
        cin >> entrada;
    }
    if(entrada == 1){

    }else{

    }
    return 0;
}
