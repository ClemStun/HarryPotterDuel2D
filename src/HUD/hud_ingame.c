#include "../sdl/sdl.h"
#include "../player/player.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

extern
void update_hud_ingame(window * win, images_t * images, player_t * monPerso){

    SDL_Rect life;
    life.x = 10;
    life.y = SCREEN_HEIGHT - 40;
    life.w = monPerso->pt_life*2;
    life.h = 20;

    SDL_Rect mana;
    mana.x = SCREEN_WIDTH - 210;
    mana.y = SCREEN_HEIGHT - 40;
    mana.w = monPerso->pt_mana*2;
    mana.h = 20;

    DrawImage(win->pRenderer, images, "hud_tmp.png", 0, 0, 1200, 60, 0, SCREEN_HEIGHT-60, SCREEN_WIDTH, 60);

    SDL_SetRenderDrawColor(win->pRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(win->pRenderer, &life);

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &mana);

}
