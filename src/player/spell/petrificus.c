/**
 * \file petrificus.c
 * \brief Méthode de l'objet petrificus_t
 * \author Comte Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../../lib/player.h"
#include "../../../lib/petrificus.h"

static void deplacement(petrificus_t *, int, int);
static void display(petrificus_t *, window *, images_t *images);
static int collision_test(petrificus_t **, int, int, player_t *);
static void destroy(petrificus_t **);

/**
 * \fn extern petrificus_t * createPetrificus(player_t * player)
 * \brief Création d'un sort petrificus.
 *
 * \param player Pointeur sur le joueur player_t qui lance le sort.
 * \return Renvoie le sort créé qui est un élément de type petrificus_t.
 */
extern
petrificus_t * createPetrificus(player_t * player, int x, int y){

    if(player->pt_mana - 20 < 0)
        return NULL;

    petrificus_t * spell = malloc(sizeof(petrificus_t));

    spell->name = malloc(sizeof(char) * strlen("Petrificus"));
    strcpy(spell->name, "Petrificus");
    spell->speed = 2;
    spell->damage = 10;
    spell->manaCost = 20;

    //position réel du sort
    spell->posXf = player->pos_x;
    spell->posYf = player->pos_y;

    //point de destination du sort
    spell->destX = x;
    spell->destY = y;

    //taille du sort
    spell->width = 10;
    spell->height = 10;

    spell->sender = player->id_player;

    //méthode du sort
    spell->deplacement = deplacement;
    spell->display = display;
    spell->collision_test = collision_test;
    spell->destroy = destroy;

    player->pt_mana -= spell->manaCost;

    return spell;
}

/**
 * \fn static void deplacement(petrificus_t * spell, int x_dest, int y_dest)
 * \brief Mis a jour de la position d'un petrificus_t
 *
 * \param spell Pointeur sur l'élément petrificus_t en question
 * \param x_dest Position X de la destination du sort
 * \param y_dest Position Y de la destination du sort
 * \return Ne renvoie rien.
 */
static
void deplacement(petrificus_t * spell, int x_dest, int y_dest){

    //calcul du vecteur direction
    float vx = x_dest - spell->posXf;
    float vy = y_dest - spell->posYf;

    //mis en norme 1 du vecteur
    double v = sqrt(vx*vx + vy*vy);
    float vxx = vx/v;
    float vyy = vy/v;

    //calcul de la nouvelle position du sort
    spell->posXf += vxx * spell->speed;
    spell->posYf += vyy * spell->speed;

    //transformation du float en int pour afficher le sort
    spell->pos_x = spell->posXf;
    spell->pos_y = spell->posYf;
}

/**
 * \fn static void display(petrificus_t * spell, window * win, images_t *images)
 * \brief Affichage d'un petrificus_t
 *
 * \param spell Pointeur sur l'élément petrificus_t en question
 * \param win Fenetre dans laquelle le sort sera afficher
 * \param images Image de du sort
 * \return Ne renvoie rien.
 */
static
void display(petrificus_t * spell, window * win, images_t *images){

    DrawImage(win->pRenderer, images, searchTexture(images, "petrificus.png"), 0, 0, 64, 64, spell->pos_x, spell->pos_y, 64, 64);

}

/**
 * \fn static int collision_test(petrificus_t ** spell, int x, int y, player_t * player)
 * \brief Test des collisions entre un sort petrificus_t et un player_t player
 *
 * \param spell Pointeur sur pointeur d'un petrificus_t
 * \param x Position X max du sort
 * \param y Position Y max du sort
 * \param player Pointeur sur un player_t
 * \return Renvoie 0 s'il y a eu collision, 1 sinon.
 */
static
int collision_test(petrificus_t ** spell, int x, int y, player_t * player){

    //si le sort touche le joueur
    if((((*spell)->pos_x + (*spell)->width >= player->pos_x) && ((*spell)->pos_x + (*spell)->width <= player->pos_x + 100)) || (((*spell)->pos_x >= player->pos_x) && ((*spell)->pos_x  <= player->pos_x + 100)))
        if((((*spell)->pos_y + (*spell)->height >= player->pos_y) && ((*spell)->pos_y + (*spell)->height <= player->pos_y + 100)) || (((*spell)->pos_y >= player->pos_y) && ((*spell)->pos_y  <= player->pos_y + 100))){

            if(player->is_protego == 0){
                player->pt_life -= (*spell)->damage;
                player->is_stun = 1;
                //démarrage du timer d'enlevement de l'étourdissement (thread)
                player->id_timer = SDL_AddTimer(1000, player->unStun, player);
                if(player->id_timer == 0){
                    printf("Error : %s\n", SDL_GetError());
                }
            }
            (*spell)->destroy(spell);
            return 0;

        }

    //si le sort arrive a la destination finale
    if((((*spell)->pos_x + (*spell)->width >= x) && ((*spell)->pos_x + (*spell)->width <= x + 10)) || (((*spell)->pos_x >= x) && ((*spell)->pos_x  <= x + 10)))
        if((((*spell)->pos_y + (*spell)->height >= y) && ((*spell)->pos_y + (*spell)->height <= y + 10)) || (((*spell)->pos_y >= y) && ((*spell)->pos_y  <= y + 10))){

            (*spell)->destroy(spell);
            return 0;

        }

    return 1;
}

/**
 * \fn static void destroy(petrificus_t ** spell)
 * \brief Desttruction d'un petrificus_t
 *
 * \param spell Pointeur sur pointeur d'un petrificus_t destiné a être détruit
 * \return Ne renvoie rien.
 */
static
void destroy(petrificus_t ** spell){
    free((*spell)->name);
    free(*spell);
    *spell = NULL;
}
