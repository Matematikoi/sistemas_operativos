#ifndef INTERACTUAR_CON_ARCHIVOS
#define INTERACTUAR_CON_ARCHIVOS

#include "mascotas.h"

using namespace std;
extern int tamano, tamano_real, tamano_id;

int guardar_tamano(void *arr);

int leer_tamano ();

int recuperar_id (int num_id);
void escribir_al_final_id (int num_idx);
void escribir_id_a_indice(int id, int new_idx);
int recuperar_hash(int h);
void escribir_hash(int h, int new_index);
mascota recuperar_indice(int num_item);
void imprimir_estructura(mascota *m);
void escribir_al_final (mascota *m);
void escribir_mascota_a_indice(int idx, mascota *m);
void borrar_indice(int idx);
void anadir_mascota(mascota *m);

#endif