#include <bits/stdc++.h>
#include "mascotas.h"

using namespace std;
int TAMANO_ACTUAL, TAMANO_REAL, TAMANO_ID;

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
    if (TAMANO_ID<=num_id){
        return -1;
    }
    ifstream archivo (ARCHIVO_IDS, ios::in|ios::binary|ios::ate);
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
    ++TAMANO_ID;
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

Mascota recuperar_indice(int num_item){
    Mascota m;
    ifstream archivo (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(Mascota) * num_item, ios::beg);
    archivo.read((char*) &m,sizeof(Mascota));
    archivo.close();
    return m;
}
void imprimir_estructura(Mascota *m){
    cout<<"nombre: "<<m->nombre  <<'\n';
    cout<<"tipo: "<<m->tipo    <<'\n';
    cout<<"edad: "<<m->edad    <<'\n';
    cout<<"raza: "<<m->raza    <<'\n';
    cout<<"estatura: "<<m->estatura<<'\n';
    cout<<"peso: "<<m->peso    <<'\n';
    cout<<"sexo: "<<m->sexo    <<'\n';
    cout<<"id: "<<m->id      <<'\n';

}
void escribir_al_final (Mascota *m){
    FILE *archivo ;
    archivo = fopen(ARCHIVO_MASCOTAS, "ab+");
    fwrite (m,sizeof(Mascota), 1, archivo);
    fclose(archivo);
    ++TAMANO_ACTUAL;
    ++TAMANO_REAL;
}
void escribir_mascota_a_indice(int idx, Mascota *m){
    ofstream archivo (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(Mascota) * idx);
    archivo.write((char*) m,sizeof(Mascota));
    archivo.close();
}
/** borra un indice del arreglo de mascotas
 * automaticamente actualiza el id y el hash
 * */
void borrar_indice(int idx){
    Mascota ultima = recuperar_indice(TAMANO_ACTUAL-1), mitad = recuperar_indice(idx);
    Mascota siguiente,anterior;
    //quitamos a mitad de la linked list
    if(mitad.anterior_con_mismo_hash==-1){
        escribir_hash(hashear_nombre(mitad.nombre),mitad.siguiente_con_mismo_hash);
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
        escribir_hash(hashear_nombre(ultima.nombre),idx);
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
    TAMANO_ACTUAL--;
}
/** 
 * Anade una mascota al final de la lista
 * de mascotas. Otorga el id y la informacion
 * del hash automaticamente
 * */
void anadir_mascota(Mascota *m){
    m->id = TAMANO_ID;
    escribir_al_final_id(TAMANO_ACTUAL);
    int current_hash = hashear_nombre(m->nombre);
    if (recuperar_hash(current_hash) == -1){
        escribir_hash(current_hash,TAMANO_ACTUAL);
        m->anterior_con_mismo_hash=-1;
        m->siguiente_con_mismo_hash=-1;
    }else{
        int index=recuperar_hash(current_hash);
        Mascota primera  = recuperar_indice( index);
        primera.anterior_con_mismo_hash=TAMANO_ACTUAL;
        escribir_hash(current_hash,TAMANO_ACTUAL);
        escribir_mascota_a_indice(index, &primera);
        m->siguiente_con_mismo_hash=index;
        m->anterior_con_mismo_hash=-1;
    }
    if (TAMANO_ACTUAL < TAMANO_REAL){
        escribir_mascota_a_indice(TAMANO_ACTUAL++,m);
        return;
    }
    escribir_al_final(m);
}