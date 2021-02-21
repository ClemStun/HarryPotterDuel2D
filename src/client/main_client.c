#include "../sdl/sdl.h"
#include "../player/move.h"
#include "../player/player.h"
#include "../HUD/hud_ingame.h"
#include <math.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

int main(int argc, char **argv){
    window *win;
    images_t images;
    int should_quit = 0;
    SDL_Event event;
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    win = Initialize_sdl();
    LoadImages(win->pRenderer, &images);


    // Destiné à dégager
    player_t * monPerso;
    monPerso = createPlayer(1, "Heaven", NULL);

    int deplX = 100, deplY = 100;

    // Boucle de jeu
    while(!should_quit){
        // Clear du rendu
        SDL_RenderClear(win->pRenderer);
        SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 255 );
        // Détection d'évènements
        while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					should_quit = 1;
				break;
                case SDL_MOUSEBUTTONDOWN:
                    if(SDL_BUTTON(SDL_BUTTON_LEFT)){
                        SDL_GetMouseState(&deplX, &deplY);
                        deplX -= 50;
                        deplY -= 50;
                    }
                break;
            }
        }

        updatePosition(win, &images, deplX, deplY);
        update_hud_ingame(win, &images, monPerso);


        // Actualisation du rendu
        SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 255);
        SDL_RenderPresent(win->pRenderer);
    }
    FreeImages(&images);

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
    SDL_Quit();
    return 1;
}
