#include <bits/stdc++.h>
#include "mascotas.h"
#include "mensaje.h"
#include "interactuar_archivos.h"
#include "interaccion_con_menu_servidor.h"
using namespace std;
RespuestaServidor recibirMensajeCliente(Mensaje mensaje);
RespuestaServidor eliminarMascota(Mascota mascota);
RespuestaServidor anadirMascota(Mascota mascota);
RespuestaServidor verMascota(Mascota mascota);
RespuestaServidor buscarMascota(Mascota mascota);
RespuestaServidor cambiarHistoriaClinicaEnServer(Mascota mascota);
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
        case HISTORIA_CLINICA:
            respuestaServidor = cambiarHistoriaClinicaEnServer(mensaje.mascota);
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
    strout<< "\n Nombre: " << mascota.nombre 
        << "\n ID : "<<mascota.id
        << "\n Tipo: " << mascota.tipo 
        << "\n Edad: " << mascota.edad
        << "\n Raza: " << mascota.raza
        << "\n Estatura: "<<mascota.estatura
        << "\n Peso: " << mascota.peso
        << "\n Sexo: " << mascota.sexo
        <<endl;
    return strout.str();
}

string respuestaToString(RespuestaServidor respuesta, Mensaje mensaje){
    if (respuesta.errorEnOperacion) {
        return "Error, revise los parametros de entrada";
    }
    string casteo="Tamano del archivo : " + to_string(TAMANO_ACTUAL)+ "\n";
    switch (mensaje.tipoDeMensaje){
    case ELIMINAR_MASCOTA:
        casteo += "Mascota eliminada\n";
        break;
    case VER_MASCOTA:
        casteo += mascotaToString(respuesta.mascota);
        break;
    case ANADIR_MASCOTA:
        casteo += "Mascota anadida\n";
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
RespuestaServidor cambiarHistoriaClinicaEnServer(Mascota mascota){
    RespuestaServidor respuesta;
    respuesta.historiaClinica = obtenerHistoriaClinica(mascota);
    return respuesta;
}

char* obtenerRutaHistoriaClinica( Mascota * mascota){
    char * ruta = (char*) malloc (100);
    sprintf(ruta, "%s/%d.txt","historia_clinica", mascota->id);
    return ruta; 
}

string obtenerHistoriaClinica(Mascota mascota){
    char * ruta = obtenerRutaHistoriaClinica(&mascota);
    return leerHistoriaClinica(ruta);
}
void cambiarHistoriaClinica(Mascota mascota, string nuevaHistoriaClinica){
    char * ruta = obtenerRutaHistoriaClinica(&mascota);
    escribirHistoriaClinica(ruta,nuevaHistoriaClinica);
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