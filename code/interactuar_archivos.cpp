#include <bits/stdc++.h>
#include "mascotas.h"

using namespace std;
int tamano, tamano_real, tamano_id;

int guardar_tamano(void *arr){
    return guardar_en_archivo(arr, ARCHIVO_TAMANO,sizeof(int),1);
}

int leer_tamano (){
    int i;
    ifstream archivo (ARCHIVO_TAMANO, ios::in|ios::binary|ios::ate);
    archivo.seekg (0, ios::beg);
    archivo.read((char*) &i,sizeof(int));
    archivo.close();
    return i;
}

int recuperar_id (int num_id){
    int i;
    if (tamano_id<=num_id){
        return -1;
    }
    ifstream archivo (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(int) * num_id, ios::beg);
    archivo.read((char*) &i,sizeof(int));
    archivo.close();
    return i;
}
void escribir_al_final_id (int num_idx){
    FILE *archivo ;
    archivo = fopen(ARCHIVO_IDS, "ab+");
    fwrite (&num_idx ,sizeof(int), 1, archivo);
    fclose(archivo);
    ++tamano_id;
}
void escribir_id_a_indice(int id, int new_idx){
    ofstream archivo (ARCHIVO_IDS, ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(int) * id);
    archivo.write((char*) &new_idx, sizeof(int));
    archivo.close();
}

/**
 * Retorna el indice de la primera ocurrencia de un
 * elemento con hash h. En caso de no existir 
 * retorna -1
 * */
int recuperar_hash(int h){
    int idx;
    ifstream archivo (ARCHIVO_HASH, ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(int) * h, ios::beg);
    archivo.read((char*) &idx,sizeof(int));
    archivo.close();
    return idx;
}
/**
 * Escribe un nuevo indice a la posicion 
 * de hash h
 * @input 
 * new_index : el nuevo indice a escribir
 * h : el hash del nuevo indice
 * */
void escribir_hash(int h, int new_index){
    ofstream archivo (ARCHIVO_HASH, ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(int) * h);
    archivo.write((char*) &new_index,sizeof(int));
    archivo.close();
}

mascota recuperar_indice(int num_item){
    mascota m;
    ifstream archivo (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(mascota) * num_item, ios::beg);
    archivo.read((char*) &m,sizeof(mascota));
    archivo.close();
    return m;
}
void imprimir_estructura(mascota *m){
    cout<<"nombre: "<<m->nombre  <<'\n';
    cout<<"tipo: "<<m->tipo    <<'\n';
    cout<<"edad: "<<m->edad    <<'\n';
    cout<<"raza: "<<m->raza    <<'\n';
    cout<<"estatura: "<<m->estatura<<'\n';
    cout<<"peso: "<<m->peso    <<'\n';
    cout<<"sexo: "<<m->sexo    <<'\n';
    cout<<"id: "<<m->id      <<'\n';

}
void escribir_al_final (mascota *m){
    FILE *archivo ;
    archivo = fopen(ARCHIVO_MASCOTAS, "ab+");
    fwrite (m,sizeof(mascota), 1, archivo);
    fclose(archivo);
    ++tamano;
    ++tamano_real;
}
void escribir_mascota_a_indice(int idx, mascota *m){
    ofstream archivo (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(mascota) * idx);
    archivo.write((char*) m,sizeof(mascota));
    archivo.close();
}
/** borra un indice del arreglo de mascotas
 * automaticamente actualiza el id y el hash
 * */
void borrar_indice(int idx){
    mascota ultima = recuperar_indice(tamano-1), mitad = recuperar_indice(idx);
    mascota siguiente,anterior;
    //quitamos a mitad de la linked list
    if(mitad.anterior_con_mismo_hash==-1){
        escribir_hash(hashear_nombre(mitad.nombre, MOD),mitad.siguiente_con_mismo_hash);
    }else{
        anterior = recuperar_indice(mitad.anterior_con_mismo_hash);
        anterior.siguiente_con_mismo_hash=mitad.siguiente_con_mismo_hash;
        escribir_mascota_a_indice(mitad.anterior_con_mismo_hash, &anterior);
    }
    if (mitad.siguiente_con_mismo_hash!=-1){
        siguiente = recuperar_indice(mitad.siguiente_con_mismo_hash);
        siguiente.anterior_con_mismo_hash=mitad.anterior_con_mismo_hash;
        escribir_mascota_a_indice(mitad.siguiente_con_mismo_hash, &siguiente);
    }
    //actualizamos la linked list para la ultima mascota
    if (ultima.anterior_con_mismo_hash==-1){
        escribir_hash(hashear_nombre(ultima.nombre,MOD),idx);
    }else{
        anterior = recuperar_indice(ultima.anterior_con_mismo_hash);
        anterior.siguiente_con_mismo_hash = idx;
        escribir_mascota_a_indice(ultima.anterior_con_mismo_hash,&anterior);
    }
    if (ultima.siguiente_con_mismo_hash){
        siguiente = recuperar_indice(ultima.siguiente_con_mismo_hash);
        siguiente.anterior_con_mismo_hash=idx;
        escribir_mascota_a_indice(ultima.siguiente_con_mismo_hash,&siguiente);
    }
    escribir_id_a_indice(mitad.id, -1);
    escribir_mascota_a_indice(idx, &ultima);
    escribir_id_a_indice(ultima.id, idx);
    tamano--;
}
/** 
 * Anade una mascota al final de la lista
 * de mascotas. Otorga el id y la informacion
 * del hash automaticamente
 * */
void anadir_mascota(mascota *m){
    m->id = tamano_id;
    escribir_al_final_id(tamano);
    int current_hash = hashear_nombre(m->nombre, MOD);
    if (recuperar_hash(current_hash) == -1){
        escribir_hash(current_hash,tamano);
        m->anterior_con_mismo_hash=-1;
        m->siguiente_con_mismo_hash=-1;
    }else{
        int index=recuperar_hash(current_hash);
        mascota primera  = recuperar_indice( index);
        primera.anterior_con_mismo_hash=tamano;
        escribir_hash(current_hash,tamano);
        escribir_mascota_a_indice(index, &primera);
        m->siguiente_con_mismo_hash=index;
        m->anterior_con_mismo_hash=-1;
    }
    if (tamano < tamano_real){
        escribir_mascota_a_indice(tamano++,m);
        return;
    }
    escribir_al_final(m);
}