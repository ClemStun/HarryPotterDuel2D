/**
 * \file init.h
 * \brief Header de init.c.
 * \author COLLET Matthieu
 * \version 1
 * \date 17 avril 2021
 *
 */

#include "utils.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENT 2
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

extern
SOCKET init_connexion(void);