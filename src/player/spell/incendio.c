/**
 * \file incendio.c
 * \brief Méthode de l'objet incendio_t
 * \author Comte Clément
 * \version 0.1
 * \date 31 mar 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../../lib/player.h"
#include "../../../lib/incendio.h"

static void deplacement(incendio_t *, int, int);
static void display(incendio_t * spell, window * win, images_t *images);
static int collision_test(incendio_t **, int, int, player_t *);
static void destroy(incendio_t **);

/**
 * \fn extern incendio_t * createIncendio(player_t * player)
 * \brief Création d'un sort incendio.
 *
 * \param player Pointeur sur le joueur player_t qui lance le sort.
 * \return Renvoie le sort créé qui est un élément de type incendio_t.
 */
extern
incendio_t * createIncendio(player_t * player, int x, int y){

    if(player->pt_mana - 20 < 0)
        return NULL;

    incendio_t * spell = malloc(sizeof(incendio_t));

    spell->name = malloc(sizeof(char) * strlen("Incendio"));
    strcpy(spell->name, "Incendio");
    spell->speed = 5;
    spell->damage = 2;
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

    //timer de la zone au sol après collision
    spell->timer = 0;

    player->pt_mana -= spell->manaCost;

    return spell;
}

/**
 * \fn static void deplacement(incendio_t * spell, int x_dest, int y_dest)
 * \brief Mis a jour de la position d'un incendio_t
 *
 * \param spell Pointeur sur l'élément incendio_t en question
 * \param x_dest Position X de la destination du sort
 * \param y_dest Position Y de la destination du sort
 * \return Ne renvoie rien.
 */
static
void deplacement(incendio_t * spell, int x_dest, int y_dest){

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
 * \fn static void display(incendio_t * spell, window * win, images_t *images)
 * \brief Affichage d'un incendio_t
 *
 * \param spell Pointeur sur l'élément incendio_t en question
 * \param win Fenetre dans laquelle le sort sera afficher
 * \param images Image du sort
 * \return Ne renvoie rien.
 */
static
void display(incendio_t * spell, window * win, images_t *images){

    DrawImage(win->pRenderer, images, searchTexture(images, "expelliarmus.png"), 0, 0, 64, 64, spell->pos_x, spell->pos_y, 64, 64);

}

/**
 * \fn static void display_zone(incendio_t * spell, window * win, images_t *images)
 * \brief Affichage de la zone au sol pour un incendio_t
 *
 * \param spell Pointeur sur l'élément incendio_t en question
 * \param win Fenetre dans laquelle le sort sera afficher
 * \param images Image du sort
 * \return Ne renvoie rien.
 */
static
void display_zone(incendio_t * spell, window * win, images_t *images){

    SDL_Rect zone;
    zone.x = spell->pos_x;
    zone.y = spell->pos_y;
    zone.w = spell->width;
    zone.h = spell->height;

    SDL_SetRenderDrawColor(win->pRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(win->pRenderer, &zone);

}

/**
 * \fn static int collision_test_zone(incendio_t ** spell, int x, int y, player_t * player)
 * \brief Test des collisions entre la zone au sol d'un sort incendio_t et un player_t player
 *
 * \param spell Pointeur sur pointeur d'un incendio_t
 * \param x Position X max du sort
 * \param y Position Y max du sort
 * \param player Pointeur sur un player_t
 * \return Renvoie 0 s'il y a eu collision, 1 sinon.
 */
static
int collision_test_zone(incendio_t ** spell, int x, int y, player_t * player){

    //si on arrive a la fin du timer
    if(SDL_GetTicks() - (*spell)->timer >= 3000){
        (*spell)->destroy(spell);
        return 1;
    }

    //si le joueur rentre dans la zone
    if((((*spell)->pos_x + (*spell)->width >= player->pos_x) && ((*spell)->pos_x + (*spell)->width <= player->pos_x + 100)) || (((*spell)->pos_x >= player->pos_x) && ((*spell)->pos_x  <= player->pos_x + 100)))
        if((((*spell)->pos_y + (*spell)->height >= player->pos_y) && ((*spell)->pos_y + (*spell)->height <= player->pos_y + 100)) || (((*spell)->pos_y >= player->pos_y) && ((*spell)->pos_y  <= player->pos_y + 100))){
    
            if(player->is_protego == 0)
                player->pt_life -= (*spell)->damage;
            return 0;

        }

    return 1;
}

/**
 * \fn static int collision_test(incendio_t ** spell, int x, int y, player_t * player)
 * \brief Test des collisions entre un sort incendio_t et un player_t player
 *
 * \param spell Pointeur sur pointeur d'un incendio_t
 * \param x Position X max du sort
 * \param y Position Y max du sort
 * \param player Pointeur sur un player_t
 * \return Renvoie 0 s'il y a eu collision, 1 sinon.
 */
static
int collision_test(incendio_t ** spell, int x, int y, player_t * player){

    //si le sort touche le joueur
    if((((*spell)->pos_x + (*spell)->width >= player->pos_x) && ((*spell)->pos_x + (*spell)->width <= player->pos_x + 100)) || (((*spell)->pos_x >= player->pos_x) && ((*spell)->pos_x  <= player->pos_x + 100)))
        if((((*spell)->pos_y + (*spell)->height >= player->pos_y) && ((*spell)->pos_y + (*spell)->height <= player->pos_y + 100)) || (((*spell)->pos_y >= player->pos_y) && ((*spell)->pos_y  <= player->pos_y + 100))){
    
            if(player->is_protego == 0)
                player->pt_life -= (*spell)->damage * 2;
            (*spell)->pos_x -= 50;
            (*spell)->pos_y -= 100;
            (*spell)->width = 100;
            (*spell)->height = 200;
            (*spell)->timer = SDL_GetTicks();
            (*spell)->deplacement = NULL;
            (*spell)->display = display_zone;
            (*spell)->collision_test = collision_test_zone;
            return 0;

        }

    //si le sort arrive au point de destination
    if((((*spell)->pos_x + (*spell)->width >= x) && ((*spell)->pos_x + (*spell)->width <= x + 10)) || (((*spell)->pos_x >= x) && ((*spell)->pos_x  <= x + 10)))
        if((((*spell)->pos_y + (*spell)->height >= y) && ((*spell)->pos_y + (*spell)->height <= y + 10)) || (((*spell)->pos_y >= y) && ((*spell)->pos_y  <= y + 10))){
            
            (*spell)->pos_x -= 50;
            (*spell)->pos_y -= 100;
            (*spell)->width = 100;
            (*spell)->height = 200;
            (*spell)->timer = SDL_GetTicks();
            (*spell)->deplacement = NULL;
            (*spell)->display = display_zone;
            (*spell)->collision_test = collision_test_zone;
            return 0;

        }

    return 1;
}

/**
 * \fn static void destroy(incendio_t ** spell)
 * \brief Desttruction d'un incendio_t
 *
 * \param spell Pointeur sur pointeur d'un incendio_t destiné a être détruit
 * \return Ne renvoie rien.
 */
static
void destroy(incendio_t ** spell){
    free((*spell)->name);
    free(*spell);
    *spell = NULL;
}
