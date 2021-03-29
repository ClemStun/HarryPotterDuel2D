/**
 * \file menus.c
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

/**
 * \fn static int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY)
 * \brief Fonction de détection de zone de la souris.
 *
 * \param x Position en X en haut à gauche de la zone à tester.
 * \param y Position en Y en haut à gauche de la zone à tester.
 * \param w Largeur de la zone.
 * \param h Hauteur de la zone.
 * \param mouseX Position en X de la souris.
 * \param mouseY Position en Y de la souris.
 *
 * \return 1 si souris dans la zone, 0 sinon.
 */
static
int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY){
    if((mouseX >= x && mouseY >= y) && (mouseX <= x + w && mouseY <= y + h)){
        return 1;
    }
    return 0;
}

/**
 * \fn extern t_etat game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort)
 * \brief Fonction état du jeu en mode jeu principal.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param mannequin Test
 * \param sort Pointeur de pointeur sur une structure sort_s.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort){
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    SDL_RenderClear(win->pRenderer);

    // Lecture des évènements
    while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					return QUIT;
				break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        SDL_GetMouseState(&(monPerso->pos_x_click), &(monPerso->pos_y_click));
                        monPerso->pos_x_click -= 50;
                        monPerso->pos_y_click -= 50;
                    }
                break;
                case SDL_KEYDOWN:
                    if(keyboard_state_array[SDL_SCANCODE_UP] && *sort == NULL)
                        *sort = monPerso->castSpell(monPerso);
                    else if(keyboard_state_array[SDL_SCANCODE_1])
                        monPerso->castSpell = monPerso->createSort[0];
                    else if(keyboard_state_array[SDL_SCANCODE_2])
                        monPerso->castSpell = monPerso->createSort[1];
                break;
            }
        }
    //Actualisation du jeu
    updatePosition(win, monPerso, images, monPerso->pos_x_click, monPerso->pos_y_click, 0.2);
    //updatePosition(win, mannequin, images, 50, 50, 0.2);
    update_hud_ingame(win, images, monPerso);

    if(*sort != NULL){
        (*sort)->deplacement((*sort), (*sort)->destX, (*sort)->destY);
        (*sort)->display((*sort), win, images);
        (*sort)->collision_test(sort, (*sort)->destX, (*sort)->destY, mannequin);
    }

    SDL_SetRenderDrawColor(win->pRenderer, 150, 150, 150, 0 );
    return GAME;
}

/**
 * \fn extern t_etat home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font)
 * \brief Fonction état du jeu en mode menu principal.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param font Police du menu.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font){
    static int mouseX, mouseY, click = 0;

    SDL_RenderClear(win->pRenderer);

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return QUIT;
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
        createButton(win, text, SCREEN_WIDTH-250, 50, 200, 100, "jouer", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return GAME;
    }
    createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "Quitter", font, 'b');
    if(zone_detect(SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "quitter", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return QUIT;
    }
    if(!(zone_detect(SCREEN_WIDTH-250, 200, 200, 100, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH-250, 200, 200, 100, "Train", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 200, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, 200, 200, 100, "train", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 200, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return TRAINING;
    }

    if(!(zone_detect(100, 250, 300, 300, mouseX, mouseY))){
        DrawImage(win->pRenderer, images, monPerso->sprite, 7*32, 0, 32, 32, 100, 250, 300, 300);
    }
    else if(zone_detect(100, 250, 300, 300, mouseX, mouseY)){
        DrawImage(win->pRenderer, images, monPerso->sprite, 7*32, 4*32, 32, 32, 100, 250, 300, 300);
    }

    createText(win->pRenderer, text, 250, 100, 250, 125, monPerso->name, font, 'w');

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0 );
    return HOME;
}

/**
 * \fn extern t_etat training_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort)
 * \brief Fonction état du jeu en mode entrainement.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param mannequin Test
 * \param sort Pointeur de pointeur sur une structure sort_s.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat training_state(window *win, images_t * images, text_t * text, player_t * monPerso, player_t * mannequin, sort_t ** sort, TTF_Font *font){
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    SDL_RenderClear(win->pRenderer);

    // Lecture des évènements
    while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					return QUIT;
				break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        SDL_GetMouseState(&(monPerso->pos_x_click), &(monPerso->pos_y_click));
                        monPerso->pos_x_click -= 50;
                        monPerso->pos_y_click -= 50;
                    }
                break;
                case SDL_KEYDOWN:
                    if(keyboard_state_array[SDL_SCANCODE_UP] && *sort == NULL)
                        *sort = monPerso->castSpell(monPerso);
                    else if(keyboard_state_array[SDL_SCANCODE_1]){
                        monPerso->numSort = 0;
                        monPerso->castSpell = monPerso->createSort[monPerso->numSort];
                    }else if(keyboard_state_array[SDL_SCANCODE_2]){
                        monPerso->numSort = 1;
                        monPerso->castSpell = monPerso->createSort[monPerso->numSort];
                    }
                break;
            }
        }

    DrawImage(win->pRenderer, images, searchTexture(images, "background_training.png"), 80, 30, 1000, 540, 0, 0, 1200, 600);

    //Actualisation du jeu
    updatePosition(win, monPerso, images, monPerso->pos_x_click, monPerso->pos_y_click, 0.2);
    update_hud_ingame(win, images, monPerso);

    rand_click_bot(mannequin);
    updatePosition(win, mannequin, images, mannequin->pos_x_click, mannequin->pos_y_click, 0.1);
    update_hud_ingame_ennemie(win, images, text, mannequin, font);

    if(*sort != NULL){
        (*sort)->deplacement((*sort), (*sort)->destX, (*sort)->destY);
        (*sort)->display((*sort), win, images);
        (*sort)->collision_test(sort, (*sort)->destX, (*sort)->destY, mannequin);
    }

    SDL_SetRenderDrawColor(win->pRenderer, 150, 150, 150, 0 );
    return TRAINING;
}

extern
t_etat waiting_state(window *win, text_t * text, TTF_Font *font){
    static int i = 0, compteur = 1;

    SDL_RenderClear(win->pRenderer);

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return QUIT;
			break;
        }
    }

    if(i++ > 1000){
        compteur++;
        i = 0;
    }
    if(compteur > 3){
        compteur = 1;
    }

    if(compteur == 1){
        createText(win->pRenderer, text, 600, 300, 600, 90, "En attente d'un joueur adverse.", font, 'w');
    }
    if(compteur == 2){
        createText(win->pRenderer, text, 600, 300, 615, 90, "En attente d'un joueur adverse..", font, 'w');
    }
    if(compteur == 3){
        createText(win->pRenderer, text, 600, 300, 630, 90, "En attente d'un joueur adverse...", font, 'w');
    }

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0 );
    return WAITING;
}
