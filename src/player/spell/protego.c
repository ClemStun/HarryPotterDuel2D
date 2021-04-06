/**
 * \file protego.c
 * \brief Méthode de l'objet protego_t
 * \author Comte Clément
 * \version 0.1
 * \date 09 feb 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../../lib/player.h"
#include "../../../lib/protego.h"

static int timer_end(protego_t **, int, int, player_t *);
static void display(protego_t * spell, window * win, images_t *images);
static void destroy(protego_t **);

/**
 * \fn extern protego_t * createProtego(player_t * player)
 * \brief Création d'un sort protego.
 *
 * \param player Pointeur sur le joueur player_t qui lance le sort.
 * \return Renvoie le sort créé qui est un élément de type protego_t.
 */
extern
protego_t * createProtego(player_t * player, int x, int y){

    if(player->pt_mana - 10 < 0)
        return NULL;

    protego_t * spell = malloc(sizeof(protego_t));

    spell->name = malloc(sizeof(char) * strlen("Protego"));
    strcpy(spell->name, "Protego");
    spell->speed = 0;
    spell->damage = 0;
    spell->manaCost = 20;
    spell->posXf = 0;
    spell->posYf = 0;
    spell->destX = 0;
    spell->destY = 0;
    spell->width = 0;
    spell->height = 0;
    spell->sender = player->id_player;

    spell->deplacement = NULL;
    spell->display = display;
    spell->collision_test = timer_end;
    spell->destroy = destroy;

    spell->timer = SDL_GetTicks();

    player->pt_mana -= spell->manaCost;
    player->is_protego = 1;

    return spell;
}

/**
 * \fn static void display(protego_t * spell, window * win, images_t *images)
 * \brief Affichage d'un protego_t
 *
 * \param spell Pointeur sur l'élément protego_t en question
 * \param win Fenetre dans laquelle le sort sera afficher
 * \param images Image de du sort
 * \return Ne renvoie rien.
 */
static
void display(protego_t * spell, window * win, images_t *images){

    //DrawImage(win->pRenderer, images, searchTexture(images, "protego.png"), 0, 0, 64, 64, spell->pos_x, spell->pos_y, 64, 64);
    SDL_Rect protego;
    protego.x = spell->pos_x;
    protego.y = spell->pos_y;
    protego.h = 100;
    protego.w = 100;

    SDL_SetRenderDrawColor(win->pRenderer, 0, 255, 0, 75);
    SDL_RenderDrawRect(win->pRenderer, &protego);
}

static
int timer_end(protego_t ** spell, int x, int y, player_t * player){

    if(SDL_GetTicks() - (*spell)->timer >= 6000){
        (*spell)->destroy(spell);
        return 1;
    }

    (*spell)->pos_x = player->pos_x;
    (*spell)->pos_y = player->pos_y;
    return 0;

}

/**
 * \fn static void destroy(protego_t ** spell)
 * \brief Desttruction d'un protego_t
 *
 * \param spell Pointeur sur pointeur d'un protego_t destiné a être détruit
 * \return Ne renvoie rien.
 */
static
void destroy(protego_t ** spell){
    free((*spell)->name);
    free(*spell);
    *spell = NULL;
}