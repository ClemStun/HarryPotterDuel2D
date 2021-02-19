 /**
 * \file utils.c
 * \brief Fonctions utiles pour les sockets
 * \author COLLET Matthieu
 * \version 0.1
 * \date 19 feb 2021
 *
 */

#include "init.h"

/**
 * \fn extern SOCKET init_connexion(void)
 * \brief Initialise la connexion du server pour écouter d'éventuelles connexions de nouveaux clients
 *
 * @return Retourne le socket du server
 */
extern 
SOCKET init_connexion(void);
 
extern
SOCKET init_connexion(void){
    SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrServer = { 0 };
    addrServer.sin_addr.s_addr = INADDR_ANY;
    addrServer.sin_family = AF_INET;
    int port;
    printf("PORTS : ");
    scanf("%i",&port);
    addrServer.sin_port = htons(port);

    if(bind(socketServer, (const struct sockaddr *)&addrServer, sizeof addrServer) == -1){
        perror("bind()");
        closesocket(socketServer);
        exit(-1);
    }  
    printf("bind : %d\n", socketServer);

    if(listen(socketServer, MAX_CLIENT) == -1){
        perror("listen()");
        exit(-1);    
    }
    printf("listen\n");
    return socketServer;
}