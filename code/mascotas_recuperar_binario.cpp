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


void recuperar_indice(int num_item){
    mascota m;
    ifstream archivo ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    archivo.seekg (sizeof(mascota) * num_item, ios::beg);
    archivo.read(m.nombre,sizeof(m.nombre));
    archivo.read(m.tipo,sizeof(m.tipo));
    archivo.read(reinterpret_cast<char*>(&m.edad),sizeof(int));
    archivo.read(m.raza,sizeof(m.raza));
    archivo.read(reinterpret_cast<char*>(&m.estatura),sizeof(int));
    archivo.read(reinterpret_cast<char*>(&m.peso), sizeof(float));
    archivo.read(reinterpret_cast<char*>(&m.sexo), sizeof(char));
    cout<<m.nombre<<endl;
    cout<<m.tipo<<endl;
    cout<<m.edad<<endl;
    cout<<m.raza<<endl;
    cout<<m.estatura<<endl;
    cout<<m.peso<<endl;
    cout<<m.sexo<<endl;
}

int main (){
    mascota arr;
    recuperar_indice(2);

}