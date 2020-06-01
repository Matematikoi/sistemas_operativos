#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "interaccion_con_menu_servidor.h"
#include "interaccion_con_menu_cliente.h"
using namespace std;


int main (){
    Mascota m;
    m.id = 2;
    string lecturaDelServer = obtenerHistoriaClinica(m);
    string lecturaDelCliente = editarHistoriaClinica(lecturaDelServer);
    cambiarHistoriaClinica(m, lecturaDelCliente);

}