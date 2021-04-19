/**
 * \file petrificus.h
 * \brief Header de petrificus.c.
 * \author Comte Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#include <stdio.h>

/**
 * \struct petrificus_s
 * \brief Structure du sort petrificus_t contanenant toutes les informations
 *
 */
typedef struct petrificus_s{

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

    void (*deplacement)(struct petrificus_s *, int, int);
    void (*display)(struct petrificus_s *, window *, images_t *images);
    int (*collision_test)(struct petrificus_s **,int , int, player_t *);
    void (*destroy)(struct petrificus_s **);

} petrificus_t;

extern petrificus_t * createPetrificus(player_t *, int x, int y);
