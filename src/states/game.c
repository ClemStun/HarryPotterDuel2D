/**
 * \file game.c
 * \brief Déroulement du jeu dans l'état GAME
 * \author COUTANT Hugo & COMTE Clément
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"

player_t * joueur2;

void *function(void *arg){
    socket_t j2;
    int socket = *(int*)arg;

        while(1){
            recv(socket, &j2, sizeof j2, 0);
            joueur2->pos_x_click = SCREEN_WIDTH-100-j2.x_click;
            joueur2->pos_y_click = SCREEN_HEIGHT-100-j2.y_click;
        }

        free(arg);
        pthread_exit(NULL);
}

/**
 * \fn extern t_etat game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, int socketClient, socket_t *j1)
 * \brief Fonction état du jeu en mode jeu principal.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param mannequin Pointeur sur une structure player_t représentant les infos d'un personnage ennemi.
 * \param socketClient Numéro du socket de client actuel.
 * \param j1 Pointeur sur un socket_s du joueur 1.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat game_state(window *win, images_t * images, player_t * monPerso, player_t * j2, int socketClient, socket_t *j1){

    joueur2 = j2;    

    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    pthread_t thread1;
    int *arg1 = malloc(sizeof(int));
    *arg1 = socketClient;
    pthread_create(&thread1, NULL, function, arg1);


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
                        socket_t update;
                        strcpy(update.pseudo, j1->pseudo);
                        update.x_click = monPerso->pos_x_click;
                        update.y_click = monPerso->pos_y_click;
                        send(socketClient, &update, sizeof(update), 0);
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
    //printf("%i %i    %i %i\n", mannequin->pos_x_click, mannequin->pos_y_click, mannequin->pos_x, mannequin->pos_y);
    updatePosition(win, joueur2, images, joueur2->pos_x_click, joueur2->pos_y_click, 0.2);
    update_hud_ingame(win, images, joueur2);

    /*if(*sort != NULL){
        (*sort)->deplacement((*sort), (*sort)->destX, (*sort)->destY);
        (*sort)->display((*sort), win, images);
        (*sort)->collision_test(sort, (*sort)->destX, (*sort)->destY, mannequin);
    }*/

    SDL_SetRenderDrawColor(win->pRenderer, 150, 150, 150, SDL_ALPHA_OPAQUE );
    return GAME;
}
