#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "menu.h"
using namespace std;

int main (){
    mascota m;
    ifstream archivo_mascotas ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    tamano_real =  archivo_mascotas.tellg() / sizeof(mascota);
    tamano= leer_tamano();
    archivo_mascotas.close();
    ifstream archivo_ids("binaries/ids.bin", ios::in|ios::binary|ios::ate);
    tamano_id = archivo_ids.tellg() / sizeof(int);
    archivo_ids.close();

    menu();
}


