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
        respuesta = recibirMensajeCliente(mensaje);
        if (!respuesta.errorEnOperacion){
            cout<<"Operación exitosa\n";
            if (mensaje.tipoDeMensaje==VER_MASCOTA or mensaje.tipoDeMensaje==BUSCAR_MASCOTA){
                imprimir_estructura(&respuesta.mascota);
            }
        }else{
            cout<<"Error en la operación, revise los parametros\n";
        }

    }while(respuesta.romperConexion == false);

}