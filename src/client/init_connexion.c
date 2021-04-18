#include "../../lib/sdl.h"
#include "../../lib/sort.h"
#include "../../lib/init_connexion.h"



extern
int init_connexion(socket_t j1){
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrClient;
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrClient.sin_family = AF_INET;
    int port;
    printf("PORTS : ");
    scanf("%i",&port);
    addrClient.sin_port = htons(port);
    if(connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient)) == -1){
        perror("connect()");
        exit(-1);
    }

    return socketClient;

}
