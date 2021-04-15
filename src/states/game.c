/**
 * \file game.c
 * \brief Déroulement du jeu dans l'état GAME
 * \author COUTANT Hugo & COMTE Clément & COLLET Matthieu
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"

player_t * joueur2;

void *function(void *arg){
    socket_t j2;
    int socket = *(int*)arg;
        int x, y;
        while(1){
            recv(socket, &j2, sizeof j2, 0);
            x = SCREEN_WIDTH-100-j2.x_click;
            y = SCREEN_HEIGHT-100-j2.y_click;
            if(j2.x_click != 0 && j2.y_click != 0){
                if(j2.sort != -1){
                    joueur2->numSort = j2.sort;
                    joueur2->createSort[joueur2->numSort].sort = joueur2->createSort[joueur2->numSort].createSort(joueur2, x, y);
                    joueur2->createSort[joueur2->numSort].timer = SDL_GetTicks();
                }else{
                    joueur2->pos_x_click = x;
                    joueur2->pos_y_click = y;
                }
            }
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

    socket_t update;

    SDL_RenderClear(win->pRenderer);

    // Lecture des évènements
    while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					return QUIT;
				break;
                case SDL_MOUSEBUTTONDOWN:
                    //Si le click de déplacement est effectué, on change tout ce qui doit etre changé (position, envoi de paquet, etc)
                    if(event.button.button == SDL_BUTTON_LEFT){
                        SDL_GetMouseState(&(monPerso->pos_x_click), &(monPerso->pos_y_click));
                        monPerso->pos_x_click -= 50;
                        monPerso->pos_y_click -= 50;
                        strcpy(update.pseudo, j1->pseudo);
                        update.x_click = monPerso->pos_x_click;
                        update.y_click = monPerso->pos_y_click;
                        update.sort = -1;
                        send(socketClient, &update, sizeof(update), 0);
                    }
                    //Si le click de sort est effectué, on lance le sort selectionné et on envoi le paquet
                    else if(event.button.button == SDL_BUTTON_RIGHT && monPerso->createSort[monPerso->numSort].sort == NULL && (SDL_GetTicks() - monPerso->createSort[monPerso->numSort].timer >= 3000)){
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        update.x_click = x;
                        update.y_click = y;
                        update.sort = monPerso->numSort;
                        monPerso->createSort[monPerso->numSort].sort = monPerso->createSort[monPerso->numSort].createSort(monPerso, x, y);
                        monPerso->createSort[monPerso->numSort].timer = SDL_GetTicks();
                        send(socketClient, &update, sizeof(update), 0);
                    }
                break;
                case SDL_KEYDOWN:
                    //Selection des sort en fonction de la touche appuyée
                    if(keyboard_state_array[SDL_SCANCODE_1]){
                        monPerso->numSort = 0;
                    }else if(keyboard_state_array[SDL_SCANCODE_2]){
                        monPerso->numSort = 1;
                    }else if(keyboard_state_array[SDL_SCANCODE_3]){
                        monPerso->numSort = 2;
                    }else if(keyboard_state_array[SDL_SCANCODE_4]){
                        monPerso->numSort = 3;
                    }
                break;
            }
        }
    //Actualisation du jeu
    updatePosition(win, monPerso, images, monPerso->pos_x_click, monPerso->pos_y_click, 0.2);
    update_hud_ingame(win, images, monPerso);
    updatePosition(win, joueur2, images, joueur2->pos_x_click, joueur2->pos_y_click, 0.2);
    //rajouter hud ennemi si possible

    //appel des méthodes des sorts pour le joueurs local
    for(int i = 0; i < NB_SORT; i++){
        if(monPerso->createSort[i].sort != NULL){
            if(monPerso->createSort[i].sort->deplacement != NULL)
                monPerso->createSort[i].sort->deplacement(monPerso->createSort[i].sort, monPerso->createSort[i].sort->destX, monPerso->createSort[i].sort->destY);
            monPerso->createSort[i].sort->display(monPerso->createSort[i].sort, win, images);
            if(monPerso->is_protego == 0)
                monPerso->createSort[i].sort->collision_test(&(monPerso->createSort[i].sort), monPerso->createSort[i].sort->destX, monPerso->createSort[i].sort->destY, joueur2);
            else
                monPerso->createSort[i].sort->collision_test(&(monPerso->createSort[i].sort), 0, 0, monPerso);
        }
    }

    //appel des méthodes des sorts pour le joueurs adverse
    for(int i = 0; i < NB_SORT; i++){
        if(joueur2->createSort[i].sort != NULL){
            if(joueur2->createSort[i].sort->deplacement != NULL)
                joueur2->createSort[i].sort->deplacement(joueur2->createSort[i].sort, joueur2->createSort[i].sort->destX, joueur2->createSort[i].sort->destY);
            joueur2->createSort[i].sort->display(joueur2->createSort[i].sort, win, images);
            if(joueur2->is_protego == 0)
                joueur2->createSort[i].sort->collision_test(&(joueur2->createSort[i].sort), joueur2->createSort[i].sort->destX, joueur2->createSort[i].sort->destY, monPerso);
            else
                joueur2->createSort[i].sort->collision_test(&(joueur2->createSort[i].sort), 0, 0, joueur2);
        }
    }

    //Couleur de fond
    SDL_SetRenderDrawColor(win->pRenderer, 150, 150, 150, SDL_ALPHA_OPAQUE );
    return GAME;
}
