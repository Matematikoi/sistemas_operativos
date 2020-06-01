#include <bits/stdc++.h>
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "mensaje.h"
#include "interaccion_con_menu_cliente.h"
using namespace std;


Mensaje menu();
Mensaje anadir_reg();
Mensaje ver_reg();
Mensaje borrar_reg();
Mensaje buscar_reg();
Mensaje modificar_hist();
Mensaje menu(){
	char opcion;
    cout<<("\n\n\n\tMENU");
    cout<<("\n\tIngresar registro\t\tIngrese (1)\n\n");
    cout<<("\tVer registro\t\t\tIngrese (2)\n\n");
    cout<<("\tBorrar registro\t\t\tIngrese (3)\n\n");
    cout<<("\tBuscar Registro\t\t\tIngrese (4)\n\n");
    cout<<("\tSalir\t\t\t\tIngrese (5)\n\n\t");
    //cout<<("\tModificar Historia Clinica  (6)\n\n");
    cin>>opcion;
    Mensaje mensaje;
	switch(opcion){
		case '1':{
			mensaje = anadir_reg();
			break;
		}
		case '2':{
			mensaje = ver_reg();
			break;
		}
		case '3':{
			mensaje = borrar_reg();
			break;
		}
		case '4':{
			mensaje = buscar_reg();
			break;
		}
		case '5':{
			cout<<("\n\n\t----HA SALIDO DEL PROGRAMA----)\n\n\t");
            mensaje.tipoDeMensaje = ROMPER_CONEXION;
			break;
		}
        case '6' :
            mensaje = modificar_hist();
            break;
		
		default:{
			cout<<"\n\n\n\t"<<opcion<<" NO ES UNA OPCION\n";
			break;	
		}
	}
    
    return mensaje;
}
//Función para verificar un input correcto de un número entero por parte del usuario
int getAndVerifyInt()
{
    int num;
    cin >> num;

    //El valor debe ser un int válido mayor a cero
    while (!cin.good() || num <= 0)
    {
        cout << "Por favor digite un número entero mayor a cero: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> num;
    }
    return num;
}

//Función para verificar un input correcto de un número decimal por parte del usuario
float getAndVerifyFloat()
{
    float num;
    cin >> num;

    //El valor debe ser un float válido mayor a cero
    while (!cin.good() || num <= 0.0)
    {
        cout << "Por favor, digite un número decimal mayor a cero: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> num;
    }
    return num;
}

//Función para verificar un input correcto de un string por parte del usuario. Recibe un int que define la longitud máxima del string.
string getAndVerifyString(int strLenght)
{
    string str = "";
    getline(cin, str);
    cin.clear();
    //El valor debe ser menor a la longitud dada
    while (!cin.good() || str.length() > strLenght || str.length() == 0)
    {
        cout << "Por favor, digite un nombre de no más de " << strLenght << " carácteres: ";
        cin.clear();
        getline(cin, str);
    }
    return str;
}

//Función que decide si un input para el sexo es válido
bool animalSexInputIsValid(string input)
{
    return input == "M"|| input == "H";
}

//Función que solicita y verifica input del sexo por parte del usuario
char getAndVerifyAnimalSexInput()
{
    string input = " ";

    while (!animalSexInputIsValid(input))
    {
        cout << "Por favor ingrese 'F' o 'M' únicamente: " << endl;
        cin >> input;
    }
    return input[0];
}

Mensaje anadir_reg(){
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    Mascota m;
    cout<<("\n\tInserte los datos a añadir: \n");
    cout<<("\nInserte el nombre: ");
    strcpy(m.nombre , getAndVerifyString(32).c_str() ) ;
    cout<<("\nInserte el tipo: ");
    strcpy(m.tipo , getAndVerifyString(32).c_str() ) ;
    cout<<("\nInserte la edad: ");
    m.edad = getAndVerifyInt();
    cout<<("\nInserte la raza: ");
    strcpy(m.raza , getAndVerifyString(16).c_str() ) ;
    cout<<("\nInserte la estatura: ");
    m.estatura = getAndVerifyInt();;
    cout<<("\nInserte el peso: ");
    m.peso = getAndVerifyFloat();
    cout<<("\nInserte el sexo: ");
    m.sexo = getAndVerifyAnimalSexInput();
    mensaje.mascota= m;
    mensaje.tipoDeMensaje = ANADIR_MASCOTA;
    return mensaje;    
}
Mensaje ver_reg(){
    int id;
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    cout << "Inserte el id: ";
    cin>>id;
    mensaje.mascota.id= id;
    mensaje.tipoDeMensaje= VER_MASCOTA;
    return mensaje;  
}
Mensaje borrar_reg(){
    Mensaje mensaje;
    int id;
    memset( &mensaje,0, sizeof(Mensaje));
    cout<<"Escriba el id a borrar: ";
    cin>>id;
    mensaje.mascota.id= id;
    mensaje.tipoDeMensaje= ELIMINAR_MASCOTA;
    return mensaje;  
}
Mensaje buscar_reg(){
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    cout<<"Ingrese el nombre a buscar : ";
    cin>>mensaje.mascota.nombre;
    mensaje.tipoDeMensaje=BUSCAR_MASCOTA;
    return mensaje;    
}
Mensaje modificar_hist(){
    int id;
    Mensaje mensaje;
    memset( &mensaje,0, sizeof(Mensaje));
    cout << "Inserte el id: ";
    cin>>id;
    mensaje.mascota.id= id;
    mensaje.tipoDeMensaje= HISTORIA_CLINICA;
    return mensaje;  
}


string editarHistoriaClinica(string historiaClinicaOriginal){
    char * ruta = (char*) malloc (50+historiaClinicaOriginal.size());
    strcpy(ruta, RUTA_HISTORIA_CLINICA_TEMPORAL );
    strcat(ruta, "/temp.txt");
    //crear un archivo temporal
    escribirHistoriaClinica(ruta, historiaClinicaOriginal);
    //Edicion de texto
    char comando[256];
    strcpy(comando, "xdg-open ");
    strcat(comando, ruta);
    system(comando);
    system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
    //se retorna el archivo editado
    return leerHistoriaClinica(ruta);
    
}