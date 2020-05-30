#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "mensaje.h"
using namespace std;


Mensaje menu();
Mensaje anadir_reg();
Mensaje ver_reg();
Mensaje borrar_reg();
Mensaje buscar_reg();

Mensaje menu(){
	char opcion;
    cout<<("\n\n\n\tMENU");
    cout<<("\n\tIngresar registro\t\tIngrese (1)\n\n");
    cout<<("\tVer registro\t\t\tIngrese (2)\n\n");
    cout<<("\tBorrar registro\t\t\tIngrese (3)\n\n");
    cout<<("\tBuscar Registro\t\t\tIngrese (4)\n\n");
    cout<<("\tSalir\t\t\t\tIngrese (5)\n\n\t");
    cin>>opcion;
    Mensaje mensaje;
	switch(opcion){
		case '1':{
			mensaje = anadir_reg();
			break;
		}
		case '2':{
			mensaje = ver_reg();
			break;
		}
		case '3':{
			mensaje = borrar_reg();
			break;
		}
		case '4':{
			mensaje = buscar_reg();
			break;
		}
		case '5':{
			cout<<("\n\n\t----HA SALIDO DEL PROGRAMA----)\n\n\t");
            mensaje.tipoDeMensaje = ROMPER_CONEXION;
			break;
		}
		
		default:{
			cout<<"\n\n\n\t"<<opcion<<" NO ES UNA OPCION\n";
			break;	
		}
	}
    
    return mensaje;
}

Mensaje anadir_reg(){
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    Mascota m;
    cout<<("\n\tInserte los datos a añadir: \n");
    cout<<("\nInserte el nombre: ");
    cin>>m.nombre;
    cout<<("\nInserte el tipo: ");
    cin>>m.tipo;
    cout<<("\nInserte la edad: ");
    cin>>m.edad;
    cout<<("\nInserte la raza: ");
    cin>>m.raza;
    cout<<("\nInserte la estatura: ");
    cin>>m.estatura;
    cout<<("\nInserte el peso: ");
    cin>>m.peso;
    cout<<("\nInserte el sexo: ");
    cin>>m.sexo;
    mensaje.mascota= m;
    mensaje.tipoDeMensaje = ANADIR_MASCOTA;
    return mensaje;    
}
Mensaje ver_reg(){
    int id;
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    cout << "Inserte el id: ";
    cin>>id;
    mensaje.mascota.id= id;
    mensaje.tipoDeMensaje= VER_MASCOTA;
    return mensaje;  
}
Mensaje borrar_reg(){
    Mensaje mensaje;
    int id;
    memset( &mensaje,0, sizeof(Mensaje));
    cout<<"Escriba el id a borrar: ";
    cin>>id;
    mensaje.mascota.id= id;
    mensaje.tipoDeMensaje= ELIMINAR_MASCOTA;
    return mensaje;  
}
Mensaje buscar_reg(){
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    cout<<"Ingrese el nombre a buscar : ";
    cin>>mensaje.mascota.nombre;
    mensaje.tipoDeMensaje=BUSCAR_MASCOTA;
    return mensaje;    
}
