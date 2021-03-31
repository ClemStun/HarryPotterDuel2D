/**
 * \file train.c
 * \brief Déroulement du jeu dans l'état TRAIN
 * \author COUTANT Hugo & COMTE Clément
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"


/**
 * \fn extern t_etat training_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort)
 * \brief Fonction état du jeu en mode entrainement.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param mannequin Test
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat training_state(window *win, images_t * images, text_t * text, player_t * monPerso, player_t * mannequin, TTF_Font *font){

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
                    }else if(event.button.button == SDL_BUTTON_RIGHT && monPerso->createSort[monPerso->numSort].sort == NULL && (SDL_GetTicks() - monPerso->createSort[monPerso->numSort].timer >= 3000)){
                        monPerso->createSort[monPerso->numSort].sort = monPerso->createSort[monPerso->numSort].createSort(monPerso);
                        monPerso->createSort[monPerso->numSort].timer = SDL_GetTicks();
                    }
                break;
                case SDL_KEYDOWN:
                    if(keyboard_state_array[SDL_SCANCODE_1]){
                        monPerso->numSort = 0;
                    }else if(keyboard_state_array[SDL_SCANCODE_2]){
                        monPerso->numSort = 1;
                    }else if(keyboard_state_array[SDL_SCANCODE_3]){
                        monPerso->numSort = 2;
                    }else if(keyboard_state_array[SDL_SCANCODE_R]){
                        monPerso->pt_mana = 100;
                    }else if(keyboard_state_array[SDL_SCANCODE_V]){
                        mannequin->pt_life = 100;
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

    for(int i = 0; i < NB_SORT; i++){
        if(monPerso->createSort[i].sort != NULL){
            if(monPerso->createSort[i].sort->deplacement != NULL)
                monPerso->createSort[i].sort->deplacement(monPerso->createSort[i].sort, monPerso->createSort[i].sort->destX, monPerso->createSort[i].sort->destY);
            monPerso->createSort[i].sort->display(monPerso->createSort[i].sort, win, images);
            monPerso->createSort[i].sort->collision_test(&(monPerso->createSort[i].sort), monPerso->createSort[i].sort->destX, monPerso->createSort[i].sort->destY, mannequin);
        }
    }
    SDL_SetRenderDrawColor(win->pRenderer, 150, 150, 150, SDL_ALPHA_OPAQUE );
    return TRAINING;
}
