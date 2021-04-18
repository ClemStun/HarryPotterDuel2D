/**
 * \file utils.h
 * \brief Header de utils.c
 * \author COLLET Matthieu
 * \version 1
 * \date 17 avril 2021
 *
 */

#include "../../lib/socket_struc.h"
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

extern
void send_all(SOCKET *clients, SOCKET sender, socket_t *joueur, int nb_client);

extern
void remove_client(SOCKET *clients, SOCKET client, int *nb_client);

extern
void readData(SOCKET socket, socket_t *joueur);