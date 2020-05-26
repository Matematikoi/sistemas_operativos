#ifndef MENU_SERVIDOR
#define MENU_SERVIDOR
#include "mensaje.h"

RespuestaServidor recibirMensajeCliente(Mensaje mensaje);
RespuestaServidor eliminarMascota(Mascota mascota);
RespuestaServidor anadirMascota(Mascota mascota);
RespuestaServidor verMascota(Mascota mascota);
RespuestaServidor buscarMascota(Mascota mascota);

#endif