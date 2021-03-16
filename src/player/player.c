#include "player.h"

static int playerUnstun(int, int *);

extern
player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite){
    player_t * p;
    p = malloc(sizeof(player_t));

    p->id_player = id_player;
    p->pos_x = 30;
    p->pos_y = 30;
    p->pt_life = 100;
    p->pt_mana = 100;
    p->sprite = sprite;
    p->is_stun = 0;

    p->unStun = playerUnstun;
    p->castSpell = NULL;
}

extern
int playerPosX(player_t * p){
    return p->pos_x;
}

extern
int playerPosY(player_t * p){
    return p->pos_y;
}

static
int playerUnstun(int intervalle, SDL_TimerID * id_timer){
    if(SDL_RemoveTimer(*id_timer))
        printf("Je suis censé ne plus pop après ça \n");
    printf("Player plus stun \n");
}
