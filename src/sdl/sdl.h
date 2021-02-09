#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct window_s{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderer;
} window;

typedef struct images_s{
    int nb_images;
    char ** nomsImages;
    SDL_Texture ** l_textImages;
} images_t;

window * Initialize_sdl();
extern void LoadImages(SDL_Renderer * pRenderer, images_t * images);
extern void DrawImage(SDL_Renderer * pRenderer, images_t * images, char * nom, int x, int y, int w, int h);
extern void FreeImages(images_t * images);
