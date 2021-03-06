/**
 * \file protego.c
 * \brief Méthode de l'objet protego_t
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

    //position réel du sort = celle du personnage
    spell->posXf = 0;
    spell->posYf = 0;

    //pas de destination
    spell->destX = 0;
    spell->destY = 0;

    //la taille correspond a celle du joueur
    spell->width = 0;
    spell->height = 0;

    spell->sender = player->id_player;

    //pas de méthode de déplacement (gérer dans timer_end)
    spell->deplacement = NULL;
    //méthode d'affichage de protego_t
    spell->display = display;
    //méthode de fin de sort de protego_t
    spell->collision_test = timer_end;
    //méthode de destruction de protego_t
    spell->destroy = destroy;

    //timer fin de protection
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

    DrawImage(win->pRenderer, images, searchTexture(images, "protego.png"), 0, 0, 556, 556, spell->pos_x-10, spell->pos_y-30, 120, 150);
}

/**
 * \fn static int timer_end(protego_t ** spell, int x, int y, player_t * player)
 * \brief Test de fin de timer de protection + déplacement du sort sur le joueur
 *
 * \param spell Pointeur sur l'élément protego_t en question
 * \param x non utiliser (utilisé pour garder la forme général de la fonction)
 * \param y non utiliser (utilisé pour garder la forme général de la fonction)
 * \param player Joueur qui a lancer le sort de protection
 * \return Renvoie 1 si le timer est fini 0 sinon
 */
static
int timer_end(protego_t ** spell, int x, int y, player_t * player){

    //si le timer de protection est fini
    if(SDL_GetTicks() - (*spell)->timer >= 6000){
        (*spell)->destroy(spell);
        player->is_protego = 0;
        return 1;
    }

    //déplacement du sort sur le joueur
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
