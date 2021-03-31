#include "../../lib/sdl.h"
#include "../../lib/sort.h"
#include "init.h"

int main(){
    SOCKET socketServer = init_connexion();
    SOCKET clients[MAX_CLIENT];
    int nb_client = 0;
    int max = socketServer;
    fd_set readfs;

    socket_t firstPlayer;

    socket_t joueur;
    socket_t j1;
    socket_t j2;

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
            exit(INVALID_SOCKET);
        }
        if(FD_ISSET(socketServer, &readfs)){
            //Nouveau Client
            SOCKADDR_IN addrClient = { 0 };
            socklen_t csize = sizeof addrClient;
            int socketClient = accept(socketServer, (SOCKADDR *)&addrClient, &csize);
            if(socketClient == INVALID_SOCKET){
                perror("accept()");
                continue;
            }
            max = socketClient > max ? socketClient : max;
            FD_SET(socketClient, &readfs);
            clients[nb_client] = socketClient;
            int nJoueur = nb_client; //(on détecte le numéro du joueur)
            //On reçoit des informations du client (pseudo, texture etc...)
            readData(socketClient, &joueur);
            //On les stocke dans le tableau 
            nb_client++;
            if(nb_client == 1){
                j1=joueur;
            }else{
                j2=joueur;
            }
            printf("%s s'est connecté (%i/%i)\nSocket : %i\n", joueur.pseudo, nb_client, MAX_CLIENT, socketClient);
            printf("\n%s %s\n", j1.pseudo, j2.pseudo);
            if(nb_client == MAX_CLIENT){
                printf("\n%i  %s\n", clients[1], j1.pseudo) ;
                send(clients[1], &j1, sizeof(j1), 0);
                send(clients[0], &j2, sizeof(j2), 0);
            }

        }else{
            for(i = 0; i < nb_client; i++){
                if(FD_ISSET(clients[i], &readfs)){
                    SOCKET client = clients[i];
                    socket_t update;
                    readData(client, &update);
                    if(update.x_click == -1){ 
                        closesocket(client);
                        remove_client(clients, i, &nb_client);
                        printf("Le joueur %i s'est deconnecte (%i/%i)\n",client-socketServer, nb_client, MAX_CLIENT);
                    }else{
                        //printf("%i %i %s\n", update.x_click, update.y_click, update.pseudo);
                        send_all(clients, clients[i], &update, nb_client);                        
                    }
                }
            }
        }
    }
    closesocket(socketServer);
    printf("close\n");
    return 0;
}