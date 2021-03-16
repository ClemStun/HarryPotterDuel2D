#include <stdio.h>

#include "../sdl/sdl.h"
#include "./spell/sort.h"

typedef struct player_s{
    int id_player;
    char name[16];
    int pos_x;
    int pos_y;
    int set_sort[5];
    int pt_life;
    int pt_mana;
    int pt_xp;
    int is_stun;
    SDL_TimerID id_timer;
    SDL_Texture *sprite;

    int (*unStun)(int, SDL_TimerID *);
    sort_t * (*castSpell)(int, int, int); 

} player_t;

extern player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite);
extern int playerPosX(player_t * p);
extern int playerPosY(player_t * p);
