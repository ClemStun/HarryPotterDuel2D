/**
 * \file protego.h
 * \brief Méthode de l'objet protego_t
 * \author Comte Clément
 * \version 0.1
 * \date 31 mar 2021
 *
 */

#include <stdio.h>

/**
 * \file protego.h
 * \brief Header de protego.o
 * \author Comte Clément
 * \version 0.1
 * \date 31 mar 2021
 *
 */

/**
 * \struct protego_s
 * \brief Structure du sort protego_t contanenant toutes les informations
 *
 */
typedef struct protego_s{

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

    void (*deplacement)(struct protego_s *, int, int);
    void (*display)(struct protego_s *, window *, images_t *images);
    int (*collision_test)(struct protego_s **,int , int, player_t *);
    void (*destroy)(struct protego_s **);

    int timer;

} protego_t;

extern protego_t * createProtego(player_t *);