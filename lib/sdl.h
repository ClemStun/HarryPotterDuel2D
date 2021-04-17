/**
 * \file sdl.h
 * \brief Header du fichier sdl.c.
 * \author COUTANT Hugo
 * \version 1
 * \date 17 avril 2021
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * \struct window_s
 * \brief Information fenêtre SDL.
 *
 * window_s est une structure regroupant le pointeur sur un SDL_Window et son rendu SDL_Renderer.
 */
typedef struct window_s{
    SDL_Window* pWindow;
    SDL_Renderer *pRenderer;
} window;

/**
 * \struct images_s
 * \brief Bibliothèque de textures d'images avec leur nom et le nombre d'images stockées.
 *
 */
typedef struct images_s{
    int nb_images;
    char ** nomsImages;
    SDL_Texture ** l_textImages;
} images_t;

/**
 * \struct text_s
 * \brief Bibliothèque de textures de textes avec leur contenu et le nombre de textes stockés.
 *
 */
typedef struct text_s{
    int nb_text;
    char ** text;
    SDL_Texture ** l_textText;
} text_t;

extern window * Initialize_sdl();
extern void LoadImages(SDL_Renderer * pRenderer, images_t * images);
extern SDL_Texture * searchTexture(images_t * images, char * nom);
extern void DrawImage(SDL_Renderer * pRenderer, images_t * images, SDL_Texture * texture, int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW, int destH);
extern void FreeImages(images_t * images);
extern text_t * init_struct_text();
extern void createText(SDL_Renderer *pRenderer, text_t * text, int x, int y, int text_width, int text_height, const char *texte, TTF_Font *font, const char color);
extern void freeText(text_t ** text);
