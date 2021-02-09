#include "sdl.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

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
    // Initialisation SDL text
    TTF_Init();

    //Création de la fenêtre et du rendu

    win->pWindow = SDL_CreateWindow("Jeu test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    win->pRenderer = SDL_CreateRenderer(win->pWindow,-1,SDL_RENDERER_ACCELERATED);

    if(!(win->pRenderer)){
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
        exit(0);
    }

    return win;
}

SDL_Texture * LoadImages(SDL_Renderer* pRenderer){
    printf("Chargement des images...\n");
    DIR *d;
    struct dirent *dir;
    char **nomsImages;
    int nb_images = 0;
    SDL_Texture * images;

    d = opendir("../../assets/images");
    while((dir = readdir(d)) != NULL) nb_images++;
    closedir(d);

    nomsImages = (char**)malloc(sizeof(char*) * nb_images);
    images = malloc(sizeof(SDL_Texture) * nb_images);

    d = opendir("../../assets/images");
    for(int i = 0; (dir = readdir(d)) != NULL; i++){
        nomsImages[i] = (char*)malloc(sizeof(char) * strlen(dir->d_name)+1);
        strcpy(nomsImages[i], dir->d_name);
    }
    closedir(d);
    for(int i=0; i<nb_images; i++){
        char nom[50] = "../../assets/images/";
        strcat(nom, nomsImages[i]);
        images[i] = IMG_LoadTexture(pRenderer, nom);
        printf("%s\n", nom);
    }
    printf("Images chargées: %d\n", nb_images);

    return images;
}

void DisplayImage(SDL_Texture *t, int posX, int posY){

}