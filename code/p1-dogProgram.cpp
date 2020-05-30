#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "menu.h"
using namespace std;

int main (){
    Mascota m;
    ifstream archivo_mascotas ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    TAMANO_REAL =  archivo_mascotas.tellg() / sizeof(Mascota);
    TAMANO_ACTUAL= leer_tamano();
    archivo_mascotas.close();
    ifstream archivo_ids("binaries/ids.bin", ios::in|ios::binary|ios::ate);
    TAMANO_ID = archivo_ids.tellg() / sizeof(int);
    archivo_ids.close();

    menu();
}


