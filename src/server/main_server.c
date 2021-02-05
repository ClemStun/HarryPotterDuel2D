#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_server.h"

#define MAX_CLIENT 2

//Fonction pour mettre en place le serveur réseau et lancer l'écoute de nouvelles connexion client
static int init_connexion(void){
    SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrServer = { 0 };
    addrServer.sin_addr.s_addr = INADDR_ANY;
    addrServer.sin_family = AF_INET;
    printf("PORTS : ");
    int port;
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
//Fonction qui envoie des données à tous les clients sauf le client qui a envoyé la donnée en question
void send_all(SOCKET *clients, SOCKET sender, DATA joueur, int nb_client){
    int i;
    for(i = 0; i < nb_client; i++){
        if(sender != clients[i]){
            if(send(clients[i], &joueur, sizeof joueur, 0) < 0){
                perror("send()");
                exit(-1);
            }
        }
    }
}
//Fonction pour retirer un client 
void remove_client(SOCKET *clients, int i, int *nb_client){
   memmove(clients + i, clients + i + 1, (*nb_client - i - 1) * sizeof(SOCKET));
   (*nb_client)--;
}
//Fonction pour lire les données d'un client
DATA readData(SOCKET socket){
    DATA joueur;
    if((recv(socket, &joueur, sizeof(joueur) , 0)) < 0){
      perror("recv()");
   }
   return joueur;
}
//Fonction Principale
int main(){
    SOCKET socketServer = init_connexion();
    SOCKET clients[MAX_CLIENT];
    int nb_client = 0;
    int max = socketServer;
    fd_set readfs;
    //Boucle Principale
    while(1){
        int i;
        FD_ZERO(&readfs);
        FD_SET(socketServer, &readfs);
        for(i = 0; i < nb_client; i++){
            FD_SET(clients[i], &readfs);
        }
        if(select(max + 1, &readfs, NULL, NULL, NULL) == -1){
            perror("select()");
            exit(-1);
        }
        if(FD_ISSET(socketServer, &readfs)){
            //Nouveau Client
            SOCKADDR_IN addrClient = { 0 };
            socklen_t csize = sizeof addrClient;
            int socketClient = accept(socketServer, (SOCKADDR *)&addrClient, &csize);
            if(socketClient == -1){
                perror("accept()");
                continue;
            }
            max = socketClient > max ? socketClient : max;
            FD_SET(socketClient, &readfs);
            clients[nb_client] = socketClient;
            nb_client++;
            printf("Le joueur %i s'est connecte (%i/%i)\n", socketClient-socketServer, nb_client, MAX_CLIENT);
        }else{
            for(i = 0; i < nb_client; i++){
                if(FD_ISSET(clients[i], &readfs)){
                    SOCKET client = clients[i];
                    DATA joueur = readData(client);
                    if(joueur.x == -1){
                        closesocket(client);
                        remove_client(clients, i, &nb_client);
                        printf("Le joueur %i s'est deconnecte (%i/%i)\n",client-socketServer, nb_client, MAX_CLIENT);
                    }else{
                        send_all(clients, clients[i], joueur, nb_client);
                    }
                }
            }
        }
    }
    closesocket(socketServer);
    printf("close\n");
    return 0;
}
