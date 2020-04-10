#include <bits/stdc++.h>
using namespace std;
struct mascota{
    char nombre[32];
    char tipo[32];
    int edad;
    char raza[16];
    int estatura;
    float peso;
    char sexo;
    int id;
};
int tamano, tamano_real, tamano_id;
int recuperar_id (int num_id){
    int i;
    ifstream archivo ("binaries/ids.bin", ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(int) * num_id, ios::beg);
    archivo.read((char*) &i,sizeof(int));
    archivo.close();
    return i;
}
void escribir_al_final_id (int num_idx){
    FILE *archivo ;
    archivo = fopen("binaries/ids.bin", "ab+");
    fwrite (&num_idx ,sizeof(int), 1, archivo);
    fclose(archivo);
    ++tamano_id;
}
void escribir_id_a_indice(int id, int new_idx){
    ofstream archivo ("binaries/ids.bin", ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(int) * id);
    archivo.write((char*) &new_idx, sizeof(int));
    archivo.close();
}



mascota recuperar_indice(int num_item){
    mascota m;
    ifstream archivo ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(mascota) * num_item, ios::beg);
    archivo.read((char*) &m,sizeof(mascota));
    archivo.close();
    return m;
}
void imprimir_estructura(mascota *m){
    cout<<m->nombre  <<' ';
    cout<<m->tipo    <<' ';
    cout<<m->edad    <<' ';
    cout<<m->raza    <<' ';
    cout<<m->estatura<<' ';
    cout<<m->peso    <<' ';
    cout<<m->sexo    <<' ';
    cout<<m->id      <<'\n';
}
void escribir_al_final (mascota *m){
    FILE *archivo ;
    archivo = fopen("binaries/mascotas_array.bin", "ab+");
    fwrite (m,sizeof(mascota), 1, archivo);
    fclose(archivo);
    ++tamano;
    ++tamano_real;
}
void escribir_mascota_a_indice(int idx, mascota *m){
    ofstream archivo ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(mascota) * idx);
    archivo.write((char*) m,sizeof(mascota));
    archivo.close();
}
void borrar_indice(int idx){
    mascota ultima = recuperar_indice(tamano-1), mitad = recuperar_indice(idx);
    escribir_id_a_indice(mitad.id, -1);
    escribir_mascota_a_indice(idx, &ultima);
    escribir_id_a_indice(ultima.id, idx);
    tamano--;
}

void anadir_mascota(mascota *m){
    m->id = tamano_id;
    escribir_al_final_id(tamano);
    if (tamano < tamano_real){
        escribir_mascota_a_indice(tamano++,m);
        return;
    }
    escribir_al_final(m);
}

int main (){
    mascota m;
    ifstream archivo_mascotas ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    tamano_real = tamano = archivo_mascotas.tellg() / sizeof(mascota);
    archivo_mascotas.close();
    ifstream archivo_ids("binaries/ids.bin", ios::in|ios::binary|ios::ate);
    tamano_id = archivo_ids.tellg() / sizeof(int);
    archivo_ids.close();


    m = recuperar_indice(3);
    borrar_indice(3);
    anadir_mascota(&m);
    anadir_mascota(&m);
    anadir_mascota(&m);


    int idx_from_id = recuperar_id(105);
    cout<<idx_from_id<<endl;
    mascota foo = recuperar_indice(idx_from_id);
    imprimir_estructura(&foo);

    cout<<tamano<<endl;
    for (int i=0;i<tamano;++i){
        m = recuperar_indice(i);
        cout <<i<<')';
        imprimir_estructura(&m);
    }
}