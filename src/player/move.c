/**
 * \file move.c
 * \brief Fonctions de déplacement.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/move.h"


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
     double vX = 0, vY = 0, norme = 0;
     int miror = 2;

     if(monPerso->id_player == 2) miror = 1;
     if(monPerso->is_stun) monPerso->vitesse = 0;

     vX = (double)deplX - (monPerso->posXfloat);
     vY = (double)deplY - (monPerso->posYfloat);

     norme = sqrt(vX*vX + vY*vY);

     monPerso->posXfloat += (vX/norme)*monPerso->vitesse;
     monPerso->posYfloat += (vY/norme)*monPerso->vitesse;

     monPerso->pos_x = (int)monPerso->posXfloat;
     monPerso->pos_y = (int)monPerso->posYfloat;

     if(((monPerso->pos_x < deplX-2 || monPerso->pos_x > deplX+2) || (monPerso->pos_y < deplY-2 || monPerso->pos_y > deplY+2)) && monPerso->is_stun == 0){
         monPerso->vitesse = vitesse;
         if((monPerso->timerSprite)++ > 100){
             (monPerso->numSprite)++;
             monPerso->timerSprite = 1;
         }
         if(monPerso->numSprite > 5){
             monPerso->numSprite = 1;
         }
         DrawImage(win->pRenderer, images, monPerso->sprite, ((monPerso->numSprite)%5)*32, miror*32, 32, 32, monPerso->pos_x, monPerso->pos_y, 100, 100);
     }
     else{
         monPerso->vitesse = 0;
         DrawImage(win->pRenderer, images, monPerso->sprite, 5*32, miror*32, 32, 32, monPerso->pos_x, monPerso->pos_y, 100, 100);
     }
 }
