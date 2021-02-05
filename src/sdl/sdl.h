_y#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct window_s{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderer;
} window;

window * Initialize_sdl();