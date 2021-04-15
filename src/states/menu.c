/**
 * \file menu.c
 * \brief Déroulement du jeu dans l'état HOME
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

/**
 * \fn extern void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color)
 * \brief Fonction de création d'un bouton sur la fenêtre en fonction d'une position donnée, d'une dimension, d'un texte, d'une police et d'une couleur.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param posX Position en X du bouton.
 * \param posY Position en Y du bouton.
 * \param rectW Largeur du bouton.
 * \param rectH Hauteur du bouton.
 * \param texte Chaine de caractère correspondant au texte du bouton.
 * \param fontButton Police de texte du bouton.
 * \param color Couleur du texte du bouton.
 *
 */
extern
void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color){

    //Parametres rectangle du bouton
    SDL_Rect button;
    button.x = posX;
    button.y = posY;
    button.w = rectW;
    button.h = rectH;

    //Couleur et intégration de la texture du rectangle sur le rendu
    SDL_SetRenderDrawColor(win->pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(win->pRenderer, &button);

    //Ecriture du texte sur le bouton
    createText(win->pRenderer, text, posX + rectW/2, posY + rectH/2, rectW-100, rectH-50, texte, fontButton, color);
}

/**
 * \fn static int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY)
 * \brief Fonction de détection de zone de la souris.
 *
 * \param x Position en X en haut à gauche de la zone à tester.
 * \param y Position en Y en haut à gauche de la zone à tester.
 * \param w Largeur de la zone.
 * \param h Hauteur de la zone.
 * \param mouseX Position en X de la souris.
 * \param mouseY Position en Y de la souris.
 *
 * \return 1 si souris dans la zone, 0 sinon.
 */
extern
int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY){
    if((mouseX >= x && mouseY >= y) && (mouseX <= x + w && mouseY <= y + h)){
        return 1;
    }
    return 0;
}

/**
 * \fn extern t_etat home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font)
 * \brief Fonction état du jeu en mode menu principal.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param font Police du menu.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font){
    static int mouseX, mouseY, click = 0;

    SDL_RenderClear(win->pRenderer);

    //Lecture des évènements
    while(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return QUIT;
			break;
            case SDL_MOUSEBUTTONDOWN:
                if(SDL_BUTTON(SDL_BUTTON_LEFT)){
                    click = 1;
                }
            break;
        }
    }
    SDL_GetMouseState(&mouseX, &mouseY);

    //Affichage du logo
    DrawImage(win->pRenderer, images, searchTexture(images, "logo.png"), 0, 0, 29, 21, SCREEN_WIDTH/2 - 150, 20, 290, 210);

    /*Fonctionnement du test des boutons,
    Si souris hors zone du bouton, alors le bouton s'affiche en blanc et ecriture noire,
    si souris sur bouton sans cliquer, alors bouton s'affiche en blanc et ecriture rouge,
    si un click est effectué sur le bouton, alors on a redirection vers un autre état.
    */

    if(!(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH-250, 50, 200, 100, "Jouer", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, 50, 200, 100, "jouer", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 50, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return WAITING;
    }
    createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "Quitter", font, 'b');
    if(zone_detect(SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, "quitter", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, SCREEN_HEIGHT-150, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return QUIT;
    }
    if(!(zone_detect(SCREEN_WIDTH-250, 200, 200, 100, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH-250, 200, 200, 100, "Train", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 200, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, 200, 200, 100, "train", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 200, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return TRAINING;
    }
    if(!(zone_detect(SCREEN_WIDTH-250, 320, 200, 100, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH-250, 320, 200, 100, "Potion", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 320, 200, 100, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH-250, 320, 200, 100, "potion", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH-250, 320, 200, 100, mouseX, mouseY) && click == 1){
        click = 0;
        return POTION;
    }

    //Petit easter egg sur le personnage ;)
    if(!(zone_detect(100, 275, 300, 300, mouseX, mouseY))){
        DrawImage(win->pRenderer, images, monPerso->sprite, 7*32, 0, 32, 32, 100, 275, 300, 300);
    }
    else if(zone_detect(100, 275, 300, 300, mouseX, mouseY)){
        DrawImage(win->pRenderer, images, monPerso->sprite, 7*32, 4*32, 32, 32, 100, 275, 300, 300);
    }

    //Affichage du nom de joueur et sa maison
    createText(win->pRenderer, text, 250, 225, 125, 63, monPerso->name, font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 350, 125, 50, "Maison :", font, 'w');
    switch (monPerso->house){
        case 'g':
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 400, 125, 50, "Griffondor", font, 'r');
            DrawImage(win->pRenderer, images, searchTexture(images, "griffondor.png"), 375, 129, 245, 756, 215, 10, 61, 189);
        break;
        case 's':
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 400, 125, 50, "Serpentard", font, 'g');
            DrawImage(win->pRenderer, images, searchTexture(images, "serpentard.png"), 375, 129, 245, 756, 215, 10, 61, 189);
        break;
        case 'r':
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 400, 125, 50, "Serdaigle", font, 'B');
            DrawImage(win->pRenderer, images, searchTexture(images, "serdaigle.png"), 375, 129, 245, 756, 215, 10, 61, 189);
        break;
        case 'p':
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 400, 125, 50, "Poufsouffle", font, 'y');
            DrawImage(win->pRenderer, images, searchTexture(images, "poufsouffle.png"), 375, 129, 245, 756, 215, 10, 61, 189);
        break;
    }

	click = 0;

    //Couleur du fond
    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0 );
    return HOME;
}



