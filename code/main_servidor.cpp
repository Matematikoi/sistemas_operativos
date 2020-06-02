#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>    //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include "mascotas.h"
#include "interactuar_archivos.h"
#include "interaccion_con_menu_servidor.h"

#define TRUE 1
#define FALSE 0
#define PORT 8888

using namespace std;

//TO RUN g++ -std=c++11 server.cpp -o server && ./server

void enviarACliente(char *data, int sd, int tamanoBuffer)
{        
    int r = send(sd, data, tamanoBuffer, 0);
    if(r < 0){
        puts("\nError en send()");
        return;
    }   
}

int opt = TRUE;
int master_socket, addrlen, new_socket, client_socket[30],
    max_clients = 30, activity, i, valread, sd;
int max_sd;
struct sockaddr_in address;

Mensaje mensajeRecibido;

fd_set readfds;

void initializeServer()
{
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    addrlen = sizeof(address);
    puts("Waiting for connections ...");
}

void loop()
{
    while (TRUE)
    {
        FD_ZERO(&readfds);

        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (sd > 0)
                FD_SET(sd, &readfds);

            if (sd > max_sd)
                max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            printf("select error");
        }

        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            for (i = 0; i < max_clients; i++)
            {
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                if ((valread = read( sd , &mensajeRecibido, sizeof (Mensaje))) == 0) 
                {
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    client_socket[i] = 0;
                }

                else
                {                                        
                    printf("TIPO %d\n", mensajeRecibido.tipoDeMensaje);                    
                    RespuestaServidor respuesta = recibirMensajeCliente(mensajeRecibido);
                    string mensajeCasteado = respuestaToString(respuesta, mensajeRecibido);                                        
                    char * res;
                    res = (char*) malloc(mensajeCasteado.size());
                    strcpy(res, mensajeCasteado.c_str());
                    enviarACliente(res, sd, mensajeCasteado.size()+1);  

                    if(mensajeRecibido.tipoDeMensaje == VER_MASCOTA) {
                        int verHistoriaClinica;
                        read(sd, &verHistoriaClinica, sizeof(int));
                        if(verHistoriaClinica){   
                            puts("VIENDO HISTORIA CLINICA");                     
                            string historiaClinica = obtenerHistoriaClinica(mensajeRecibido.mascota);
                            printf("HISTORIA ACTUAL %s\n", historiaClinica.c_str());
                            char * historia;
                            historia = (char*) malloc(historiaClinica.size());
                            strcpy(historia, historiaClinica.c_str());
                            enviarACliente(historia, sd, historiaClinica.size()+1);
                            
                            int tamanoDelBuffer = 1000;
                            char buffer[tamanoDelBuffer];                            
                            int r = read(sd, buffer, tamanoDelBuffer);
                            string nuevaHistoria(buffer);
                            printf("NUEVA HISTORIA %s\n", nuevaHistoria.c_str());
                            cambiarHistoriaClinica(mensajeRecibido.mascota, nuevaHistoria);
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    //alistar algunas variables
    ifstream mascotasArray (ARCHIVO_MASCOTAS, ios::in|ios::binary|ios::ate);
    TAMANO_REAL =  mascotasArray.tellg() / sizeof(Mascota);
    TAMANO_ACTUAL= leer_tamano();
    mascotasArray.close();
    ifstream archivoIDs(ARCHIVO_IDS, ios::in|ios::binary|ios::ate);
    TAMANO_ID = archivoIDs.tellg() / sizeof(int);
    archivoIDs.close();

    initializeServer();
    loop();
}