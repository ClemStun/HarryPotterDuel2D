#include "../menus/menus.h"
#include "../player/spell/expelliarmus.h"
#include "../player/spell/petrificus.h"
#include <math.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

int main(int argc, char **argv){
    window *win;
    images_t images;
    text_t * text;
    t_etat etat_de_jeu = HOME;
    int should_quit = 1;
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    sort_t * sort = NULL;

    win = Initialize_sdl();
    LoadImages(win->pRenderer, &images);
    text = init_struct_text();

    // fonts
    TTF_Font *font = TTF_OpenFont("../../assets/fonts/big_noodle_titling.ttf", 80);

    // Destiné à dégager
    player_t * monPerso;
    monPerso = createPlayer(1, "Heaven", NULL);
    monPerso->castSpell = createExpelliarmus;

    //Mannequin
    player_t * mannequin;
    mannequin = createPlayer(2, "Mannequin", NULL);

    // Boucle de jeu
    while(should_quit){
        
        // Clear du rendu
        SDL_RenderClear(win->pRenderer);
        SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 255 );

        // Etat
        switch(etat_de_jeu){
            case HOME:
                should_quit = home_state(win, &images, text, monPerso, font);
            break;
            case GAME:
                should_quit = game_state(win, &images, monPerso, mannequin, &sort, keyboard_state_array);
            break;
        }
        
        if(should_quit == 2){
            etat_de_jeu = GAME;
        }

        // Actualisation du rendu
        SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 255);
        SDL_RenderPresent(win->pRenderer);
    }
    FreeImages(&images);
    freeText(&text);
    freePlayer(monPerso);

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
