/**
 * \file player.c
 * \brief Fonctions utilisant principalement la SDL2.
 * \author COUTANT Hugo / COMTE Clément
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/player.h"

static int playerUnstun(int, player_t *);

/**
 * \fn extern player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite)
 * \brief Création d'un personnage et initialisation de ses valeurs.
 *
 * \param id_player Identifiant du joueur.
 * \param name Nom du personnage.
 * \param sprite Texture des sprites du personnage.
 * \return p Pointeur sur une structure player_s étant le nouveau personnage créé.
 */
extern
player_t * createPlayer(int id_player, char name[], SDL_Texture * sprite, sort_t * (*createSort[])(player_t *)){
    player_t * p;
    p = malloc(sizeof(player_t));

    p->id_player = id_player;
    strcpy(p->name, name);
    p->pos_x = 50;
    p->pos_y = 50;
    p->posXfloat = 50;
    p->posYfloat = 50;
    p->numSort = 0;
    p->pos_x_click = 200;
    p->pos_y_click = 200;
    p->pt_life = 100;
    p->pt_mana = 100;
    p->sprite = sprite;
    p->is_stun = 0;
    p->vitesse = 0.2;
    p->timerSprite = 1;
    p->numSprite = 1;

    for (int i = 0; i < 2; i++){
        p->createSort[i] = createSort[i];
    }
    

    p->unStun = playerUnstun;
    p->castSpell = p->createSort[p->numSort];
}

/**
 * \fn extern void freePlayer(player_t * p)
 * \brief Libération mémoire de la structure de personnage.
 *
 * \param p Pointeur sur une structure player_s à libérer.
 */
extern
void freePlayer(player_t * p){
    free(p);
}

/**
 * \fn extern int playerPosX(player_t * p)
 * \brief Position du joueur en X.
 *
 * \param p Pointeur sur une structure player_s.
 * \return int Position en X.
 */
extern
int playerPosX(player_t * p){
    return p->pos_x;
}

/**
 * \fn extern int playerPosY(player_t * p)
 * \brief Position du joueur en Y.
 *
 * \param p Pointeur sur une structure player_s.
 * \return int Position en Y.
 */
extern
int playerPosY(player_t * p){
    return p->pos_y;
}

static
int playerUnstun(int intervalle, player_t * player){
    if(SDL_RemoveTimer(player->id_timer)){
        player->is_stun = 0;
        printf("Je suis censé ne plus pop après ça \n");
    }
    printf("Player plus stun \n");
}
