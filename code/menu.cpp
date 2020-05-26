#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
using namespace std;


void menu();
void anadir_reg();
void ver_reg();
void borrar_reg();
void buscar_reg();
int procesar_nombre (char* original, char* resultado);
bool comparar_nombres (char *s1, char *s2);




void menu(){
    guardar_tamano(&TAMANO_ACTUAL);
    //system("clear");
	char opcion;
    cout<<("\n\n\n\tMENU");
    cout<<("\n\tIngresar registro\t\tIngrese (1)\n\n");
    cout<<("\tVer registro\t\t\tIngrese (2)\n\n");
    cout<<("\tBorrar registro\t\t\tIngrese (3)\n\n");
    cout<<("\tBuscar Registro\t\t\tIngrese (4)\n\n");
    cout<<("\tSalir\t\t\t\tIngrese (5)\n\n\t");
    cin>>opcion;
	switch(opcion){
		case '1':{
			anadir_reg();
			break;
		}
		case '2':{
			ver_reg();
			break;
		}
		case '3':{
			borrar_reg();
			break;
		}
		case '4':{
			buscar_reg();
			break;
		}
		case '5':{
			cout<<("\n\n\t----HA SALIDO DEL PROGRAMA----)\n\n\t");
			break;
		}
		
		default:{
			cout<<"\n\n\n\t"<<opcion<<"NO ES UNA OPCION\n";
			menu();
			break;	
		}
	}
    
}
void anadir_reg(){
    Mascota mascota;
    cout<<("\n\tInserte los datos a añadir: \n");
    cout<<("\nInserte el nombre: ");
    cin>>mascota.nombre;
    cout<<("\nInserte el tipo: ");
    cin>>mascota.tipo;
    cout<<("\nInserte la edad: ");
    cin>>mascota.edad;
    cout<<("\nInserte la raza: ");
    cin>>mascota.raza;
    cout<<("\nInserte la estatura: ");
    cin>>mascota.estatura;
    cout<<("\nInserte el peso: ");
    cin>>mascota.peso;
    cout<<("\nInserte el sexo: ");
    cin>>mascota.sexo;
    anadir_mascota(&mascota);
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
}
void ver_reg(){
    cout<<"\nExisten "<<TAMANO_ACTUAL<<" registros en la base de datos\nEscriba el id a buscar: ";
    int id;
    cin>>id;
    int idx =  recuperar_id(id);
    if (idx == -1){
        cout<<("\nid no encontrado\n");
        
    }else{
        Mascota m = recuperar_indice(idx);
        imprimir_estructura(&m);
        cout<<"\n\n¿Desea abrir la historia clinica? (S/N): ";
        char c;
        cin>>c;
        if (c=='S'){
            char comando[256];
            sprintf( comando,"date -Iminutes >> historia_clinica/%d.txt",id);
            system (comando);
            sprintf(comando,"xdg-open historia_clinica/%d.txt &",id);
            system (comando);
        }
    }
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
}
void borrar_reg(){
    cout<<"\nExisten "<<TAMANO_ACTUAL<<" registros en la base de datos\nEscriba el id a borrar: ";
    int id;
    cin>>id;
    int idx =  recuperar_id(id);
    if (idx == -1){
        cout<<("\nid no encontrado\n");
        system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
        menu();
        return;
    }
    borrar_indice(idx);
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
    return;
}
void buscar_reg(){
    char c[32];
    cout<<"Ingrese el nombre a buscar : ";
    cin>>c;
    int current_hash = hashear_nombre(c);
    if (recuperar_hash(current_hash) == -1){
        cout << "Nombre no encontrado...\n";
    }else{
        int index=recuperar_hash(current_hash), cnt = 1;
        Mascota ultima  = recuperar_indice( index);
        if (comparar_nombres(ultima.nombre,c)){
            cout<<"\n Mascota "<<cnt++<<"\n";
            imprimir_estructura(&ultima);
        }
        while (ultima.siguiente_con_mismo_hash!=-1){
            index = ultima.siguiente_con_mismo_hash;
            ultima = recuperar_indice( index);
            if (comparar_nombres(ultima.nombre,c)){
                cout<<"\n Mascota "<<cnt++<<"\n";
                imprimir_estructura(&ultima);
            }
        }
    }
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
    return;
}

int procesar_nombre (char* original, char* resultado){
    int tam =0;
    for (int i=0;original[i];++i){
        if('A'<=original[i] && original[i]<'Z'){
            resultado[tam++]=original[i]-'A'+'a';
        }else if('a'<=original[i] && original[i]<'z'){
            resultado[tam++]=original[i];
        }
    }
    return tam;
}

bool comparar_nombres (char *s1, char *s2){
    char s1_procesado[32],s2_procesado[32];
    int tam1 = procesar_nombre(s1,s1_procesado);
    int tam2 = procesar_nombre(s2,s2_procesado);
    if (tam1 != tam2){
        return false;
    }
    for (int i=0;i<tam1;++i){
        if(s1_procesado[i]!=s2_procesado[i]){
            return false;
        }
    }
    return true;
}
