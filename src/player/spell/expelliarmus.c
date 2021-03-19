/**
 * \file expelliarmus.c
 * \brief Méthode de l'objet expelliarmus_t
 * \author Comte Clément
 * \version 0.1
 * \date 09 feb 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../player.h"
#include "expelliarmus.h"

static void deplacement(expelliarmus_t *, int, int);
static void display(expelliarmus_t *, window *);
static int collision_test(expelliarmus_t **, int, int, player_t *);
static void destroy(expelliarmus_t **);

extern
expelliarmus_t * createExpelliarmus(player_t * player){

    expelliarmus_t * spell = malloc(sizeof(expelliarmus_t));

    spell->name = malloc(sizeof(char) * strlen("Expelliarmus"));
    strcpy(spell->name, "Expelliarmus");
    spell->speed = 5;
    spell->damage = 10;
    spell->manaCost = 10;
    spell->posXf = player->pos_x;
    spell->posYf = player->pos_y;
    spell->destX;
    spell->destY;
    SDL_GetMouseState(&(spell->destX), &(spell->destY));
    spell->width = 10;
    spell->height = 10;
    spell->sender = player->id_player;

    //spell->sprite = NULL;

    spell->deplacement = deplacement;
    spell->display = display;
    spell->collision_test = collision_test;
    spell->destroy = destroy;

    return spell;
}

static
void deplacement(expelliarmus_t * spell, int x_dest, int y_dest){

    //printf("YO!\n");

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
void display(expelliarmus_t * spell, window * win){

    //printf("YO displayed!\n");

    SDL_Rect display;
    display.x = spell->pos_x;
    display.y = spell->pos_y;
    display.w = 30;
    display.h = 30;

    SDL_SetRenderDrawColor(win->pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &display);

}
/*
static
int collision_test(expelliarmus_t * spell, player_t * player){

    if(((spell->pos_x + spell->width >= player->pos_x) && (spell->pos_x + spell->width <= player->width)) || ((spell->pos_x >= player->pos_x) && (spell->pos_x  <= player->width)))
        if(((spell->pos_y + spell->height >= player->pos_y) && (spell->pos_y + spell->height <= player->height + player->pos_y)) || ((spell->pos_y >= player->pos_y) && (spell->pos_y  <= player->pos_y + player->heihgt))){
            player->pt_life -= spell->damamge;
        }

}*/

static
int collision_test(expelliarmus_t ** spell, int x, int y, player_t * player){

    if((((*spell)->pos_x + (*spell)->width >= x) && ((*spell)->pos_x + (*spell)->width <= x + 10)) || (((*spell)->pos_x >= x) && ((*spell)->pos_x  <= x + 10)))
        if((((*spell)->pos_y + (*spell)->height >= y) && ((*spell)->pos_y + (*spell)->height <= y + 10)) || (((*spell)->pos_y >= y) && ((*spell)->pos_y  <= y + 10))){
            player->pt_life -= (*spell)->damage;
            player->pt_mana -= (*spell)->manaCost;
            (*spell)->destroy(spell);
            return 0;
        }

    return 1;
}

static
void destroy(expelliarmus_t ** spell){
    free((*spell)->name);
    free(*spell);
    *spell = NULL;
}
