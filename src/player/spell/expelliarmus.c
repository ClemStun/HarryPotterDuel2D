/**
 * \file expelliarmus.c
 * \brief Méthode de l'objet expelliarmus_t
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
#include "../../../lib/expelliarmus.h"

static void deplacement(expelliarmus_t *, int, int);
static void display(expelliarmus_t * spell, window * win, images_t *images);
static int collision_test(expelliarmus_t **, int, int, player_t *);
static void destroy(expelliarmus_t **);

/**
 * \fn extern expelliarmus_t * createExpelliarmus(player_t * player)
 * \brief Création d'un sort expelliarmus.
 *
 * \param player Pointeur sur le joueur player_t qui lance le sort.
 * \return Renvoie le sort créé qui est un élément de type expelliarmus_t.
 */
extern
expelliarmus_t * createExpelliarmus(player_t * player, int x, int y){

    if(player->pt_mana - 10 < 0)
        return NULL;

    expelliarmus_t * spell = malloc(sizeof(expelliarmus_t));

    spell->name = malloc(sizeof(char) * strlen("Expelliarmus"));
    strcpy(spell->name, "Expelliarmus");
    spell->speed = 5;
    spell->damage = 10;
    spell->manaCost = 10;

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
 * \fn static void deplacement(expelliarmus_t * spell, int x_dest, int y_dest)
 * \brief Mis a jour de la position d'un expelliarmus_t
 *
 * \param spell Pointeur sur l'élément expelliarmus_t en question
 * \param x_dest Position X de la destination du sort
 * \param y_dest Position Y de la destination du sort
 * \return Ne renvoie rien.
 */
static
void deplacement(expelliarmus_t * spell, int x_dest, int y_dest){

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
 * \fn static void display(expelliarmus_t * spell, window * win, images_t *images)
 * \brief Affichage d'un expelliarmus_t
 *
 * \param spell Pointeur sur l'élément expelliarmus_t en question
 * \param win Fenetre dans laquelle le sort sera afficher
 * \param images Image de du sort
 * \return Ne renvoie rien.
 */
static
void display(expelliarmus_t * spell, window * win, images_t *images){

    DrawImage(win->pRenderer, images, searchTexture(images, "expelliarmus.png"), 0, 0, 64, 64, spell->pos_x, spell->pos_y, 64, 64);

}

/**
 * \fn static int collision_test(expelliarmus_t ** spell, int x, int y, player_t * player)
 * \brief Test des collisions entre un sort expelliarmus_t et un player_t player
 *
 * \param spell Pointeur sur pointeur d'un expelliarmus_t
 * \param x Position X max du sort
 * \param y Position Y max du sort
 * \param player Pointeur sur un player_t
 * \return Renvoie 0 s'il y a eu collision, 1 sinon.
 */
static
int collision_test(expelliarmus_t ** spell, int x, int y, player_t * player){

    //si on touche le sort
    if((((*spell)->pos_x + (*spell)->width >= player->pos_x) && ((*spell)->pos_x + (*spell)->width <= player->pos_x + 100)) || (((*spell)->pos_x >= player->pos_x) && ((*spell)->pos_x  <= player->pos_x + 100)))
        if((((*spell)->pos_y + (*spell)->height >= player->pos_y) && ((*spell)->pos_y + (*spell)->height <= player->pos_y + 100)) || (((*spell)->pos_y >= player->pos_y) && ((*spell)->pos_y  <= player->pos_y + 100))){

            if(player->is_protego == 0)
                player->pt_life -= (*spell)->damage;
            (*spell)->destroy(spell);
            return 0;

        }

    //si on touche le point de destination
    if((((*spell)->pos_x + (*spell)->width >= x) && ((*spell)->pos_x + (*spell)->width <= x + 10)) || (((*spell)->pos_x >= x) && ((*spell)->pos_x  <= x + 10)))
        if((((*spell)->pos_y + (*spell)->height >= y) && ((*spell)->pos_y + (*spell)->height <= y + 10)) || (((*spell)->pos_y >= y) && ((*spell)->pos_y  <= y + 10))){

            (*spell)->destroy(spell);
            return 0;

        }

    return 1;
}

/**
 * \fn static void destroy(expelliarmus_t ** spell)
 * \brief Desttruction d'un expelliarmus_t
 *
 * \param spell Pointeur sur pointeur d'un expelliarmus_t destiné a être détruit
 * \return Ne renvoie rien.
 */
static
void destroy(expelliarmus_t ** spell){
    free((*spell)->name);
    free(*spell);
    *spell = NULL;
}
