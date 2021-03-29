/**
 * \file expelliarmus.h
 * \brief Méthode de l'objet expelliarmus_t
 * \author Comte Clément
 * \version 0.1
 * \date 09 feb 2021
 *
 */

#include <stdio.h>

/**
 * \struct expelliarmus_s
 * \brief Structure du sort expelliarmus_t contanenant toutes les informations
 *
 */
typedef struct expelliarmus_s{

    char * name;
    int speed;
    int damage;
    int manaCost;
    int pos_x;
    int pos_y;
    int destX;
    int destY;
    float posXf;
    float posYf;
    int width;
    int height;
    int sender;

    void (*deplacement)(struct expelliarmus_s *, int, int);
    void (*display)(struct expelliarmus_s *, window *, images_t *images);
    int (*collision_test)(struct expelliarmus_s **,int , int, player_t *);
    void (*destroy)(struct expelliarmus_s **);

} expelliarmus_t;

extern expelliarmus_t * createExpelliarmus(player_t *);
