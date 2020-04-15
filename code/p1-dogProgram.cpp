#include <bits/stdc++.h>
using namespace std;
const int MOD = 5003;
int tamano, tamano_real, tamano_id;

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
int leer_tamano (){
    int i;
    ifstream archivo ("binaries/tamano.bin", ios::in|ios::binary|ios::ate);
    archivo.seekg (0, ios::beg);
    archivo.read((char*) &i,sizeof(int));
    archivo.close();
    return i;
}
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
int recuperar_id (int num_id){
    int i;
    if (tamano_id<=num_id){
        return -1;
    }
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

/**
 * Retorna el indice de la primera ocurrencia de un
 * elemento con hash h. En caso de no existir 
 * retorna -1
 * */
int recuperar_hash(int h){
    int idx;
    ifstream archivo ("binaries/hash.bin", ios::in|ios::binary|ios::ate);
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
    ofstream archivo ("binaries/hash.bin", ios::in|ios::binary|ios::ate);
    archivo.seekp(sizeof(int) * h);
    archivo.write((char*) &new_index,sizeof(int));
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
/** borra un indice del arreglo de mascotas
 * automaticamente actualiza el id y el hash
 * */
void borrar_indice(int idx){
    mascota ultima = recuperar_indice(tamano-1), mitad = recuperar_indice(idx);
    mascota siguiente,anterior;
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
    int current_hash = hashear_nombre(m->nombre);
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

void anadir_reg();
void ver_reg();
void borrar_reg();
void buscar_reg();
void menu();
int procesar_nombre (char* original, char* resultado);
bool comparar_nombres (char *s1, char *s2);

int main (){
    mascota m;
    ifstream archivo_mascotas ("binaries/mascotas_array.bin", ios::in|ios::binary|ios::ate);
    tamano_real =  archivo_mascotas.tellg() / sizeof(mascota);
    tamano= leer_tamano();
    archivo_mascotas.close();
    ifstream archivo_ids("binaries/ids.bin", ios::in|ios::binary|ios::ate);
    tamano_id = archivo_ids.tellg() / sizeof(int);
    archivo_ids.close();

    menu();
}



void anadir_reg(){
    mascota m;
    cout<<("\n\tInserte los datos a añadir: \n");
    cout<<("\nInserte el nombre: ");
    cin>>m.nombre;
    cout<<("\nInserte el tipo: ");
    cin>>m.tipo;
    cout<<("\nInserte la edad: ");
    cin>>m.edad;
    cout<<("\nInserte la raza: ");
    cin>>m.raza;
    cout<<("\nInserte la estatura: ");
    cin>>m.estatura;
    cout<<("\nInserte el peso: ");
    cin>>m.peso;
    cout<<("\nInserte el sexo: ");
    cin>>m.sexo;
    anadir_mascota(&m);
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
}
void ver_reg(){
    cout<<"\nExisten "<<tamano<<" registros en la base de datos\nEscriba el id a buscar: ";
    int id;
    cin>>id;
    int idx =  recuperar_id(id);
    if (idx == -1){
        cout<<("\nid no encontrado\n");
        
    }else{
        mascota m = recuperar_indice(idx);
        imprimir_estructura(&m);
        cout<<"\n\n¿Desea abrir la historia clinica? (S/N): ";
        char c;
        cin>>c;
        if (c=='S'){
            char comando[256];
            sprintf( comando,"date -Iminutes >> historia_clinica/%d.txt",id);
            system (comando);
            sprintf(comando,"xdg-open historia_clinica/%d.txt &",id);
            system (comando);
        }
    }
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
}
void borrar_reg(){
    cout<<"\nExisten "<<tamano<<" registros en la base de datos\nEscriba el id a borrar: ";
    int id;
    cin>>id;
    int idx =  recuperar_id(id);
    if (idx == -1){
        cout<<("\nid no encontrado\n");
        system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
        menu();
        return;
    }
    borrar_indice(idx);
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
    return;
}
void buscar_reg(){
    char c[32];
    cout<<"Ingrese el nombre a buscar : ";
    cin>>c;
    int current_hash = hashear_nombre(c);
    if (recuperar_hash(current_hash) == -1){
        cout << "Nombre no encontrado...\n";
    }else{
        int index=recuperar_hash(current_hash), cnt = 1;
        mascota ultima  = recuperar_indice( index);
        if (comparar_nombres(ultima.nombre,c)){
            cout<<"\n Mascota "<<cnt++<<"\n";
            imprimir_estructura(&ultima);
        }
        while (ultima.siguiente_con_mismo_hash!=-1){
            index = ultima.siguiente_con_mismo_hash;
            ultima = recuperar_indice( index);
            if (comparar_nombres(ultima.nombre,c)){
                cout<<"\n Mascota "<<cnt++<<"\n";
                imprimir_estructura(&ultima);
            }
        }
    }
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    menu();
    return;
}
void menu(){
    guardar_tamano(&tamano);
    //system("clear");
	char opcion;
    cout<<("\n\n\n\tMENU");
    cout<<("\n\tIngresar registro\t\tIngrese (1)\n\n");
    cout<<("\tVer registro\t\t\tIngrese (2)\n\n");
    cout<<("\tBorrar registro\t\t\tIngrese (3)\n\n");
    cout<<("\tBuscar Registro\t\t\tIngrese (4)\n\n");
    cout<<("\tSalir\t\t\t\tIngrese (5)\n\n\t");
    cin>>opcion;
	switch(opcion){
		case '1':{
			anadir_reg();
			break;
		}
		case '2':{
			ver_reg();
			break;
		}
		case '3':{
			borrar_reg();
			break;
		}
		case '4':{
			buscar_reg();
			break;
		}
		case '5':{
			cout<<("\n\n\t----HA SALIDO DEL PROGRAMA----)\n\n\t");
			break;
		}
		
		default:{
			cout<<"\n\n\n\t"<<opcion<<"NO ES UNA OPCION\n";
			menu();
			break;	
		}
	}
    
}
int procesar_nombre (char* original, char* resultado){
    int tam =0;
    for (int i=0;original[i];++i){
        if('A'<=original[i] && original[i]<'Z'){
            resultado[tam++]=original[i]-'A'+'a';
        }else if('a'<=original[i] && original[i]<'z'){
            resultado[tam++]=original[i];
        }
    }
    return tam;
}
bool comparar_nombres (char *s1, char *s2){
    char s1_procesado[32],s2_procesado[32];
    int tam1 = procesar_nombre(s1,s1_procesado);
    int tam2 = procesar_nombre(s2,s2_procesado);
    if (tam1 != tam2){
        return false;
    }
    for (int i=0;i<tam1;++i){
        if(s1_procesado[i]!=s2_procesado[i]){
            return false;
        }
    }
    return true;
}

