#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "interaccion_con_menu_servidor.h"
using namespace std;

Mensaje escucharCliente(){
    Mensaje mensaje;
    //funcion que lee la peticion del cliente
    return mensaje;
}
void enviarACliente(string * data){
    //funcion que envia al cliente un string
}
int main (){
    //alistar algunas variables
    ifstream mascotasArray (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    TAMANO_REAL =  mascotasArray.tellg() / sizeof(Mascota);
    TAMANO_ACTUAL= leer_tamano();
    mascotasArray.close();
    ifstream archivoIDs(ARCHIVO_IDS, ios::in|ios::binary|ios::ate);
    TAMANO_ID = archivoIDs.tellg() / sizeof(int);
    archivoIDs.close();


    RespuestaServidor respuesta;
    Mensaje mensaje;
    do {
        mensaje = escucharCliente();
        respuesta = recibirMensajeCliente(mensaje);
        string mensajeCasteado = respuestaToString(respuesta, mensaje);
        enviarACliente(&mensajeCasteado);
    }while(true);

}