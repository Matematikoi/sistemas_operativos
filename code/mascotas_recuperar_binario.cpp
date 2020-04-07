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
int tamano;

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
}

int main (){
    mascota m;
    ifstream archivo ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    tamano = archivo.tellg() / sizeof(mascota);
    archivo.close();
    cout<<tamano<<endl;
    for (int i=0;i<tamano;++i){
        m = recuperar_indice(i);
        imprimir_estructura(&m);
    }
}