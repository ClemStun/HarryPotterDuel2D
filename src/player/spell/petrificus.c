/**
 * \file petrificus.c
 * \brief Méthode de l'objet petrificus_t
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
#include "../../../lib/petrificus.h"

static void deplacement(petrificus_t *, int, int);
static void display(petrificus_t *, window *, images_t *images);
static int collision_test(petrificus_t **, int, int, player_t *);
static void destroy(petrificus_t **);

extern
petrificus_t * createPetrificus(player_t * player){

    petrificus_t * spell = malloc(sizeof(petrificus_t));

    spell->name = malloc(sizeof(char) * strlen("Petrificus"));
    strcpy(spell->name, "Petrificus");
    spell->speed = 2;
    spell->damage = 10;
    spell->manaCost = 20;
    spell->posXf = player->pos_x;
    spell->posYf = player->pos_y;
    SDL_GetMouseState(&(spell->destX), &(spell->destY));
    spell->width = 10;
    spell->height = 10;
    spell->sender = player->id_player;

    spell->deplacement = deplacement;
    spell->display = display;
    spell->collision_test = collision_test;
    spell->destroy = destroy;

    //printf("Petrificus lancé !\n");

    return spell;
}

static
void deplacement(petrificus_t * spell, int x_dest, int y_dest){

    float vx = x_dest - spell->posXf;
    float vy = y_dest - spell->posYf;

    double v = sqrt(vx*vx + vy*vy);
    float vxx = vx/v;
    float vyy = vy/v;

    spell->posXf += vxx * spell->speed;
    spell->posYf += vyy * spell->speed;

    spell->pos_x = spell->posXf;
    spell->pos_y = spell->posYf;
}

static
void display(petrificus_t * spell, window * win, images_t *images){

    DrawImage(win->pRenderer, images, searchTexture(images, "petrificus.png"), 0, 0, 64, 64, spell->pos_x, spell->pos_y, 64, 64);

}

static
int collision_test(petrificus_t ** spell, int x, int y, player_t * player){

    if((((*spell)->pos_x + (*spell)->width >= x) && ((*spell)->pos_x + (*spell)->width <= x + 10)) || (((*spell)->pos_x >= x) && ((*spell)->pos_x  <= x + 10)))
        if((((*spell)->pos_y + (*spell)->height >= y) && ((*spell)->pos_y + (*spell)->height <= y + 10)) || (((*spell)->pos_y >= y) && ((*spell)->pos_y  <= y + 10))){
            player->pt_life -= (*spell)->damage;
           player->id_timer = SDL_AddTimer(1000, player->unStun, player);
            if(player->id_timer == 0){
                printf("Error : %s\n", SDL_GetError());
            }
            (*spell)->destroy(spell);
            return 0;
        }

    return 1;
}

static
void destroy(petrificus_t ** spell){
    free((*spell)->name);
    free(*spell);
    *spell = NULL;
}
