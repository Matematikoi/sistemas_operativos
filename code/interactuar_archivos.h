#ifndef INTERACTUAR_CON_ARCHIVOS
#define INTERACTUAR_CON_ARCHIVOS

#include "mascotas.h"

using namespace std;
extern int TAMANO_ACTUAL, TAMANO_REAL, TAMANO_ID;

int guardar_tamano(void *arr);

int leer_tamano ();

int recuperar_id (int num_id);
void escribir_al_final_id (int num_idx);
void escribir_id_a_indice(int id, int new_idx);
int recuperar_hash(int h);
void escribir_hash(int h, int new_index);
Mascota recuperar_indice(int num_item);
void imprimir_estructura(Mascota *m);
void escribir_al_final (Mascota *m);
void escribir_mascota_a_indice(int idx, Mascota *m);
void borrar_indice(int idx);
void anadir_mascota(Mascota *m);

#endif