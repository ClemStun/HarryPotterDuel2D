/**
 * \file player.h
 * \brief Header du fichier player.c.
 * \author COUTANT Hugo / COMTE Clément
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include <stdio.h>

#include "sdl.h"
#include "sort.h"

/**
 * \struct player_s
 * \brief Informations d'un personnage.
 *
 * Toutes les statistiques liées au personnage nécessaire au fonctionnement du jeu et de l'affichage des informations.
 */
typedef struct player_s{
    int id_player;
    char name[16];
    int pos_x;
    int pos_y;
    double posXfloat;
    double posYfloat;
    int pos_x_click;
    int pos_y_click;
    sort_t * (*createSort[5])(struct player_s *);
    int pt_life;
    int pt_mana;
    int pt_xp;
    int numSort;
    double vitesse;
    int timerSprite;
    int numSprite;
    int is_stun;
    SDL_TimerID id_timer;
    SDL_Texture *sprite;

    int (*unStun)(int, struct player_s *);
    sort_t * (*castSpell)(struct player_s *);

} player_t;

extern player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite, sort_t * (*createSort[])(struct player_s *));
extern void freePlayer(player_t * p);
extern int playerPosX(player_t * p);
extern int playerPosY(player_t * p);
