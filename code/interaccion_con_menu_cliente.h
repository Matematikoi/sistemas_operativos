#ifndef MENU_CLIENTE
#define MENU_CLIENTE
#include "mensaje.h"
#include <string>
#define RUTA_HISTORIA_CLINICA_TEMPORAL "historiaClinicaTemporal"
Mensaje menu(std::string respuestaTamano);
Mensaje anadir_reg();
Mensaje ver_reg();
Mensaje borrar_reg();
Mensaje buscar_reg();
std::string editarHistoriaClinica(std::string historiaClinicaOriginal);

#endif