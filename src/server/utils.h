typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct player_s{
    int id;
    int x;
    int y;
    char pseudo[16];
    

}player_t;

extern
void send_all(SOCKET *clients, SOCKET sender, player_t *joueur, int nb_client);

extern
void remove_client(SOCKET *clients, SOCKET client, int *nb_client);

extern
void readData(SOCKET socket, player_t *joueur);