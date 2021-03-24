/**
 * \file move.c
 * \brief Fonctions de déplacement.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "move.h"


/**
 * \fn extern void updatePosition(window * win, player_t * monPerso, images_t * images, int deplX, int deplY, double vitesse)
 * \brief Mise à jour de position de l'image pour atteindre le clique effectué par l'utilisateur en respectant la vitesse.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param deplX Coordonée en X du clic.
 * \param deplY Coordonée en Y du clic.
 * \param vitesse vitesse de déplacement du personnage.
 *
 */
 extern
 void updatePosition(window * win, player_t * monPerso, images_t * images, int deplX, int deplY, double vitesse){
     static double vit = 0.2;
     static double vX = 0, vY = 0, norme = 0;
     static double posXfloat = 50;
     static double posYfloat = 50;
     static int a = 1, b = 1;

     vX = (double)deplX - posXfloat;
     vY = (double)deplY - posYfloat;

     norme = sqrt(vX*vX + vY*vY);

     posXfloat += (vX/norme)*vit;
     posYfloat += (vY/norme)*vit;

     monPerso->pos_x = (int)posXfloat;
     monPerso->pos_y = (int)posYfloat;

     if((monPerso->pos_x < deplX-2 || monPerso->pos_x > deplX+2) || (monPerso->pos_y < deplY-2 || monPerso->pos_y > deplY+2)){
         vit = vitesse;
         if(b++ > 100){
             a++;
             b = 1;
         }
         DrawImage(win->pRenderer, images, "hp.png", (a%5)*32, 64, 32, 32, monPerso->pos_x, monPerso->pos_y, 100, 100);
     }
     else{
         vit = 0;
         DrawImage(win->pRenderer, images, "hp.png", 5*32, 64, 32, 32, monPerso->pos_x, monPerso->pos_y, 100, 100);
     }
 }
