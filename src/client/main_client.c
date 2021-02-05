#include "../sdl/sdl.h"

int main(int argc, char **argv){
    window *win;
    int should_quit = 0;
    SDL_Event event;
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

    win = Initialize_sdl();
    

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
            }
        }
        if(keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN]) && rect1.y-VITESSE > 0){
            rect1.y -= VITESSE;
        }
        else if(!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN] && rect1.y+VITESSE < SCREEN_HEIGHT-RECT_HEIGHT){
            rect1.y += VITESSE;
        }
        if(keyboard_state_array[SDL_SCANCODE_LEFT] && !(keyboard_state_array[SDL_SCANCODE_RIGHT]) && rect1.x-VITESSE6 > 0){
            rect1.x -= VITESSE;
        }
        else if(!keyboard_state_array[SDL_SCANCODE_LEFT] && keyboard_state_array[SDL_SCANCODE_RIGHT] && rect1.x+VITESSE < SCREEN_WIDTH-RECT_WIDTH){
            rect1.x += VITESSE;
        }

        // Actualisation du rendu
        SDL_RenderPresent(win->pRenderer);
    }

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