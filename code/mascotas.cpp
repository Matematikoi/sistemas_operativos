#include <bits/stdc++.h>
#include "mascotas.h"
#include <sstream>
const char * ARCHIVO_TAMANO="binaries/tamano.bin";
const char * ARCHIVO_MASCOTAS="binaries/mascotas_array.bin";
const char * ARCHIVO_IDS="binaries/ids.bin";
const char * ARCHIVO_HASH="binaries/hash.bin";


int hashear_nombre(char *str ){
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
        acu= (acu +((letra*base_acumulada)% MOD ))% MOD ;
        base_acumulada=(base*base_acumulada) % MOD ;
    }
    return acu;
}

int guardar_en_archivo(void *arr,const char * nombre, int TAMANO_ACTUAL, int n ){
    FILE *apFile;
    int r;
    apFile = fopen(nombre,"w+");
    if(apFile == NULL){
        perror("error fopen:");
        exit(-1);
    }
    r = fwrite(arr, TAMANO_ACTUAL,n, apFile);
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

std::string leerHistoriaClinica(char* ruta){
    std::ifstream nameFileout;
    nameFileout.open(ruta);
    std::string linea, texto = "";
    while(std::getline(nameFileout, linea)){
       texto+=linea+'\n';
    }
    return texto;
}
void escribirHistoriaClinica(char * ruta, std::string data){
    std::ofstream out(ruta);
    out << data;
    out.close();
}