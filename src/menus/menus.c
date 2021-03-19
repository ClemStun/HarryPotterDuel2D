#include "menus.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

SDL_Event event;

extern
void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton){

    SDL_Rect button;
    button.x = posX;
    button.y = posY;
    button.w = rectW;
    button.h = rectH;

    SDL_SetRenderDrawColor(win->pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &button);

    createText(win->pRenderer, text, posX + rectW/2, posY + rectH/2, rectW-100, rectH-50, texte, fontButton, 'b');
}

extern
int game_state(window *win, images_t * images, player_t * monPerso, sort_t * sort, const Uint8 *keyboard_state_array){
    // Lecture des évènements
    while(SDL_PollEvent(&event)){
			switch (event.type){
				case SDL_QUIT:
					return -1;
				break;
                case SDL_MOUSEBUTTONDOWN:
                    if(SDL_BUTTON(SDL_BUTTON_LEFT)){
                        SDL_GetMouseState(&monPerso->pos_x_click, &monPerso->pos_y_click);
                        monPerso->pos_x_click -= 50;
                        monPerso->pos_y_click -= 50;
                    }
                break;
                case SDL_KEYDOWN:
                    if(keyboard_state_array[SDL_SCANCODE_UP] && sort == NULL){
                        sort = monPerso->castSpell(monPerso);
                    }
                break;
            }
        }

    //Actualisation du jeu
    updatePosition(win, monPerso, images, monPerso->pos_x_click, monPerso->pos_y_click);
    update_hud_ingame(win, images, monPerso);

    if(sort != NULL){
        sort->deplacement(sort, sort->destX, sort->destY);
        sort->display(sort, win);
        sort->collision_test(&sort, sort->destX, sort->destY, monPerso);
    }
}

extern
int home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font){

    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return -1;
			break;
        }
    }

    createButton(win, text, SCREEN_WIDTH-250, 50, 200, 100, "Jouer", font);
    createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "Quitter", font);
    DrawImage(win->pRenderer, images, "hp.png", 7*32, 0, 32, 32, 100, 250, 300, 300);
    createText(win->pRenderer, text, 250, 100, 250, 125, "Heaven", font, 'w');

}
