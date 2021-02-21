/**
 * \file move.c
 * \brief Fonctions de déplacement
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../sdl/sdl.h"


/**
 * \fn extern void updatePosition(window * win, images_t * images, int deplX, int deplY)
 * \brief Mise à jour de position de image en fonction du clique
 *
 * @param win Structure de la fenêtre de jeu
 * @param images Structure de la liste des images
 * @param deplX Coordonée en X du clique
 * @param deplY Coordonée en Y du clique
 *
 * @return Ne retourne rien
 */
extern
void updatePosition(window * win, images_t * images, int deplX, int deplY);



int posX = 50, posY = 50;
double posXfloat = 50, posYfloat = 50;
double vitesse = 0;
double vX = 0, vY = 0, norme = 0;
int a = 1, b = 1;

extern
void updatePosition(window * win, images_t * images, int deplX, int deplY){
    vX = (double)deplX - posXfloat;
    vY = (double)deplY - posYfloat;

    norme = sqrt(vX*vX + vY*vY);

    posXfloat += (vX/norme)*vitesse;
    posYfloat += (vY/norme)*vitesse;

    posX = (int)posXfloat;
    posY = (int)posYfloat;

    if((posX < deplX-2 || posX > deplX+2) || (posY < deplY-2 || posY > deplY+2)){
        vitesse = 0.2;
        if(b++ > 100){
            a++;
            b = 1;
        }
        DrawImage(win->pRenderer, images, "hp.png", (a%5)*32, 64, 32, 32, posX, posY, 100, 100);
    }
    else{
        vitesse = 0;
        DrawImage(win->pRenderer, images, "hp.png", 5*32, 64, 32, 32, posX, posY, 100, 100);
    }
}