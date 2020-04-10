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
    static mascota arr[10000007];
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

int guardar_estructura(void *arr){
    FILE *apFile;
    int r;
    apFile = fopen("binaries/mascotas_array.bin","w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(mascota),tamano_arr_mascota, apFile);
    if(r <= 0){
        perror("error fwrite");
        exit(-1);
    }
    r = fclose(apFile);
    if(r < 0){
        perror("error fclose: ");
        exit(-1);
    }
    return 1;
}


int main (){
    mascota *arr_mascotas = leer_archivo(), *lectura;
    cerr<<"tamano de arreglo: "<<tamano_arr_mascota<<endl;
    guardar_estructura(arr_mascotas);
    
    
    //imprimir la estructura
    /*
    for (int i =0;i<tamano_arr_mascota;++i){
        cout<< ((arr_mascotas + i)->nombre)<<' ';
        cout<< ((arr_mascotas + i)->tipo)<<' ';
        cout<< ((arr_mascotas + i)->edad)<<' ';
        cout<< ((arr_mascotas + i)->raza)<<' ';
        cout<< ((arr_mascotas + i)->estatura)<<' ';
        cout<< ((arr_mascotas + i)->peso)<<' ';
        cout<< ((arr_mascotas + i)->sexo)<<'\n';
    }
    */

}