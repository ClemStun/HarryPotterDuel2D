/**
 * \file testMaisons.c
 * \brief Déroulement du jeu dans l'état TEST_M
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/menus.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

/**
 * \fn static int begin_test(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click)
 * \brief Fonction de début du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param mouseX Position en X de la souris.
 * \param mouseY Position en Y de la souris.
 * \param click Valeur du click, 1 = click detecté, 0 sinon.
 *
 * \return Soit son propre état donc 0 ici, soit 1 pour passer à la page suivante.
 */
static
int begin_test(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 150, 1100, 150, "Quelle maison vous acceptera ?", font, 'w');

    if(!(zone_detect(SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 50, 500, 150, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 50, 500, 150, "Prendre le chapeau", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 50, 500, 150, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 50, 500, 150, "prendre le chapeau", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 50, 500, 150, mouseX, mouseY) && click == 1){
        click = 0;
        return 1;
    }
    return 0;
}

/**
 * \fn static int test_un(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la premiere page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 1 ici, soit 2 pour passer à la page suivante.
 */
static
int test_un(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 800, 75, "Quelle est ta plus grande qualite ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 150, 25, "Ton audace", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 900, 250, 150, 25, "Ta sensibilite", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 150, 25, "Ta creativite", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 900, 450, 150, 25, "Ta malice", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "1/10", font, 'w');

    switch(choix){
        case 'A':
            house[0]++;
            return 2;
        break;
        case 'B':
            house[3]++;
            return 2;
        break;
        case 'C':
            house[2]++;
            return 2;
        break;
        case 'D':
            house[1]++;
            return 2;
        break;
        default:
            return 1;
    }
}

/**
 * \fn static int test_deux(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la seconde page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 2 ici, soit 3 pour passer à la page suivante.
 */
static
int test_deux(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 800, 75, "Quel est ton plus gros defaut ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 150, 25, "Ta passivite", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 900, 250, 150, 25, "Ton orgueil", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 150, 25, "Ton impulsivite", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 900, 450, 150, 25, "Ton arrogance", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "2/10", font, 'w');

    switch(choix){
        case 'A':
            house[3]++;
            return 3;
        break;
        case 'B':
            house[2]++;
            return 3;
        break;
        case 'C':
            house[0]++;
            return 3;
        break;
        case 'D':
            house[1]++;
            return 3;
        break;
        default:
            return 2;
    }
}

/**
 * \fn static int test_trois(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la troisieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 3 ici, soit 4 pour passer à la page suivante.
 */
static
int test_trois(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 800, 75, "Quelle activite preferes-tu ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 150, 25, "Cuisine", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 900, 250, 150, 25, "Shopping", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 150, 25, "Sport", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 900, 450, 200, 35, "Activites culturelles", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "3/10", font, 'w');

    switch(choix){
        case 'A':
            house[3]++;
            return 4;
        break;
        case 'B':
            house[1]++;
            return 4;
        break;
        case 'C':
            house[0]++;
            return 4;
        break;
        case 'D':
            house[2]++;
            return 4;
        break;
        default:
            return 3;
    }
}

/**
 * \fn static int test_quatre(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la quatrieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 4 ici, soit 5 pour passer à la page suivante.
 */
static
int test_quatre(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 800, 75, "Dans ton groupe d'amis, tu es plutot :", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 150, 25, "Le clown", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 900, 250, 150, 25, "Le leader", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 150, 25, "Le conseiller", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 900, 450, 150, 25, "Le mediateur", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "4/10", font, 'w');

    switch(choix){
        case 'A':
            house[1]++;
            return 5;
        break;
        case 'B':
            house[0]++;
            return 5;
        break;
        case 'C':
            house[2]++;
            return 5;
        break;
        case 'D':
            house[3]++;
            return 5;
        break;
        default:
            return 4;
    }
}

/**
 * \fn static int test_cinq(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la cinquieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 5 ici, soit 6 pour passer à la page suivante.
 */
static
int test_cinq(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 1000, 75, "Quelle matiere magique t'attire le plus a l'ecole de Poudlard ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 175, 25, "Le cours de Sortileges", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 950, 250, 300, 25, "Le cours de Defense contre les Forces du Mal", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 175, 25, "Le cours de Potions", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 950, 450, 300, 25, "Le cours de Soins aux creatures magiques", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "5/10", font, 'w');

    switch(choix){
        case 'A':
            house[2]++;
            return 6;
        break;
        case 'B':
            house[0]++;
            return 6;
        break;
        case 'C':
            house[1]++;
            return 6;
        break;
        case 'D':
            house[3]++;
            return 6;
        break;
        default:
            return 5;
    }
}

/**
 * \fn static int test_six(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la sixieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 6 ici, soit 7 pour passer à la page suivante.
 */
static
int test_six(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 1000, 75, "Si tu ne pouvais utiliser qu'un seul sortilege, ce serait :", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+85, 250, 400, 25, "Alohomora, pour acceder a tous les lieux fermes", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 985, 250, 400, 25, "Accio, pour faire venir des objets a toi sans bouger", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+85, 450, 400, 25, "Legilimens, pour lire dans les pensees des autres", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 985, 450, 400, 25, "Wingardium Leviosa, pour faire lever les objets", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "6/10", font, 'w');

    switch(choix){
        case 'A':
            house[0]++;
            return 7;
        break;
        case 'B':
            house[3]++;
            return 7;
        break;
        case 'C':
            house[1]++;
            return 7;
        break;
        case 'D':
            house[2]++;
            return 7;
        break;
        default:
            return 6;
    }
}

/**
 * \fn static int test_sept(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la septieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 7 ici, soit 8 pour passer à la page suivante.
 */
static
int test_sept(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 1000, 75, "Quelle creature choisirais-tu pour t'accompagner a poudlard ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 150, 25, "Un chat", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 900, 250, 150, 25, "Un niffleur", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 150, 25, "Une chouette", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 900, 450, 150, 25, "Un crapaud", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "7/10", font, 'w');

    switch(choix){
        case 'A':
            house[1]++;
            return 8;
        break;
        case 'B':
            house[3]++;
            return 8;
        break;
        case 'C':
            house[2]++;
            return 8;
        break;
        case 'D':
            house[0]++;
            return 8;
        break;
        default:
            return 7;
    }
}

/**
 * \fn static int test_huit(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la huitieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 8 ici, soit 9 pour passer à la page suivante.
 */
static
int test_huit(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 1000, 75, "Quel objet magique aimerais-tu avoir le plus ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 250, 200, 25, "La baguette de Surreau", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 900, 250, 200, 25, "La carte du Maraudeur", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4, 450, 200, 25, "Le retourneur de temps", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 900, 450, 200, 25, "La cape d'invisibilite", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "8/10", font, 'w');

    switch(choix){
        case 'A':
            house[0]++;
            return 9;
        break;
        case 'B':
            house[3]++;
            return 9;
        break;
        case 'C':
            house[2]++;
            return 9;
        break;
        case 'D':
            house[1]++;
            return 9;
        break;
        default:
            return 8;
    }
}

/**
 * \fn static int test_neuf(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la neuvieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 9 ici, soit 10 pour passer à la page suivante.
 */
static
int test_neuf(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 1000, 75, "Quelle potion aimerais-tu utiliser parmi celles-ci ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 250, 250, 25, "De l'Aiguise-Meninges,", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 275, 250, 25, "pour mieux reflechir", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 925, 250, 250, 25, "De l'Amortentia, pour faire", font, 'w');
    createText(win->pRenderer, text, 925, 275, 250, 25, "tomber quelqu'un amoureux de toi", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 450, 250, 25, "Du Polynectar, pour prendre", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 475, 250, 25, "l'apparence de quelqu'un d'autre", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 925, 450, 250, 25, "Du Felix Felicis, pour que", font, 'w');
    createText(win->pRenderer, text, 925, 475, 250, 25, "tout te reussisse sans effort", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "9/10", font, 'w');

    switch(choix){
        case 'A':
            house[2]++;
            return 10;
        break;
        case 'B':
            house[0]++;
            return 10;
        break;
        case 'C':
            house[1]++;
            return 10;
        break;
        case 'D':
            house[3]++;
            return 10;
        break;
        default:
            return 9;
    }
}

/**
 * \fn static int test_dix(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la dixieme page du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 10 ici, soit 11 pour passer à la page suivante.
 */
static
int test_dix(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 75, 1000, 75, "Enfin, parce qu'il faut bien penser a l'avenir,", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 150, 1000, 75, "quel metier magique te plairait le plus ?", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 250, 250, 25, "Journaliste a la Gazette du sorcier", font, 'w');

    createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
    createText(win->pRenderer, text, 925, 250, 250, 25, "Professeur.e a Poudlard", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
    createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 450, 150, 25, "Auror", font, 'w');

    createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
    createText(win->pRenderer, text, 925, 450, 250, 25, "Ministre de la Magie", font, 'w');

    createText(win->pRenderer, text, SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 75, 75, "10/10", font, 'w');

    switch(choix){
        case 'A':
            house[3]++;
            return 11;
        break;
        case 'B':
            house[2]++;
            return 11;
        break;
        case 'C':
            house[0]++;
            return 11;
        break;
        case 'D':
            house[1]++;
            return 11;
        break;
        default:
            return 10;
    }
}

/**
 * \fn static int final_test(window *win, text_t * text, TTF_Font *font, int house[], char choix)
 * \brief Fonction de la page finale du test qui sert uniquement en cas d'égalité.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param choix Touche de réponse appuyé sur le clavier.
 *
 * \return Soit son propre état donc 11 ici, soit 12 pour passer à la page suivante.
 */
static
int final_test(window *win, text_t * text, TTF_Font *font, int house[], char choix){
    static int last_test = 0, i, max;

    if(last_test == 0){
        for(i = 0; i < 4; i++){
            if(house[i] > house[max]){
                max = i;
            }
        }

        for(i = 0; i < 4; i++){
            if(house[max] == house[i] && max != i){
                last_test = 1;
            }
        }
    }

    if(last_test == 1){
        createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 800, 75, "De quoi as-tu le plus peur ?", font, 'w');
        if(house[0] == house[max]){
            createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 250, 50, 50, "A", font, 'w');
            createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 250, 250, 25, "De la solitude", font, 'w');

            if(choix == 'A'){
                house[0]++;
                last_test = 2;
            }
        }
        if(house[1] == house[max]){
            createText(win->pRenderer, text, 900-150, 250, 50, 50, "B", font, 'w');
            createText(win->pRenderer, text, 925, 250, 250, 25, "Du feu", font, 'w');

            if(choix == 'B'){
                house[1]++;
                last_test = 2;
            }
        }
        if(house[2] == house[max]){
            createText(win->pRenderer, text, SCREEN_WIDTH/4-150, 450, 50, 50, "C", font, 'w');
            createText(win->pRenderer, text, SCREEN_WIDTH/4+25, 450, 150, 25, "Du noir", font, 'w');

            if(choix == 'C'){
                house[2]++;
                last_test = 2;
            }
        }
        if(house[3] == house[max]){
            createText(win->pRenderer, text, 900-150, 450, 50, 50, "D", font, 'w');
            createText(win->pRenderer, text, 925, 450, 250, 25, "Des endroits etroits", font, 'w');

            if(choix == 'D'){
                house[3]++;
                last_test = 2;
            }
        }
        return 11;
    }
    else if(last_test == 0 || last_test == 2){
        return 12;
    }
}

/**
 * \fn static int end_test(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click, int house[], player_t * monPerso)
 * \brief Fonction de fin du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param mouseX Position en X de la souris.
 * \param mouseY Position en Y de la souris.
 * \param click Valeur du click, 1 = click detecté, 0 sinon.
 * \param house Tableau état des valeurs de chaque maison suite aux réponses du test.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 *
 * \return Soit son propre état donc 12 ici, soit 13 pour terminer le test et aller au menu du jeu.
 */
static
int end_test(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click, int house[], player_t * monPerso){
    static int i, max;
    createText(win->pRenderer, text, SCREEN_WIDTH/2, 150, 1100, 150, "Vous etes donc", font, 'w');

    for(i = 0; i < 4; i++){
        if(house[i] > house[max]){
            max = i;
        }
    }

    switch(max){
        case 0:
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 300, 700, 150, "Griffondor", font, 'r');
            monPerso->house = 'g';
        break;
        case 1:
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 300, 700, 150, "Serpentard", font, 'g');
            monPerso->house = 's';
        break;
        case 2:
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 300, 700, 150, "Serdaigle", font, 'B');
            monPerso->house = 'r';
        break;
        case 3:
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 300, 700, 150, "Poufsouffle", font, 'y');
            monPerso->house = 'p';
        break;
    }

    if(!(zone_detect(SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 100, 500, 150, mouseX, mouseY))){
        createButton(win, text, SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 100, 500, 150, "Aller au dortoir", font, 'b');
    }
    else if(zone_detect(SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 100, 500, 150, mouseX, mouseY) && click == 0){
        createButton(win, text, SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 100, 500, 150, "aller au dortoir", font, 'r');
    }
    else if(zone_detect(SCREEN_WIDTH/2 -250, SCREEN_HEIGHT/2 + 100, 500, 150, mouseX, mouseY) && click == 1){
        click = 0;
        return 13;
    }
    return 12;
}

/**
 * \fn extern
 t_etat test_m_state(window *win, text_t * text, player_t * monPerso, TTF_Font *font)
 * \brief Fonction de fin du test.
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param font Pointeur sur une police de caractère.
 *
 * \return Soit son propre état pour y rester, soit un autre pour changer d'état dans la suite du programme.
 */
extern
t_etat test_m_state(window *win, text_t * text, player_t * monPerso, TTF_Font *font){
    const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
    static int mouseX, mouseY, click = 0, suivant = 0;
    static int house[4] = {0}; //Grifondor = 0, Serpentard = 1, Serdaigle = 2, Poufsouffle = 3
    char choix = 'N';

    SDL_RenderClear(win->pRenderer);

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
            case SDL_KEYDOWN:
                if(keyboard_state_array[SDL_SCANCODE_Q]){
                    choix = 'A';
                }else if(keyboard_state_array[SDL_SCANCODE_B]){
                    choix = 'B';
                }else if(keyboard_state_array[SDL_SCANCODE_C]){
                    choix = 'C';
                }else if(keyboard_state_array[SDL_SCANCODE_D]){
                    choix = 'D';
                }
            break;
        }
    }
    SDL_GetMouseState(&mouseX, &mouseY);

    switch (suivant) {
        case 0:
            suivant = begin_test(win, text, font, mouseX, mouseY, click);
        break;
        case 1:
            suivant = test_un(win, text, font, house, choix);
            choix = 'N';
        break;
        case 2:
            suivant = test_deux(win, text, font, house, choix);
            choix = 'N';
        break;
        case 3:
            suivant = test_trois(win, text, font, house, choix);
            choix = 'N';
        break;
        case 4:
            suivant = test_quatre(win, text, font, house, choix);
            choix = 'N';
        break;
        case 5:
            suivant = test_cinq(win, text, font, house, choix);
            choix = 'N';
        break;
        case 6:
            suivant = test_six(win, text, font, house, choix);
            choix = 'N';
        break;
        case 7:
            suivant = test_sept(win, text, font, house, choix);
            choix = 'N';
        break;
        case 8:
            suivant = test_huit(win, text, font, house, choix);
            choix = 'N';
        break;
        case 9:
            suivant = test_neuf(win, text, font, house, choix);
            choix = 'N';
        break;
        case 10:
            suivant = test_dix(win, text, font, house, choix);
            choix = 'N';
        break;
        case 11:
            suivant = final_test(win, text, font, house, choix);
            choix = 'N';
        break;
        case 12:
            suivant = end_test(win, text, font, mouseX, mouseY, click, house, monPerso);
        break;
        case 13:
            return HOME;
        break;
    }

	click = 0;

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0 );
    return TEST_M;
}
