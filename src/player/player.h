#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    SDL_Texture *sprite;

    int (*unStun)(int, struct player_s *);
} player_t;

extern int playerPosX(player_t * p);
extern int playerPosY(player_t * p);
player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite);