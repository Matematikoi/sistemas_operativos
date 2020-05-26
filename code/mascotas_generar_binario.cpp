#include <bits/stdc++.h>
#include "mascotas.h"
using namespace std;
const int MAX = 10000007;
int TAMANO_ARR_MASCOTAS;
int IDS[MAX];
int *HASH_NOMBRES;






/**
 * Lee de std input mascotas en formato de texto y devuelve un vector con mascotas 
 * como estructura de datos. 
 * 
 * Se encarga sobre de ajustar el id, y el hash de los nombres automaticamente. Estos datos
 * no se deben pasar
 * */
Mascota * leer_archivo(){
    static Mascota arr[MAX];
    int hash_actual;
    Mascota mascota_actual;
    while (cin>>mascota_actual.nombre){
        cin>>mascota_actual.tipo;
        cin>>mascota_actual.edad;
        cin>>mascota_actual.raza;
        cin>>mascota_actual.estatura;
        cin>>mascota_actual.peso;
        cin>> mascota_actual.sexo;
        //Ajustar el hash de los nombres de las mascotas
        hash_actual = hashear_nombre(mascota_actual.nombre);
        //Cuando el hash no existe se crea con valor de indice actual
        // en otro caso se busca el ultimo y se añade como linked list
        if (HASH_NOMBRES[hash_actual]==-1){
            HASH_NOMBRES[hash_actual]= TAMANO_ARR_MASCOTAS;
            mascota_actual.anterior_con_mismo_hash=-1;
            mascota_actual.siguiente_con_mismo_hash=-1;
        }else{
            int index=HASH_NOMBRES[hash_actual];
            arr[index].anterior_con_mismo_hash=TAMANO_ARR_MASCOTAS;
            HASH_NOMBRES[hash_actual] = TAMANO_ARR_MASCOTAS;
            mascota_actual.siguiente_con_mismo_hash = index;
            mascota_actual.anterior_con_mismo_hash = -1;
        }

        mascota_actual.id = TAMANO_ARR_MASCOTAS;
        IDS[TAMANO_ARR_MASCOTAS] = TAMANO_ARR_MASCOTAS;
        arr[TAMANO_ARR_MASCOTAS++]=mascota_actual;
    }
    return arr;
}

int guardar_estructura(void *arr){
    FILE *apFile;
    int r;
    apFile = fopen(ARCHIVO_MASCOTAS,"w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(Mascota),TAMANO_ARR_MASCOTAS, apFile);
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
int guardar_IDS(void *arr){
    FILE *apFile;
    int r;
    apFile = fopen(ARCHIVO_IDS,"w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(int),TAMANO_ARR_MASCOTAS, apFile);
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
/**
 * Guarda la informacion del hash de los nombres
 * de las mascotas como un archivo binario
 * */
int guardar_hash(void *arr){
    FILE *apFile;
    int r;
    apFile = fopen(ARCHIVO_HASH,"w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(int), MOD , apFile);
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
int guardar_tamano(void *arr){
    FILE *apFile;
    int r;
    apFile = fopen(ARCHIVO_TAMANO,"w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(int),1, apFile);
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    HASH_NOMBRES = (int*) malloc(sizeof(int) * MOD);
    memset(HASH_NOMBRES,-1, sizeof(int) * MOD);
    Mascota *arr_mascotas = leer_archivo(), *lectura;
    cerr<<"tamano de arreglo: "<<TAMANO_ARR_MASCOTAS<<endl;
    guardar_estructura(arr_mascotas);
    guardar_IDS(&IDS);
    guardar_hash(HASH_NOMBRES);
    guardar_tamano(&TAMANO_ARR_MASCOTAS);

}