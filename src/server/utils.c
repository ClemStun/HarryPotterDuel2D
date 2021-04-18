/**
 * \file utils.c
 * \brief Fonctions utiles pour les sockets
 * \author COLLET Matthieu
 * \version 0.1
 * \date 19 feb 2021
 *
 */

#include "../../lib/sdl.h"
#include "../../lib/sort.h"
#include "init.h"

/**
 * \fn extern void send_all(SOCKET *clients, SOCKET sender, player_t *joueur, int nb_client)
 * \brief Envoie de socket à tous les clients en dehors du sender
 *
 * @param clients Tous les clients connectés au server
 * @param sender Client qui a envoyé le socket
 * @param joueur Donnée à transmettre à tous les clients
 * @param nb_client Nombre de client connectés au server
 *
 * @return Ne retourne rien
 */
extern
void send_all(SOCKET *clients, SOCKET sender, socket_t *joueur, int nb_client);

/**
 * \fn extern void remove_client(SOCKET *clients, SOCKET client, int *nb_client)
 * \brief Retire un client du server
 *
 * @param clients Tous les clients connectés au server
 * @param client Client a retirer
 * @param nb_client Nombre de client connectés au server
 *
 * @return Ne retourne rien
 */
extern
void remove_client(SOCKET *clients, SOCKET client, int *nb_client);

/**
 * \fn extern player_t readData(SOCKET socket, player_t *joueur)
 * \brief Fonction de lecture d'une socket
 *
 * @param socket Socket du client qui envoie la donnée
 * @param joueur Pointeur du joueur à modifier
 *
 * @return Ne retourne rien
 */
extern
void readData(SOCKET socket, socket_t *joueur);


extern
void send_all(SOCKET *clients, SOCKET sender, socket_t *joueur, int nb_client){
    //Pour tous les clients, on envoie la donnée si le client n'est pas le client qui a envoyé la donnée
    int i;
    for(i = 0; i < nb_client; i++){
        if(sender != clients[i]){
            if(send(clients[i], joueur, sizeof (socket_t), 0) < 0){
                perror("send()");
                exit(-1);
            }
        }
    }
}

extern
void remove_client(SOCKET *clients, SOCKET i, int *nb_client){
   memmove(clients + i, clients + i + 1, (*nb_client - i - 1) * sizeof(SOCKET));
   (*nb_client)--;
}

extern
void readData(SOCKET socket, socket_t *joueur){
    if((recv(socket, joueur, sizeof(socket_t) , 0)) < 0){
      perror("recv()");
   }
}