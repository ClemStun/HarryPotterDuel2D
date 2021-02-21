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
    SDL_Texture *sprite;
} player_t;

extern player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite);
extern int playerPosX(player_t * p);
extern int playerPosY(player_t * p);
