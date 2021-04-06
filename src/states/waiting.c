/**
 * \file waiting.c
 * \brief Déroulement du jeu dans l'état WAITING
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"

/**
 * \fn extern t_etat waiting_state(window *win, text_t * text, TTF_Font *font, int socketClient, socket_t *j1, socket_t *adv)
 * \brief Fonction état du jeu en mode attente.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param socketClient Numéro du socket de client actuel.
 * \param j1 Pointeur sur un socket_s du joueur 1.
 * \param adv Pointeur sur un socket_s de l'adversaire.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat waiting_state(window *win, text_t * text, TTF_Font *font, int socketClient, socket_t *j1){
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

    send(socketClient, j1, sizeof(j1), 0);
    socket_t adv;
    recv(socketClient, &adv, sizeof adv, 0);
    printf("Votre adversaire est %s\n", adv.pseudo);

    return GAME;
}
