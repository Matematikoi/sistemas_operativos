#ifndef MENSAJE
#define MENSAJE
#include "mascotas.h"
#define ELIMINAR_MASCOTA 0
#define ANADIR_MASCOTA 1
#define BUSCAR_MASCOTA 2
#define VER_MASCOTA 3
#define ROMPER_CONEXION 4
struct Mensaje{
    int tipoDeMensaje;
    Mascota mascota;
};
struct RespuestaServidor{
    Mascota mascota;
    bool romperConexion=false;
    bool errorEnOperacion = false;
};




#endif