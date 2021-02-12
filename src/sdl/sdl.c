#include "sdl.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

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

    //Création de la fenêtre et du rendu

    win->pWindow = SDL_CreateWindow("Jeu test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    win->pRenderer = SDL_CreateRenderer(win->pWindow,-1,SDL_RENDERER_ACCELERATED);

    if(!(win->pRenderer)){
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
        exit(0);
    }

    return win;
}

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

extern
void DrawImage(SDL_Renderer * pRenderer, images_t * images, char * nom, int x, int y, int w, int h){
    // x et y les coordonnées,
    SDL_Rect imgDestRect;
    imgDestRect.x = x;
    imgDestRect.y = y;
    imgDestRect.w = w;
    imgDestRect.h = h;
  char nom2[50];
  sprintf(nom2, "%s", nom);
  if(!strstr(nom2, ".png")){
    strcat(nom2, ".png");
  }
    int i;
    //ici on recherche quel est l'indice de l'image qu'on veux afficher
    for(i=0; strcmp(images->nomsImages[i], nom2)!=0 && i<images->nb_images; i++);
    //on l'affiche ensuite
    SDL_RenderCopy(pRenderer, images->l_textImages[i], NULL, &imgDestRect);
}

extern
void FreeImages(images_t * images){
	for(int i = 0; i < images->nb_images; i++){
		free(images->nomsImages[i]);
	}
	free(images->nomsImages);
	free(images->l_textImages);
}
