#ifndef MASCOTA
#define MASCOTA

extern const char * ARCHIVO_TAMANO;
extern const char * ARCHIVO_MASCOTAS;
extern const char * ARCHIVO_IDS;
extern const char * ARCHIVO_HASH;
#define MOD 5003

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


int hashear_nombre(char *str, int mod);

int guardar_en_archivo(void *arr,const char * nombre, int tamano , int n );

#endif