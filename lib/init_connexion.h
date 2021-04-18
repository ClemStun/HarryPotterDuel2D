/**
 * \file init_connexion.h
 * \brief Header de init_connexion.c.
 * \author COLLET Matthieu
 * \version 1
 * \date 17 avril 2021
 *
 */

#include "socket_struc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
extern
int init_connexion(socket_t pseudo);