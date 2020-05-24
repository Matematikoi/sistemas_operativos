#include <bits/stdc++.h>

const char * ARCHIVO_TAMANO="binaries/tamano.bin";
const char * ARCHIVO_MASCOTAS="binaries/mascotas_array.bin";
const char * ARCHIVO_IDS="binaries/ids.bin";
const char * ARCHIVO_HASH="binaries/hash.bin";

int hashear_nombre(char *str, int mod){
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
        acu= (acu +((letra*base_acumulada)%mod))%mod;
        base_acumulada=(base*base_acumulada)%mod;
    }
    return acu;
}