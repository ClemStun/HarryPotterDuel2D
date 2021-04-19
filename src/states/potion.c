/**
 * \file potion.c
 * \brief Menu de création de potions
 * \author COMTE Clément & COUTANT Hugo
 * \version 1
 * \date 17 avril 2021
 *
 */
#include "../../lib/menus.h"
#include "../../lib/potions.h"

/**
 * \fn static int GetPotionIndex(int potion)
 * \brief Recherche l'index de la potion dans le tableau général
 *
 * \param potion numero de la potion créer précédement
 * \return Retourne l'index de la potion
 */
static
int GetPotionIndex(int potion){

    int i;

    for(i = 0; i < NB_POT; i++)
        if(potion == potions[i])
            return i;

    return -1;

}

/**
 * \fn static int MakePotion(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click)
 * \brief Menu de création de potion
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param mouseX Position en X de la souris.
 * \param mouseY Position en Y de la souris.
 * \param click Valeur du click, 1 = click detecté, 0 sinon.
 *
 * \return Retourne soit son propre état, soit un autre.
 */
static
int MakePotion(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click){

    static int ingredient = 0, potion = 0, restant = 3, i;
    static char r[3], aj[] = "Ajoutez ", ingr[] = " ingredient(s)", final[35] = "";

    //On regarde si nous avons saisi trois ingrédients, si non on continu de demandé un prochain ingrédient
    if(restant > 0){
        SDL_RenderClear(win->pRenderer);

        //Chaine de caractere adaptive en fonction du nombre restant d'ingrédients à ajouter
        strcpy(final, "");
        sprintf(r, "%i", restant);
        strcat(final, aj);
        strcat(final, r);
        strcat(final, ingr);

        //Texte + boutons
        createText(win->pRenderer, text, SCREEN_WIDTH/2, 50, 1100, 125, final, font, 'w');

        if(!(zone_detect(SCREEN_WIDTH/2-125, 150, 300, 100, mouseX, mouseY))){
            createButton(win, text, SCREEN_WIDTH/2-125, 150, 300, 100, "Racine d'asphodele", font, 'b');
        }
        else if(zone_detect(SCREEN_WIDTH/2-125, 150, 300, 100, mouseX, mouseY) && click == 0){
            createButton(win, text, SCREEN_WIDTH/2-125, 150, 300, 100, "racine d'asphodele", font, 'r');
        }
        else if(zone_detect(SCREEN_WIDTH/2-125, 150, 300, 100, mouseX, mouseY) && click == 1){
            ingredient = 1;
            potion = potion * 10 + ingredient;
            restant--;
            click = 0;
        }

        if(!(zone_detect(SCREEN_WIDTH/2-125, 300, 300, 100, mouseX, mouseY))){
            createButton(win, text, SCREEN_WIDTH/2-125, 300, 300, 100, "Ecrain de licorne", font, 'b');
        }
        else if(zone_detect(SCREEN_WIDTH/2-125, 300, 300, 100, mouseX, mouseY) && click == 0){
            createButton(win, text, SCREEN_WIDTH/2-125, 300, 300, 100, "ecrain de licorne", font, 'r');
        }
        else if(zone_detect(SCREEN_WIDTH/2-125, 300, 300, 100, mouseX, mouseY) && click == 1){
            ingredient = 2;
            potion = potion * 10 + ingredient;
            restant --;
            click = 0;
        }

        if(!(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY))){
            createButton(win, text, SCREEN_WIDTH/2-125, 450, 300, 100, "Mandragore", font, 'b');
        }
        else if(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY) && click == 0){
            createButton(win, text, SCREEN_WIDTH/2-125, 450, 300, 100, "mandragore", font, 'r');
        }
        else if(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY) && click == 1){
            ingredient = 3;
            //code représentant les différents ingrédients ajoutés
            potion = potion * 10 + ingredient;
            restant --;
            click = 0;
        }
    }
    //Quand on a assez d'ingrédient on rentre ici
    if(restant <= 0){
        //On cherche l'index de la potion par rapport au ingrédients entrés
        i = GetPotionIndex(potion);
        //Si la potion créée n'existe pas
        if(i < 0){
            createText(win->pRenderer, text, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1100, 125, "Cette potion n'existe pas", font, 'w');

            if(!(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY))){
                createButton(win, text, SCREEN_WIDTH/2-125, 450, 300, 100, "Retour", font, 'b');
            }
            else if(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY) && click == 0){
                createButton(win, text, SCREEN_WIDTH/2-125, 450, 300, 100, "retour", font, 'r');
            }
            else if(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY) && click == 1){
                ingredient = 0;
                potion = 0;
                restant = 3;
                click = 0;
                return 0;
            }
        }
        //Si elle existe
        else{
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 100, 1100, 125, "Vous avez confectionne une potion :", font, 'w');
            createText(win->pRenderer, text, SCREEN_WIDTH/2, 300, 800, 125, nomPotions[i], font, 'w');

            if(!(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY))){
                createButton(win, text, SCREEN_WIDTH/2-125, 450, 300, 100, "Retour", font, 'b');
            }
            else if(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY) && click == 0){
                createButton(win, text, SCREEN_WIDTH/2-125, 450, 300, 100, "retour", font, 'r');
            }
            else if(zone_detect(SCREEN_WIDTH/2-125, 450, 300, 100, mouseX, mouseY) && click == 1){
                ingredient = 0;
                potion = 0;
                restant = 3;
                click = 0;
                potions_unlock[i] = 1;
                return 0;
            }
        }
    }

    return 1;
}

/**
 * \fn static int AfficherPotion(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click)
 * \brief Menu d'affichage de potions
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 * \param mouseX Position en X de la souris.
 * \param mouseY Position en Y de la souris.
 * \param click Valeur du click, 1 = click detecté, 0 sinon.
 *
 * \return Retourne soit son propre état, soit un autre.
 */
static
int AfficherPotion(window *win, text_t * text, TTF_Font *font, int mouseX, int mouseY, int click){
    static int noPotion = 1;
    static char in[NB_IN][21];

    for(int i = 0; i < NB_IN; i++){
        strcpy(in[i], ingredients[i]);
        strcat(in[i], " ");
    }

    //Affichage des potions et de leur recette si elles sont débloquées
    if(potions_unlock[0] == 1){
        createText(win->pRenderer, text, SCREEN_WIDTH/2, 50, 400, 50, nomPotions[0], font, 'w');

        createText(win->pRenderer, text, 300, 100, 200, 25, in[0], font, 'w');
        createText(win->pRenderer, text, 600, 100, 250, 25, in[1], font, 'w');
        createText(win->pRenderer, text, 900, 100, 250, 25, in[2], font, 'w');

        noPotion = 0;
    }

    if(potions_unlock[1] == 1){
        createText(win->pRenderer, text, SCREEN_WIDTH/2, 200, 400, 50, nomPotions[1], font, 'w');

        createText(win->pRenderer, text, 300, 250, 250, 25, in[1], font, 'w');
        createText(win->pRenderer, text, 600, 250, 200, 25, in[0], font, 'w');
        createText(win->pRenderer, text, 900, 250, 250, 25, in[2], font, 'w');

        noPotion = 0;
    }

    if(potions_unlock[2] == 1){
        createText(win->pRenderer, text, SCREEN_WIDTH/2, 350, 400, 50, nomPotions[2], font, 'w');

        createText(win->pRenderer, text, 300, 400, 200, 25, in[0], font, 'w');
        createText(win->pRenderer, text, 600, 400, 250, 25, in[2], font, 'w');
        createText(win->pRenderer, text, 900, 400, 250, 25, in[1], font, 'w');

        noPotion = 0;
    }

    //Si aucune potion débloquée
    if(noPotion)
        createText(win->pRenderer, text, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1100, 125, "Vous n'avez pas encore confectionne de potion", font, 'w');

    if(!(zone_detect(1000, 500, 150, 75, mouseX, mouseY))){
        createButton(win, text, 1000, 500, 150, 75, "Retour", font, 'b');
    }
    else if(zone_detect(1000, 500, 150, 75, mouseX, mouseY) && click == 0){
        createButton(win, text, 1000, 500, 150, 75, "retour", font, 'r');
    }
    else if(zone_detect(1000, 500, 150, 75, mouseX, mouseY) && click == 1){
        return 0;
    }

    return 2;
}

/**
 * \fn extern t_etat potion_state(window *win, player_t *monPerso, text_t * text, TTF_Font *font)
 * \brief Menu principal des potions choix entre potion, ingrédient et quitter
 *
 * \param win Pointeur sur une structure window_s, étant la fenêtre du jeu.
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param text Pointeur sur une structure text_s regroupant les différents textes déjà créer et leur texture.
 * \param font Pointeur sur une police de caractère.
 *
 * \return Retourne soit son propre état soit le prochain état du jeu
 */
extern
t_etat potion_state(window *win, player_t *monPerso, text_t * text, TTF_Font *font){

    static int mouseX, mouseY, click = 0, choix = 0, i = 0, flag = 0;

    //Si nouveau joueur, alors on créer son tableau de potions sans recette trouvée
    if(monPerso->potions_unl == NULL){
        monPerso->potions_unl = malloc(sizeof(int) * NB_POT);
        for(int i = 0; i < NB_POT; i++)
            monPerso->potions_unl[i] = 0;
    }
    //Sinon on synchronise les infos avec ce qui est contenu dans les infos du joueur
    else if(flag == 0){
        for(int i = 0; i < NB_POT; i++)
            potions_unlock[i] = monPerso->potions_unl[i];
        flag = 1;
    }

    //Synchronisation données joueur et données état potion
    for(i = 0; i < NB_POT; i++)
        monPerso->potions_unl[i] = potions_unlock[i];

    monPerso->nb_pot = NB_POT;

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
        }
    }
    SDL_GetMouseState(&mouseX, &mouseY);

    //Switch de navigation
    switch(choix){
        case 0:
            if(!(zone_detect(SCREEN_WIDTH/2-250, 50, 500, 150, mouseX, mouseY))){
                createButton(win, text, SCREEN_WIDTH/2-250, 50, 500, 150, "Faire une potion", font, 'b');
            }
            else if(zone_detect(SCREEN_WIDTH/2-250, 50, 500, 150, mouseX, mouseY) && click == 0){
                createButton(win, text, SCREEN_WIDTH/2-250, 50, 500, 150, "faire une potion", font, 'r');
            }
            else if(zone_detect(SCREEN_WIDTH/2-250, 50, 500, 150, mouseX, mouseY) && click == 1){
                choix = 1;
                click = 0;
            }


            if(!(zone_detect(SCREEN_WIDTH/2-250, 250, 500, 150, mouseX, mouseY))){
                createButton(win, text, SCREEN_WIDTH/2-250, 250, 500, 150, "Liste recettes", font, 'b');
            }
            else if(zone_detect(SCREEN_WIDTH/2-250, 250, 500, 150, mouseX, mouseY) && click == 0){
                createButton(win, text, SCREEN_WIDTH/2-250, 250, 500, 150, "liste recettes", font, 'r');
            }
            else if(zone_detect(SCREEN_WIDTH/2-250, 250, 500, 150, mouseX, mouseY) && click == 1){
                choix = 2;
                click = 0;
            }

            if(!(zone_detect(1000, 500, 150, 75, mouseX, mouseY))){
                createButton(win, text, 1000, 500, 150, 75, "Quitter", font, 'b');
            }
            else if(zone_detect(1000, 500, 150, 75, mouseX, mouseY) && click == 0){
                createButton(win, text, 1000, 500, 150, 75, "quitter", font, 'r');
            }
            else if(zone_detect(1000, 500, 150, 75, mouseX, mouseY) && click == 1){
                choix = 3;
                click = 0;
            }
        break;
        case 1:
            choix = MakePotion(win, text, font, mouseX, mouseY, click);
        break;
        case 2:
            choix = AfficherPotion(win, text, font, mouseX, mouseY, click);
        break;
        case 3:
            choix = 0;
            return HOME;
    }
    click = 0;

    SDL_SetRenderDrawColor(win->pRenderer, 0, 0, 0, 0 );
    return POTION;
}

