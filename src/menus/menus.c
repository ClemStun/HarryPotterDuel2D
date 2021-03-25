/**
 * \file move.c
 * \brief Fonctions sur les différents états de jeu.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"
#include "../../lib/expelliarmus.h"
#include "../../lib/petrificus.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

SDL_Event event;

/**
 * \fn extern void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color)
 * \brief Fonction de création d'un bouton sur la fenêtre en fonction d'une position donnée, d'une dimension, d'un texte, d'une police et d'une couleur.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param posX Position en X du bouton.
 * \param posY Position en Y du bouton.
 * \param rectW Largeur du bouton.
 * \param rectH Hauteur du bouton.
 * \param texte Chaine de caractère correspondant au texte du bouton.
 * \param fontButton Police de texte du bouton.
 * \param color Couleur du texte du bouton.
 *
 */
extern
void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color){

    SDL_Rect button;
    button.x = posX;
    button.y = posY;
    button.w = rectW;
    button.h = rectH;

    SDL_SetRenderDrawColor(win->pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &button);

    createText(win->pRenderer, text, posX + rectW/2, posY + rectH/2, rectW-100, rectH-50, texte, fontButton, color);
}

int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY){
    if((mouseX >= x && mouseY >= y) && (mouseX <= x + w && mouseY <= y + h)){
        return 1;
    }
    return 0;
}

/**
 * \fn extern int game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort, const Uint8 *keyboard_state_array)
 * \brief Fonction état du jeu en mode jeu principal.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param mannequin Test
 * \param sort Pointeur de pointeur sur une structure sort_s.
 * \param keyboard_state_array État des actions claviers.
 *
 */
extern
int game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort, const Uint8 *keyboard_state_array){
    // Lecture des évènements
    while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					return 0;
				break;
                case SDL_MOUSEBUTTONDOWN:
                    if(SDL_BUTTON(SDL_BUTTON_LEFT)){
                        SDL_GetMouseState(&(monPerso->pos_x_click), &(monPerso->pos_y_click));
                        monPerso->pos_x_click -= 50;
                        monPerso->pos_y_click -= 50;
                    }
                break;
                case SDL_KEYDOWN:
                    if(keyboard_state_array[SDL_SCANCODE_UP] && *sort == NULL)
                        *sort = monPerso->castSpell(monPerso);
                    else if(keyboard_state_array[SDL_SCANCODE_1])
                        monPerso->castSpell = createExpelliarmus;
                    else if(keyboard_state_array[SDL_SCANCODE_2])
                        monPerso->castSpell = createPetrificus;
                break;
            }
        }

    //Actualisation du jeu
    updatePosition(win, monPerso, images, monPerso->pos_x_click, monPerso->pos_y_click, 0.2);
    //updatePosition(win, mannequin, images, 50, 50, 0.2);
    update_hud_ingame(win, images, monPerso);

    if(*sort != NULL){
        (*sort)->deplacement((*sort), (*sort)->destX, (*sort)->destY);
        (*sort)->display((*sort), win);
        (*sort)->collision_test(sort, (*sort)->destX, (*sort)->destY, mannequin);
    }

    return 2;
}

/**
 * \fn extern int home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font)
 * \brief Fonction état du jeu en mode menu principal.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param font Police du menu.
 *
 */
extern
int home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font){
    static int mouseX, mouseY, click = 0;

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return 0;
			break;
            case SDL_MOUSEBUTTONDOWN:
                if(SDL_BUTTON(SDL_BUTTON_LEFT)){
                    click = 1;
                }
            break;
        }
    }
    SDL_GetMouseState(&mouseX, &mouseY);

    if(!(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH-250, 50, 200, 100, "Jouer", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, 50, 200, 100, "Jouer", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return 2;
    }
    createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "Quitter", font, 'b');
    if(zone_detect(SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "Quitter", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return 0;
    }
    DrawImage(win->pRenderer, images, "hp.png", 7*32, 0, 32, 32, 100, 250, 300, 300);
    createText(win->pRenderer, text, 250, 100, 250, 125, "Heaven", font, 'w');

    return 1;
}
