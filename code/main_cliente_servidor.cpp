#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "interaccion_con_menu_servidor.h"
#include "interaccion_con_menu_cliente.h"
using namespace std;


int main (){
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
        mensaje = menu();
        /*if (mensaje.tipoDeMensaje== VER_MASCOTA){
            //hacer cosas de historia clinica.
            respuesta_aux = recibirMensajeCliente(mensaje);
            preguntar_historia_clinica();
        }*/
        respuesta = recibirMensajeCliente(mensaje);
        string mensajeCasteado = respuestaToString(respuesta, mensaje);
        cout<<mensajeCasteado<<endl;
        system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
        system("clear");
    }while(respuesta.romperConexion == false);

}