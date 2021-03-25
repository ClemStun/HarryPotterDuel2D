/**
 * \file move.c
 * \brief Fonctions de déplacement.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/hud_ingame.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

/**
 * \fn extern void updatePosition(window * win, player_t * monPerso, images_t * images, int deplX, int deplY, double vitesse)
 * \brief Mise à jour de position de l'image pour atteindre le clique effectué par l'utilisateur en respectant la vitesse.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 *
 */
extern
void update_hud_ingame(window * win, images_t * images, player_t * monPerso){

    SDL_Rect life;
    life.x = 10;
    life.y = SCREEN_HEIGHT - 40;
    life.w = monPerso->pt_life*2;
    life.h = 20;

    SDL_Rect mana;
    mana.x = SCREEN_WIDTH - 210;
    mana.y = SCREEN_HEIGHT - 40;
    mana.w = monPerso->pt_mana*2;
    mana.h = 20;

    DrawImage(win->pRenderer, images, "hud_tmp.png", 0, 0, 1200, 60, 0, SCREEN_HEIGHT-60, SCREEN_WIDTH, 60);

    SDL_SetRenderDrawColor(win->pRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(win->pRenderer, &life);

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &mana);

}
