/**
 * \file player.h
 * \brief Header du fichier player.c.
 * \author COUTANT Hugo / COMTE Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>

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
    char house; // g pour Griffondor, s pour Serpentard, r pour Serdaigle, p pour Poufsouffle
    int pos_x;
    int pos_y;
    double posXfloat;
    double posYfloat;
    int pos_x_click;
    int pos_y_click;
    cd_t createSort[5];
    int pt_life;
    int pt_mana;
    int pt_xp;
    int numSort;
    double vitesse;
    int timerSprite;
    int numSprite;
    int is_stun;
    int is_protego;
    SDL_TimerID id_timer;
    SDL_Texture *sprite;
    int nb_pot;
    int *potions_unl;

    int (*unStun)(int, struct player_s *);

} player_t;

extern player_t * createPlayer(int id_player, char name[], int xp, SDL_Texture * sprite, cd_t setSort[], int x, int y);
extern void freePlayer(player_t * p);
extern int playerPosX(player_t * p);
extern int playerPosY(player_t * p);
extern void rand_click_bot(player_t *mannequin);

