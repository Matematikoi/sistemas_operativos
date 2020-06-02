#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "mascotas.h"
#include "interaccion_con_menu_cliente.h"
using namespace std;

int sock = -1;

void inicializarSocket (int port, char * hostR) {    	
	struct sockaddr_in address;
	struct hostent * host;
	int len;

	if (port <= 0)
	{
		fprintf(stderr, "error: wrong parameter: port\n");
		return;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0)
	{
		fprintf(stderr, "error: cannot create socket\n");
		return;
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	host = gethostbyname(hostR);
	if (!host)
	{
		fprintf(stderr, "error: unknown host %s\n", hostR);
		return;
	}
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);
	if (connect(sock, (struct sockaddr *)&address, sizeof(address)))
	{
		fprintf(stderr, "error: cannot connect to host %s\n", hostR);
        return;		
    }
}

void enviarMensaje(Mensaje mensaje){    
    write(sock, &mensaje, sizeof(Mensaje));
    //con esta funcion se envia al server la info
}
string mensajeRecibido(){
	string resultado = "";
	int tamanoDelBuffer = 1000;
    char buffer[tamanoDelBuffer];
	while (true){
		int r = recv(sock, buffer, tamanoDelBuffer, 0);
		if(r < 0){
            perror("read error");
            exit(-1);
        }
		for (int i =0; i<r;++i)resultado+=buffer[i];
        if(r < tamanoDelBuffer-1)break;
	}
	resultado+="\n";
	return resultado;
}
void romperConexion(){
    //funcion con la que se rompe conexion al server
}
int main (int argc, char ** argv){
     if (argc != 3)
	{
		printf("usage: %s hostname port\n", argv[0]);
		return -1;
	}
    int port;
    sscanf(argv[2], "%d", &port);
    inicializarSocket(port, argv[1]);
    

    Mensaje mensaje, mensajePeticionTamano;
	mensajePeticionTamano.tipoDeMensaje = PETICION_TAMANO;
    do {
		enviarMensaje(mensajePeticionTamano);
		string respuestaTamano = mensajeRecibido();
        mensaje = menu(respuestaTamano);
        if (mensaje.tipoDeMensaje == ROMPER_CONEXION){
            romperConexion();
            break;
        }
        enviarMensaje(mensaje);
        string respuestaServer = mensajeRecibido();
		cout<<respuestaServer;
        system("read -n 1 -s -r -p \"Presione cualquier tecla para continuar...\"");
        //system("clear");
    }while(true);

}