/**
 * \file incendio.h
 * \brief Méthode de l'objet incendio_t
 * \author Comte Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#include <stdio.h>

/**
 * \file incendio.h
 * \brief Header de incendio.o
 * \author Comte Clément
 * \version 0.1
 * \date 31 mar 2021
 *
 */

/**
 * \struct incendio_s
 * \brief Structure du sort incendio_t contanenant toutes les informations
 *
 */
typedef struct incendio_s{

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

    void (*deplacement)(struct incendio_s *, int, int);
    void (*display)(struct incendio_s *, window *, images_t *images);
    int (*collision_test)(struct incendio_s **,int , int, player_t *);
    void (*destroy)(struct incendio_s **);

    int timer;

} incendio_t;

extern incendio_t * createIncendio(player_t *, int x, int y);
