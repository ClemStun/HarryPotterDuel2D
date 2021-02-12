#include "../sdl/sdl.h"
#include "../player/move.h"
#include <math.h>

int main(int argc, char **argv){
    window *win;
    images_t images;
    int should_quit = 0;
    SDL_Event event;
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    win = Initialize_sdl();
    LoadImages(win->pRenderer, &images);

    int deplX = 100, deplY = 100;

    // Boucle de jeu
    while(!should_quit){
        // Clear du rendu
        SDL_RenderClear(win->pRenderer);
        // Détection d'évènements
        while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					should_quit = 1;
				break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    if(SDL_BUTTON(SDL_BUTTON_LEFT)){
                        SDL_GetMouseState(&deplX, &deplY);
                        deplX -= 50;
                        deplY -= 50;
                    }
                break;
            }
        }

        updatePosition(win, &images, deplX, deplY);

        // Actualisation du rendu
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
