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

#include "../player.h"
#include "petrificus.h"

/**
 * \fn extern petrificus_t * createPetrificus(int x, int y)
 * \brief création d'un objet petrificus_t
 *
 * @param x Entier de la coordonée x de l'objet
 * @param y Entier de la coordonée y de l'objet
 *
 * @return Retourne un objet petrificus_t
 */
extern petrificus_t * createPetrificus(int, int, int, int, int);

/**
 * \fn static void deplacement(petrificus_t * spell, int x, int y);
 * \brief Déplacment d'un objet petrificus_t
 *
 * @param spell Pointeur sur l'objet petrificus_t qui a déplacer
 * @param x Entier de la coordonée x de destination de l'objet
 * @param y Entier de la coordonée y de destination de l'objet
 *
 * @return void
 */
static void deplacement(petrificus_t *, int, int);

/**
 * \fn static void display(petrificus_t * spell);
 * \brief Affichage d'un objet petrificus_t
 *
 * @param spell Pointeur sur l'objet petrificus_t a afficher
 *
 * @return void
 */
static void display(petrificus_t *, window *);

/**
 * \fn static int collision_test(petrificus_t * spell, int x, int y);
 * \brief Test de collision entre l'objet petrificus_t et un joueurs
 *
 * @param spell Pointeur sur l'objet petrificus_t a afficher
 *
 * @return Entier 0 s'il y a collision 1 sinon
 */
static int collision_test(petrificus_t *, int, int, int *, int *, SDL_TimerID *, int (*)(int, int *));

/**
 * \fn static void destroy(petrificus_t ** spell);
 * \brief Destruction d'un objet petrificus_t
 *
 * @param spell Pointeur sur un pointeur d'objet petrificus_t a afficher
 *
 * @return void
 */
static void destroy(petrificus_t **);

extern
petrificus_t * createPetrificus(int player_posX, int player_posY, int id_player, int destX, int destY){

    petrificus_t * spell = malloc(sizeof(petrificus_t));

    spell->name = malloc(sizeof(char) * strlen("Petrificus"));
    strcpy(spell->name, "Petrificus");
    spell->speed = 2;
    spell->damage = 10;
    spell->manaCost = 20;
    spell->posXf = player_posX;
    spell->posYf = player_posY;
    spell->destX = destX;
    spell->destY = destY;
    spell->width = 10;
    spell->height = 10;
    spell->sender = id_player;

    //spell->sprite = NULL;

    spell->deplacement = deplacement;
    spell->display = display;
    spell->collision_test = collision_test;
    spell->destroy = destroy;

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
void display(petrificus_t * spell, window * win){

    SDL_Rect display;
    display.x = spell->pos_x;
    display.y = spell->pos_y;
    display.w = 30;
    display.h = 30;

    SDL_SetRenderDrawColor(win->pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &display);

}

static
int collision_test(petrificus_t * spell, int x, int y, int * pt_life, int * pStun, SDL_TimerID * id_timer, int (*unStun)(int , int *)){

    if(((spell->pos_x + spell->width >= x) && (spell->pos_x + spell->width <= x + 10)) || ((spell->pos_x >= x) && (spell->pos_x  <= x + 10)))
        if(((spell->pos_y + spell->height >= y) && (spell->pos_y + spell->height <= y + 10)) || ((spell->pos_y >= y) && (spell->pos_y  <= y + 10))){
            *pt_life -= spell->damage;
            id_timer = SDL_AddTimer(1000, unStun, id_timer);
            if(id_timer == 0){
                printf("Error : %s\n", SDL_GetError());
            }
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
