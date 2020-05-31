#include <bits/stdc++.h>
#include "mascotas.h"
#include "interaccion_con_menu_cliente.h"
using namespace std;

void enviarMensaje(){
    //con esta funcion se envia al server la info
}
string mensajeRecibido(){
    //con esta funcion se recibe la respuesta del server
}
void romperConexion(){
    //funcion con la que se rompe conexion al server
}
int main (){
    Mensaje mensaje;
    do {
        mensaje = menu();
        if (mensaje.tipoDeMensaje == ROMPER_CONEXION){
            romperConexion();
            break;
        }
        enviarMensaje();
        string respuesta =  mensajeRecibido();
        cout <<respuesta<<endl;
        system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
        system("clear");
    }while(true);

}