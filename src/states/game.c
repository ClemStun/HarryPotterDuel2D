#include "../../lib/menus.h"

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
t_etat game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin){
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
                    /*if(keyboard_state_array[SDL_SCANCODE_UP] && *sort == NULL)
                        *sort = monPerso->castSpell(monPerso);
                    else if(keyboard_state_array[SDL_SCANCODE_1])
                        monPerso->castSpell = monPerso->createSort[0];
                    else if(keyboard_state_array[SDL_SCANCODE_2])
                        monPerso->castSpell = monPerso->createSort[1];*/
                break;
            }
        }
    //Actualisation du jeu
    updatePosition(win, monPerso, images, monPerso->pos_x_click, monPerso->pos_y_click, 0.2);
    //updatePosition(win, mannequin, images, 50, 50, 0.2);
    update_hud_ingame(win, images, monPerso);

    /*if(*sort != NULL){
        (*sort)->deplacement((*sort), (*sort)->destX, (*sort)->destY);
        (*sort)->display((*sort), win, images);
        (*sort)->collision_test(sort, (*sort)->destX, (*sort)->destY, mannequin);
    }*/

    SDL_SetRenderDrawColor(win->pRenderer, 150, 150, 150, 0 );
    return GAME;
}