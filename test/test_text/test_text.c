#include "../../lib/sdl.h"
#include <math.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

int main(int argc, char **argv){
    window *win;
    text_t * text;
    int should_quit = 0;
    SDL_Event event;

    win = Initialize_sdl();
    text = init_struct_text();

    TTF_Font *font = TTF_OpenFont("../../assets/fonts/big_noodle_titling.ttf", 80);

    while(!should_quit){
        SDL_RenderClear(win->pRenderer);
        SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0);

        while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					should_quit = 1;
				break;
            }
        }

        createText(win->pRenderer, text, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 100, 100, "Test", font, 'r');

        // Actualisation du rendu
        SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0);
        SDL_RenderPresent(win->pRenderer);
    }

    TTF_CloseFont(font);
    freeText(&text);

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



