/**
 * \file hud_ingame.c
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
 * \fn extern void update_hud_ingame(window * win, images_t * images, player_t * monPerso)
 * \brief Mise à jour de l'HUD du jeu (barre de vie et de mana, barre de sorts, etc).
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

    DrawImage(win->pRenderer, images, searchTexture(images, "hud_tmp.png"), 0, 0, 1200, 60, 0, SCREEN_HEIGHT-60, SCREEN_WIDTH, 60);
    DrawImage(win->pRenderer, images, searchTexture(images, "expelliarmus.png"), 0, 0, 1200, 60, 445, SCREEN_HEIGHT-69, 64, 64);
    DrawImage(win->pRenderer, images, searchTexture(images, "petrificus.png"), 0, 0, 1200, 60, 510, SCREEN_HEIGHT-56, 62, 52);

    switch(monPerso->numSort){
        case 0:
            DrawImage(win->pRenderer, images, searchTexture(images, "selection.png"), 0, 0, 1200, 60, 438, SCREEN_HEIGHT-60, 72, 60);
        break;
        case 1:
            DrawImage(win->pRenderer, images, searchTexture(images, "selection.png"), 0, 0, 1200, 60, 506, SCREEN_HEIGHT-60, 70, 60);
        break;
        case 2:
            DrawImage(win->pRenderer, images, searchTexture(images, "selection.png"), 0, 0, 1200, 60, 572, SCREEN_HEIGHT-60, 70, 60);
        break;
        case 3:
            DrawImage(win->pRenderer, images, searchTexture(images, "selection.png"), 0, 0, 1200, 60, 638, SCREEN_HEIGHT-60, 70, 60);
        break;
        case 4:
            DrawImage(win->pRenderer, images, searchTexture(images, "selection.png"), 0, 0, 1200, 60, 704, SCREEN_HEIGHT-60, 70, 60);
        break;
    }

    SDL_SetRenderDrawColor(win->pRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(win->pRenderer, &life);

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &mana);

}
