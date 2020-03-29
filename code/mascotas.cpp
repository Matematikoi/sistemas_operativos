#include <bits/stdc++.h>
using namespace std;
int tamano_arr_mascota;
struct mascota{
    char nombre[32];
    char tipo[32];
    int edad;
    char raza[16];
    int estatura;
    float peso;
    char sexo;
};

mascota * leer_archivo(){
    static mascota arr[100];
    mascota cur;
    while (cin>>cur.nombre){
        cin>>cur.tipo;
        cin>>cur.edad;
        cin>>cur.raza;
        cin>>cur.estatura;
        cin>>cur.peso;
        cin>> cur.sexo;
        arr[tamano_arr_mascota++]=cur;
    }
    return arr;
}


int main (){
    mascota *arr_mascotas = leer_archivo();
    for (int i =0;i<tamano_arr_mascota;++i){
        cout<< ((arr_mascotas + i)->nombre)<<' ';
        cout<< ((arr_mascotas + i)->tipo)<<' ';
        cout<< ((arr_mascotas + i)->edad)<<' ';
        cout<< ((arr_mascotas + i)->raza)<<' ';
        cout<< ((arr_mascotas + i)->estatura)<<' ';
        cout<< ((arr_mascotas + i)->peso)<<' ';
        cout<< ((arr_mascotas + i)->sexo)<<'\n';
    }

      
}