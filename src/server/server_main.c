#include "init.h"

int main(){
    SOCKET socketServer = init_connexion();
    SOCKET clients[MAX_CLIENT];
    int nb_client = 0;
    int max = socketServer;
    fd_set readfs;

    player_t *joueur;
    player_t **joueurs;
    joueur = malloc(sizeof(player_t));
    joueurs = malloc(sizeof(player_t)*MAX_CLIENT);
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
            nb_client++;
            //On reçoit des informations du client (pseudo, texture etc...)
            readData(socketClient, joueur);
            int nJoueur = socketClient-socketServer; //(on détecte le numéro du joueur)
            //On les stocke dans le tableau 
            joueurs[nJoueur-1] = joueur;
            if(nb_client == MAX_CLIENT){
                send(clients[0], joueurs[0], sizeof (player_t), 0);
                send(clients[1], joueurs[1], sizeof (player_t), 0);                
            }
            printf("%s s'est connecté (%i/%i)\n", joueur->pseudo, nb_client, MAX_CLIENT);

        }else{
            for(i = 0; i < nb_client; i++){
                if(FD_ISSET(clients[i], &readfs)){
                    SOCKET client = clients[i];
                    readData(client, joueur);
                    if(joueur->x == -1){ 
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
    free(joueurs[0]);
    free(joueurs[1]);
    free(joueurs);
    return 0;
}