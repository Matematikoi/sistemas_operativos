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
};
int tamano, tamano_real;

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
    cout<<m->sexo    <<endl;
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
    mascota ultima = recuperar_indice(tamano-1);
    escribir_mascota_a_indice(idx, &ultima);
    tamano--;
}
void anadir_mascota(mascota *m){
    if (tamano < tamano_real){
        escribir_mascota_a_indice(tamano++,m);
        return;
    }
    escribir_al_final(m);
}

int main (){
    mascota m;
    ifstream archivo ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    tamano_real = tamano = archivo.tellg() / sizeof(mascota);
    archivo.close();
    m = recuperar_indice(3);
    //borrar_indice(3);
    anadir_mascota(&m);
    
    cout<<tamano<<endl;
    for (int i=0;i<tamano;++i){
        m = recuperar_indice(i);
        cout <<i<<')';
        imprimir_estructura(&m);
    }
}