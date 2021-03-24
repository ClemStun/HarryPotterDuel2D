/**
 * \file sdl.c
 * \brief Fonctions utilisant principalement la SDL2.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "sdl.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

/**
 * \fn extern window * Initialize_sdl()
 * \brief Fonction d'initialisation de notre fenêtre SDL dans une structure window.
 *
 * \return window* Pointeur sur une structure comportant des infos sur la fenêtre.
 */
extern
window * Initialize_sdl(){
    window *win;
    win = malloc(sizeof(window));

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 0;
    }

    // Initialisation format PNG
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "could not initialize sdl2_image: %s\n", IMG_GetError());
        return 0;
    }

    if(TTF_Init() == -1){
        printf("TTF_Init: %s\n", TTF_GetError());
        return 0;
    }

    //Création de la fenêtre et du rendu

    win->pWindow = SDL_CreateWindow("Jeu test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    win->pRenderer = SDL_CreateRenderer(win->pWindow,-1,SDL_RENDERER_ACCELERATED);

    if(!(win->pRenderer)){
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
        exit(0);
    }

    return win;
}

/**
 * \fn extern void LoadImages(SDL_Renderer * pRenderer, images_t * images)
 * \brief Fonction qui créer la texture d'images présentes dans un fichier, et les range dans une structure images_t.
 *
 * \param pRenderer Pointeur sur le rendu où vont se trouver les images.
 * \param images Pointeur sur une structure images_t où vont être rangées les textures des images.
 */
extern
void LoadImages(SDL_Renderer * pRenderer, images_t * images){
    printf("Chargement des images...\n");
    DIR *d;
    struct dirent *dir;
    images->nb_images = 0;

    d = opendir("../../assets/images");
    while((dir = readdir(d)) != NULL) images->nb_images++;
    closedir(d);

    images->nomsImages = (char**)malloc(sizeof(char*) * images->nb_images);
    images->l_textImages = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * images->nb_images);

    d = opendir("../../assets/images");
    for(int i = 0; (dir = readdir(d)) != NULL; i++){
        images->nomsImages[i] = (char*)malloc(sizeof(char) * strlen(dir->d_name)+1);
        strcpy(images->nomsImages[i], dir->d_name);
    }
    closedir(d);
    for(int i = 0; i < images->nb_images; i++){
        char nom[50] = "../../assets/images/";
        strcat(nom, images->nomsImages[i]);
        images->l_textImages[i] = IMG_LoadTexture(pRenderer, nom);
        printf("%s\n", nom);
    }
    printf("Images chargées: %d\n", images->nb_images);
}

/**
 * \fn extern void DrawImage(SDL_Renderer * pRenderer, images_t * images, char * nom, int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW, int destH)
 * \brief Fonction qui affiche une image demandée de la taille souhaitée, à l'endroit souhaité sur le rendu.
 *
 * \param pRenderer Pointeur sur le rendu où vont être affichées les images.
 * \param images Pointeur sur une structure image_t où sont rangées les textures des images.
 * \param nom Chaine de caractère étant le nom de l'image.
 * \param srcX Position en X du rectangle source de l'image.
 * \param srcY Position en Y du rectangle source de l'image.
 * \param srcW Largeur du rectangle source de l'image.
 * \param srcH Hauteur du rectangle source de l'image.
 * \param destX Position en X du rectangle cible sur le rendu.
 * \param destY Position en Y du rectangle cible sur le rendu.
 * \param destW Largeur du rectangle cible sur le rendu.
 * \param destH Hauteur du rectangle cible sur le rendu.
 */
extern
void DrawImage(SDL_Renderer * pRenderer, images_t * images, char * nom, int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW, int destH){
    SDL_Rect imgDestRect;
    imgDestRect.x = destX;
    imgDestRect.y = destY;
    imgDestRect.w = destW;
    imgDestRect.h = destH;

    SDL_Rect imgSrcRect;
    imgSrcRect.x = srcX;
    imgSrcRect.y = srcY;
    imgSrcRect.w = srcW;
    imgSrcRect.h = srcH;
  char nom2[50];
  sprintf(nom2, "%s", nom);
  if(!strstr(nom2, ".png")){
    strcat(nom2, ".png");
  }
    int i;
    //ici on recherche quel est l'indice de l'image qu'on veux afficher
    for(i=0; strcmp(images->nomsImages[i], nom2)!=0 && i<images->nb_images; i++);
    //on l'affiche ensuite
    SDL_RenderCopy(pRenderer, images->l_textImages[i], &imgSrcRect, &imgDestRect);
}

/**
 * \fn extern void FreeImages(images_t * images)
 * \brief Libération mémoire de la structure image_t.
 *
 * \param images Pointeur sur une structure images_t.
 */
extern
void FreeImages(images_t * images){
	for(int i = 0; i < images->nb_images; i++){
		free(images->nomsImages[i]);
        SDL_DestroyTexture(images->l_textImages[i]);
	}
	free(images->nomsImages);
	free(images->l_textImages);
}

/**
 * \fn extern text_t * init_struct_text()
 * \brief Initialisation d'une structure text_t servant à stocké des textures de textes.
 *
 * \return text_t* Pointeur sur une structure text_t.
 */
extern
text_t * init_struct_text(){
    text_t * text;
    text = malloc(sizeof(text_t));
    text->nb_text = 0;
    text->text = malloc(sizeof(char *));
    text->l_textText = malloc(sizeof(SDL_Texture *));
    return text;
}

/**
 * \fn extern void createText(SDL_Renderer *pRenderer, text_t * text, int x, int y, int text_width, int text_height, const char *texte, TTF_Font *font, const char color)
 * \brief Fonction de création de texte à l'endroit donné sur le rendu, avec sa taille, son contenu, sa police et sa couleur.
 *
 * \param pRenderer Pointeur sur le rendu où va se trouver le texte.
 * \param text Pointeur sur une structure text_t servant à rangé les textures de textes.
 * \param x Position en X du centre du texte sur le rendu.
 * \param y Position en Y du centre du texte sur le rendu.
 * \param text_width Largeur du texte sur le rendu.
 * \param text_height Hauteur du texte sur le rendu.
 * \param texte Contenu du texte sur le rendu.
 * \param font Pointeur sur une structure TTF_Font étant la police du texte.
 * \param color Caractère représentant la couleur du texte (exemple : 'r' pour rouge).
 */
extern
void createText(SDL_Renderer *pRenderer, text_t * text, int x, int y, int text_width, int text_height, const char *texte, TTF_Font *font, const char color){
    int flag = 0, i;
    SDL_Rect textRect;
    SDL_Texture *textTexture;

    textRect.x = x - (text_width/2);
    textRect.y = y - (text_height/2);
    textRect.w = text_width;
    textRect.h = text_height;

    if(text->nb_text > 0){
        for(i = 0; i < text->nb_text; i++){
            if(strcmp(text->text[i], texte) == 0) flag = i;
        }
    }

    if(!flag){
        SDL_Surface *textSurface;
        SDL_Color textColor;

        switch(color){
            case 'b':
                textColor.r = 0;
                textColor.g = 0;
                textColor.b = 0;
            break;
            case 'w':
                textColor.r = 255;
                textColor.g = 255;
                textColor.b = 255;
            break;
            case 'r':
                textColor.r = 255;
                textColor.g = 0;
                textColor.b = 0;
            break;
        }

        textSurface = TTF_RenderText_Blended(font, texte, textColor);
        textTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
        SDL_FreeSurface(textSurface);

        text->nb_text++;
        text->text = realloc(text->text, sizeof(char *) * text->nb_text);
        text->text[text->nb_text - 1] = malloc(sizeof(char) * strlen(texte) + 1);
        strcpy(text->text[text->nb_text - 1], texte);
        text->l_textText = realloc(text->l_textText, sizeof(SDL_Texture *) * text->nb_text);
        text->l_textText[text->nb_text - 1] = textTexture;
    }
    else{
        textTexture = text->l_textText[flag];
    }

    SDL_RenderCopy(pRenderer, textTexture, NULL, &textRect);
}

/**
 * \fn extern void freeText(text_t ** text)
 * \brief Fonction de libération mémoire d'une structure text_t.
 *
 * \param text Double pointeur sur une structure text_t.
 */
extern
void freeText(text_t ** text){
    for(int i = 0; i < (*text)->nb_text; i++){
        free((*text)->text[i]);
        SDL_DestroyTexture((*text)->l_textText[i]);
    }
    free((*text)->text);
    free((*text)->l_textText);
    free(*text);
    *text = NULL;
}
