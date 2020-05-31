#include <bits/stdc++.h>
#include "mensaje.h"
#include "interactuar_archivos.h"
using namespace std;
RespuestaServidor recibirMensajeCliente(Mensaje mensaje);
RespuestaServidor eliminarMascota(Mascota mascota);
RespuestaServidor anadirMascota(Mascota mascota);
RespuestaServidor verMascota(Mascota mascota);
RespuestaServidor buscarMascota(Mascota mascota);
string toString(RespuestaServidor respuesta);
bool comparar_nombres (char *s1, char *s2);
int procesar_nombre (char* original, char* resultado);


RespuestaServidor recibirMensajeCliente(Mensaje mensaje){
    RespuestaServidor respuestaServidor;
    switch (mensaje.tipoDeMensaje){
        case ELIMINAR_MASCOTA:
            respuestaServidor= eliminarMascota(mensaje.mascota);
            break;
        case ANADIR_MASCOTA:
            respuestaServidor= anadirMascota(mensaje.mascota);
            break;
        case BUSCAR_MASCOTA:
            respuestaServidor= buscarMascota(mensaje.mascota);
            break;
        case VER_MASCOTA:
            respuestaServidor= verMascota(mensaje.mascota);
            break;
        case ROMPER_CONEXION:
            respuestaServidor.romperConexion=true;
            break;

    }
    return respuestaServidor;
}
RespuestaServidor eliminarMascota(Mascota mascota){
    RespuestaServidor respuesta;
    int id = mascota.id;
    int idx =  recuperar_id(id);
    if (idx == -1){
        respuesta.errorEnOperacion = true;
        return respuesta;
    }
    borrar_indice(idx);
    return respuesta;
}
RespuestaServidor anadirMascota(Mascota mascota){
    RespuestaServidor respuesta;
    anadir_mascota(&mascota);
    return respuesta;
}

RespuestaServidor verMascota(Mascota mascota){
    RespuestaServidor respuesta;
    int id = mascota.id;
    int idx =  recuperar_id(id);
    if (idx == -1){
        cout << "IDX -1 \n";
        respuesta.errorEnOperacion = true;
        return respuesta;
    }
    
    //AQUI FALTA VER QUE SE HACE CON LA HISTORIA CLINICA
    //POR QUE NO SE SI LEER Y PASAR STRINGS
    //O SIMPLEMENTE HACERLO LOCAL


    respuesta.mascota=recuperar_indice(idx);
    return respuesta;
}

RespuestaServidor buscarMascota(Mascota mascota){
    RespuestaServidor respuesta;
    respuesta.errorEnOperacion=true;
    int current_hash = hashear_nombre(mascota.nombre);
    if (recuperar_hash(current_hash) == -1){
        respuesta.errorEnOperacion=true;
        return respuesta;
    }else{
        int index=recuperar_hash(current_hash), cnt = 1;
        Mascota ultima  = recuperar_indice( index);
        if (comparar_nombres(ultima.nombre,mascota.nombre)){
            respuesta.busqueda.push_back(ultima);
        }
        while (ultima.siguiente_con_mismo_hash!=-1){
            index = ultima.siguiente_con_mismo_hash;
            ultima = recuperar_indice( index);
            if (comparar_nombres(ultima.nombre,mascota.nombre)){
                respuesta.busqueda.push_back(ultima);
            }
        }
    }
    respuesta.errorEnOperacion=false;
    return respuesta;
}
string mascotaToString(Mascota mascota){
    ostringstream strout;
    strout<< " Nombre: " << mascota.nombre 
        << "\n Tipo: " << mascota.tipo 
        << "\n Edad: " << mascota.edad
        << "\n ID : "<<mascota.id<<endl;
    return strout.str();
}

string respuestaToString(RespuestaServidor respuesta, Mensaje mensaje){
    if (respuesta.errorEnOperacion) {
        return "Error, revise los parametros de entrada";
    }
    string casteo="";
    switch (mensaje.tipoDeMensaje){
    case ELIMINAR_MASCOTA:
        casteo = "Mascota eliminada\n";
        break;
    case VER_MASCOTA:
        casteo = mascotaToString(respuesta.mascota);
        break;
    case ANADIR_MASCOTA:
        casteo = "Mascota anadida\n";
        break;
    case BUSCAR_MASCOTA:
        for (auto mascota : respuesta.busqueda){
            casteo+=mascotaToString(mascota);
        }
        break;
    
    default:
        break;
    }
    return casteo;
}




int procesar_nombre (char* original, char* resultado){
    int tam =0;
    for (int i=0;original[i];++i){
        if('A'<=original[i] && original[i]<'Z'){
            resultado[tam++]=original[i]-'A'+'a';
        }else if('a'<=original[i] && original[i]<'z'){
            resultado[tam++]=original[i];
        }
    }
    return tam;
}

bool comparar_nombres (char *s1, char *s2){
    char s1_procesado[32],s2_procesado[32];
    int tam1 = procesar_nombre(s1,s1_procesado);
    int tam2 = procesar_nombre(s2,s2_procesado);
    if (tam1 != tam2){
        return false;
    }
    for (int i=0;i<tam1;++i){
        if(s1_procesado[i]!=s2_procesado[i]){
            return false;
        }
    }
    return true;
}