/**
 * \file player.c
 * \brief Fonctions d'actions sur une entité joueur.
 * \author COUTANT Hugo / COMTE Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#include "../../lib/player.h"

static int playerUnstun(int, player_t *);

/**
 * \fn extern player_t * createPlayer(int id_player, char name[], int xp, SDL_Texture * sprite, cd_t setSort[], int x, int y)
 * \brief Création d'un personnage et initialisation de ses valeurs.
 *
 * \param id_player Identifiant du joueur.
 * \param name Nom du personnage.
 * \param xp Experience du personnage.
 * \param sprite Texture des sprites du personnage.
 * \param setSort Tableau de sort du personnage.
 * \param x Position en X initiale du personnage.
 * \param y Position en Y initiale du personnage.
 *
 * \return p Pointeur sur une structure player_s étant le nouveau personnage créé.
 */
extern
player_t * createPlayer(int id_player, char name[], int xp, SDL_Texture * sprite, cd_t setSort[], int x, int y){
    player_t * p;
    p = malloc(sizeof(player_t));

    //initialisation de tous les éléments de la structure
    p->id_player = id_player;
    strcpy(p->name, name);
    p->house = 'n';
    p->pos_x = x;
    p->pos_y = y;
    p->posXfloat = (float)x;
    p->posYfloat = (float)y;
    p->numSort = 0;
    p->pos_x_click = x+10;
    p->pos_y_click = y+10;
    p->pt_life = 100;
    p->pt_mana = 100;
    p->pt_xp = xp;
    p->sprite = sprite;
    p->is_stun = 0;
    p->is_protego = 0;
    p->vitesse = 0.2;
    p->timerSprite = 1;
    p->numSprite = 1;
    p->nb_pot = 0;
    p->potions_unl = NULL;

    if(setSort != NULL){
        for (int i = 0; i < NB_SORT; i++){
            p->createSort[i] = setSort[i];
        }
    }

    p->unStun = playerUnstun;

    return p;
}

/**
 * \fn extern void freePlayer(player_t * p)
 * \brief Libération mémoire de la structure de personnage.
 *
 * \param p Pointeur sur une structure player_s à libérer.
 */
extern
void freePlayer(player_t * p){
    free(p->potions_unl);
    free(p);
}

static
int playerUnstun(int intervalle, player_t * player){
    if(SDL_RemoveTimer(player->id_timer)){
        player->is_stun = 0;
    }
}

/**
 * \fn extern void rand_click_bot(player_t *mannequin)
 * \brief Genereration d'une position de click pour un personnage ennemi dans la zone ennemie.
 *
 * \param mannequin Pointeur sur une structure player_s à déplacer aléatoirement.
 */
extern
void rand_click_bot(player_t *mannequin){

    if(mannequin->vitesse == 0){
        mannequin->pos_x_click = rand()%200+900;
        mannequin->pos_y_click = rand()%400+100;
    }
}
