/**
 * \file hud_ingame.c
 * \brief Fonctions de generation d'interface.
 * \author COUTANT Hugo
 * \version 1
 * \date 17 avril 2021
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

    //parametres rectangle de vie
    SDL_Rect life;
    life.x = 10;
    life.y = SCREEN_HEIGHT - 40;
    life.w = monPerso->pt_life*2;
    life.h = 20;

    //parametres contour du rectangle de vie
    SDL_Rect bd_life;
    bd_life.x = 8;
    bd_life.y = SCREEN_HEIGHT - 42;
    bd_life.w = (monPerso->pt_life*2)+4;
    bd_life.h = 24;

    //parametres rectangle de mana
    SDL_Rect mana;
    mana.x = SCREEN_WIDTH - 210;
    mana.y = SCREEN_HEIGHT - 40;
    mana.w = monPerso->pt_mana*2;
    mana.h = 20;

    //parametres contour rectangle de mana
    SDL_Rect bd_mana;
    bd_mana.x = SCREEN_WIDTH - 212;
    bd_mana.y = SCREEN_HEIGHT - 42;
    bd_mana.w = (monPerso->pt_mana*2)+4;
    bd_mana.h = 24;

    //Affichage de la barre des sorts et de ses sorts
    DrawImage(win->pRenderer, images, searchTexture(images, "hud_tmp.png"), 0, 0, 1200, 60, 0, SCREEN_HEIGHT-60, SCREEN_WIDTH, 60);
    DrawImage(win->pRenderer, images, searchTexture(images, "expelliarmus.png"), 0, 0, 1200, 60, 445, SCREEN_HEIGHT-69, 64, 64);
    DrawImage(win->pRenderer, images, searchTexture(images, "petrificus.png"), 0, 0, 1200, 60, 510, SCREEN_HEIGHT-56, 62, 52);

    //Affichage du carré de selection rouge autour du sort selectionné en fonction du numSort
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

    //mise dans le rendu des textures des rectangles et choix de leur couleur
	SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(win->pRenderer, &bd_life);

    SDL_SetRenderDrawColor(win->pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(win->pRenderer, &life);

	SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(win->pRenderer, &bd_mana);

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(win->pRenderer, &mana);

}

/**
 * \fn extern void update_hud_ingame_ennemie(window * win, images_t * images, text_t * text, player_t * ennemie, TTF_Font *font)
 * \brief Mise à jour de l'HUD du jeu pour les informations ennemies (barre de vie, pseudo, etc).
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param ennemie Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param font Pointeur sur une police de texte.
 *
 */
extern
void update_hud_ingame_ennemie(window * win, images_t * images, text_t * text, player_t * ennemie, TTF_Font *font){

    //parametres rectangle de vie
    SDL_Rect life;
    life.x = SCREEN_WIDTH - 120;
    life.y = 28;
    life.w = ennemie->pt_life;
    life.h = 14;

    //parametres contour rectangle de vie
    SDL_Rect bd_life;
    bd_life.x = SCREEN_WIDTH - 122;
    bd_life.y = 26;
    bd_life.w = ennemie->pt_life + 4;
    bd_life.h = 18;

    //affichage de l'image coeur devant la barre de vie ennemie ainsi que le pseudo en dessous de celle-ci
    DrawImage(win->pRenderer, images, searchTexture(images, "heart.png"), 0, 0, 46, 41, SCREEN_WIDTH - 150, 25, 23, 20);
    createText(win->pRenderer, text, SCREEN_WIDTH - 75, 60, 80, 20, ennemie->name, font, "r");

    //mise dans le rendu des textures des rectangles et choix de leur couleur
	SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(win->pRenderer, &bd_life);

    SDL_SetRenderDrawColor(win->pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(win->pRenderer, &life);
}
