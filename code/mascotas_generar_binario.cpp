#include <bits/stdc++.h>
using namespace std;
const int MAX = 10000007;
const int MOD = 5003;
int tamano_arr_mascota;
int ids[MAX];
int hash_nombres[MOD];

struct mascota{
    char nombre[32];
    char tipo[32];
    int edad;
    char raza[16];
    int estatura;
    float peso;
    char sexo;
    int id;
    int siguiente_con_mismo_hash;
    int anterior_con_mismo_hash;
};
int hashear_nombre(char *str){
    int acu=0, base = 26, base_acumulada = 1,letra;
    for( int i = 0 ; str[i]; ++ i ){
        if (str[i]>='A' && str[i] <='Z'){
            //caso mayusculas
            letra = str[i]-'A';
        }else if(str[i]>='a' && str[i] <='z') {
            //caso minusculas
            letra = str[i] -'a';
        }else{
            //caso no letra
            continue;
        }
        acu= (acu +((letra*base_acumulada)%MOD))%MOD;
        base_acumulada=(base*base_acumulada)%MOD;
    }
    return acu;
}
/**
 * Lee de std input mascotas en formato de texto y devuelve un vector con mascotas 
 * como estructura de datos. 
 * 
 * Se encarga sobre de ajustar el id, y el hash de los nombres automaticamente. Estos datos
 * no se deben pasar
 * */
mascota * leer_archivo(){
    static mascota arr[MAX];
    int current_hash;
    mascota cur;
    while (cin>>cur.nombre){
        cin>>cur.tipo;
        cin>>cur.edad;
        cin>>cur.raza;
        cin>>cur.estatura;
        cin>>cur.peso;
        cin>> cur.sexo;
        //Ajustar el hash de los nombres de las mascotas
        current_hash = hashear_nombre(cur.nombre);
        //Cuando el hash no existe se crea con valor de indice actual
        // en otro caso se busca el ultimo y se añade como linked list
        if (hash_nombres[current_hash]==-1){
            hash_nombres[current_hash]= tamano_arr_mascota;
            cur.anterior_con_mismo_hash=-1;
            cur.siguiente_con_mismo_hash=-1;
        }else{
            int index=hash_nombres[current_hash];
            arr[index].anterior_con_mismo_hash=tamano_arr_mascota;
            hash_nombres[current_hash] = tamano_arr_mascota;
            cur.siguiente_con_mismo_hash = index;
            cur.anterior_con_mismo_hash = -1;
        }

        cur.id = tamano_arr_mascota;
        ids[tamano_arr_mascota] = tamano_arr_mascota;
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
int guardar_ids(void *arr){
    FILE *apFile;
    int r;
    apFile = fopen("binaries/ids.bin","w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(int),tamano_arr_mascota, apFile);
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
    apFile = fopen("binaries/hash.bin","w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, sizeof(int),MOD, apFile);
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
    apFile = fopen("binaries/tamano.bin","w+");
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
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    memset(hash_nombres,-1, sizeof(hash_nombres));
    mascota *arr_mascotas = leer_archivo(), *lectura;
    cerr<<"tamano de arreglo: "<<tamano_arr_mascota<<endl;
    guardar_estructura(arr_mascotas);
    guardar_ids(&ids);
    guardar_hash(&hash_nombres);
    guardar_tamano(&tamano_arr_mascota);

}