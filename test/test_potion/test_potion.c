#include <stdio.h>
#include <stdlib.h>

#include "../../lib/menus.h"
#include "../../lib/potions.h"

int GetPotionIndex(int potion){

    int i;

    for(i = 0; i < NB_POT; i++)
        if(potion == potions[i])
            return i;

    return -1;

}

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
    else
        printf("Vous avez confectionné une potion: %s\n", nomPotions[i]);

}

void menu(){

    int choix = 1;

    while(choix){

        printf("Lancement de la création ...\n");
        MakePotion();

        printf("Voulez-vous faire un autre test ? (0/1)");
        scanf("%i", &choix);

    }

}


int main(void){

    printf("-- TEST CREATION POTION --\n");
    menu();
    printf("-- FIN DE TEST --\n");

    return EXIT_SUCCESS;
}