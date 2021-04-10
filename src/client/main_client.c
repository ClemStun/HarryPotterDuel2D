/**
 * \file main_client.c
 * \brief Fonction principale du jeu.
 * \author COUTANT Hugo & COMTE Clement & COLLET Matthieu
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"
#include "../../lib/expelliarmus.h"
#include "../../lib/petrificus.h"
#include "../../lib/incendio.h"
#include "../../lib/protego.h"
#include <math.h>
#include <pthread.h>



int main(int argc, char **argv){
    window *win;
    images_t images;
    text_t * text;
    t_etat etat_de_jeu = TEST_M;
    int socketClient;
    char offline;
    char data_storage[] = "./svg/";

    printf("Voulez vous jouer hors ligne (y or n) ?\n");
    scanf("%c", &offline);

    socket_t j1;

    win = Initialize_sdl();
    LoadImages(win->pRenderer, &images);
    text = init_struct_text();

    // fonts
    TTF_Font *font = TTF_OpenFont("./assets/fonts/big_noodle_titling.ttf", 200);

    // Destiné à dégager
    cd_t setSort[NB_SORT];
    for(int i = 0; i < NB_SORT; i++){
        setSort[i].timer = SDL_GetTicks();
        setSort[i].createSort = NULL;
        setSort[i].sort = NULL;
    }
    setSort[0].createSort = createExpelliarmus;
    setSort[1].createSort = createPetrificus;
    setSort[2].createSort = createIncendio;
    setSort[3].createSort = createProtego;

    player_t * monPerso;
    monPerso = accueil_connexion(&images, setSort, data_storage);
    if(monPerso->house == 'n'){
        etat_de_jeu = TEST_M;
    }
    else{
        etat_de_jeu = HOME;
    }

    if(offline == 'n'){
        strcpy(j1.pseudo, monPerso->name);
        socketClient = init_connexion(j1);
    }

    //Mannequin

    player_t * mannequin;
    mannequin = createPlayer(3, "Pouette", 0, searchTexture(&images, "Mannequin.png"), setSort, 900, 250);

    //Joueur 2

    player_t * joueur2;
    joueur2 = createPlayer(2, "Ennemi", 0, searchTexture(&images, "Mannequin.png"), setSort, 900, 250);

    // Boucle de jeu
    while(etat_de_jeu != QUIT){

        // Etat
        switch(etat_de_jeu){
            case HOME:
                etat_de_jeu = home_state(win, &images, text, monPerso, font);
            break;
            case GAME:
                etat_de_jeu = game_state(win, &images, monPerso, joueur2, socketClient, &j1);
            break;
            case TRAINING:
                etat_de_jeu = training_state(win, &images, text, monPerso, mannequin, font);
            break;
            case WAITING:
                etat_de_jeu = waiting_state(win, text, font, socketClient, &j1);
            break;
            case TEST_M:
                etat_de_jeu = test_m_state(win, text, monPerso, font);
            break;
        }

        // Actualisation du rendu
        SDL_RenderPresent(win->pRenderer);
    }
    FreeImages(&images);
    freeText(&text);
    accueil_deconnexion(monPerso, data_storage);
    freePlayer(mannequin);
    freePlayer(joueur2);

    TTF_CloseFont(font);

    // Libération mémoire du rendu
    SDL_DestroyRenderer(win->pRenderer);

    if(win->pWindow){
        // Libération mémoire de la fenêtre
        SDL_DestroyWindow(win->pWindow);
    }
    else{
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        exit(0);
    }
    free(win);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 1;
}
