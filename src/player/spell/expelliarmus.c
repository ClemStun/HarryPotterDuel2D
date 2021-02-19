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

#include "expelliarmus.h"

/**
 * \fn extern expelliarmus_t * createExpelliarmus(int x, int y)
 * \brief création d'un objet expelliarmus_t
 *
 * @param x Entier de la coordonée x de l'objet
 * @param y Entier de la coordonée y de l'objet
 *
 * @return Retourne un objet expelliarmus_t
 */
extern expelliarmus_t * createExpelliarmus(int, int);

/**
 * \fn static void deplacement(expelliarmus_t * spell, int x, int y);
 * \brief Déplacment d'un objet expelliarmus_t
 *
 * @param spell Pointeur sur l'objet expelliarmus_t qui a déplacer
 * @param x Entier de la coordonée x de destination de l'objet
 * @param y Entier de la coordonée y de destination de l'objet
 *
 * @return void
 */
static void deplacement(expelliarmus_t *, int, int);

/**
 * \fn static void display(expelliarmus_t * spell);
 * \brief Affichage d'un objet expelliarmus_t
 *
 * @param spell Pointeur sur l'objet expelliarmus_t a afficher
 *
 * @return void
 */
static void display(expelliarmus_t *);

/**
 * \fn static int collision_test(expelliarmus_t * spell, int x, int y);
 * \brief Test de collision entre l'objet expelliarmus_t et un joueurs
 *
 * @param spell Pointeur sur l'objet expelliarmus_t a afficher
 *
 * @return Entier 0 s'il y a collision 1 sinon
 */
static int collision_test(expelliarmus_t *, int, int);

/**
 * \fn static void destroy(expelliarmus_t ** spell);
 * \brief Destruction d'un objet expelliarmus_t
 *
 * @param spell Pointeur sur un pointeur d'objet expelliarmus_t a afficher
 *
 * @return void
 */
static void destroy(expelliarmus_t **);

extern
expelliarmus_t * createExpelliarmus(int x, int y){

    expelliarmus_t * spell = malloc(sizeof(expelliarmus_t));

    strcpy(spell->name, "Expelliarmus");
    spell->speed = 5;
    spell->damage = 10;
    spell->pos_x = x;//player->pos_x;
    spell->pos_y = y;//player->pos_y;
    spell->width = 10;
    spell->height = 10;
    spell->sender = 0;//player->id_player;

    //spell->sprite = NULL;

    spell->deplacement = deplacement;
    spell->display = display;
    spell->collision_test = collision_test;

    return spell;
}

static
void deplacement(expelliarmus_t * spell, int x_dest, int y_dest){

    float vx = x_dest - spell->pos_x;
    float vy = y_dest - spell->pos_y;

    double v = sqrt(vx*vx + vy*vy);
    float vxx = vx/v;
    float vyy = vy/v;

    spell->pos_x += vxx * spell->speed;
    spell->pos_y += vyy * spell->speed;
}

static
void display(expelliarmus_t * spell){

    //Hugo je te laisse faire ça

    //TU VEUX QUE TE DEMARRRRE

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
int collision_test(expelliarmus_t * spell, int x, int y){

    if(((spell->pos_x + spell->width >= x) && (spell->pos_x + spell->width <= x)) || ((spell->pos_x >= x) && (spell->pos_x  <= x)))
        if(((spell->pos_y + spell->height >= y) && (spell->pos_y + spell->height <= y)) || ((spell->pos_y >= y) && (spell->pos_y  <= y))){
            //player->pt_life -= spell->damage;
            return 0;
        }

    return 1;
}

static
void destroy(expelliarmus_t ** spell){
    free(*spell);
    *spell = NULL;
}
