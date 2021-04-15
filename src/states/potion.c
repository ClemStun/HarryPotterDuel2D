/**
 * \file potion.c
 * \brief Menu de création de potions
 * \author COMTE Clément
 * \version 0.1
 * \date 14 feb 2021
 *
 */
#include "../../lib/menus.h"
#include "../../lib/ingredients.h"

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
 * \fn static void MakePotion(void)
 * \brief Menu de création de potion
 * 
 * \return Retourne rien.
 */
static
void MakePotion(){

    int ingredient;
    int potion = 0;
    int restant = 3;
    int i;

    while(restant > 0){

        ingredient = 0;

        printf("Ajoutez %i ingredients !\n", restant);

        while(ingredient < 1 || ingredient > 3){
            printf("\nIngrédients disponible :\n");
            printf("1 - Racinde d'asphodele\n");
            printf("2 - Ecrain de licorne\n");
            printf("3 - Mandragore\n");

            scanf("%i", &ingredient);
            if(ingredient < 1 || ingredient > 3)
                printf("Cet ingredient n'existe pas !\n\n");
        }

        potion = potion * 10 + ingredient;
        restant --;

        printf("Ingredients de la potion : %i\n", potion);
    }

    i = GetPotionIndex(potion);
    if(i < 0)
        printf("Cette potions n'existe pas \n");
    else{
        printf("Vous avez confectionné une potion: %s\n", nomPotions[i]);
        potions_unlock[i] = 1;
    }

}

static
void AfficherPotion(){
    int i, j, n, in, noPotion = 1;
    for(i = 0; i < NB_POT; i++){
        if(potions_unlock[i] == 1){
            noPotion = 0;
            printf("%s : \n\t", nomPotions[i]);
            n = potions[i];
            for(j = 100; j > 0; j = j/10){
              in = n/j-1;
              printf("%s ", ingredients[in]);
              n %= j;
            }
            printf("\n");
        }
    }
    if(noPotion)
        printf("Vous n'avez pas encore créer de potion !\n");
}

/**
 * \fn extern t_etat potion_state()
 * \brief Menu principal des potions choix entre potion, ingrédient et quitter
 * 
 * \return Retourne le prochaine état du jeu
 */
extern
t_etat potion_state(){

    int choix;

    while(1){

        choix = 0;

        while(choix < 1 || choix > 3){
            printf("1 - Faire une potion \n");
            printf("2 - Liste recettes\n");
            printf("3 - Quitter \n");

            scanf("%i", &choix);

            if(choix < 1 || choix > 3)
                printf("Le choix doit etre compris entre 1 et 3\n\n");
        }

        switch(choix){
            case 1:
                MakePotion(); 
                break;
            case 2:
                AfficherPotion();
                break;
            case 3:
                return HOME;
        }
    }

}