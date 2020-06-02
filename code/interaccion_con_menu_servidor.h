#ifndef MENU_SERVIDOR
#define MENU_SERVIDOR
#include "mensaje.h"
#include <string>
RespuestaServidor recibirMensajeCliente(Mensaje mensaje);
RespuestaServidor eliminarMascota(Mascota mascota);
RespuestaServidor anadirMascota(Mascota mascota);
RespuestaServidor verMascota(Mascota mascota);
RespuestaServidor buscarMascota(Mascota mascota);
std::string respuestaToString(RespuestaServidor respuesta, Mensaje mensaje);
std::string obtenerHistoriaClinica(Mascota mascota);
void cambiarHistoriaClinica(Mascota mascota, std::string nuevaHistoriaClinica);


#endif