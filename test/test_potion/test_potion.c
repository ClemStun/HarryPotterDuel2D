#include <stdio.h>

#include "../../lib/menus.h"
#include "../../lib/potions.h"
#include "../../lib/ingredients.h"

static
int GetPotionIndex(int potion){

    int i;

    for(i = 0; i < NB_POT; i++)
        if(potion == potions[i])
            return i;

    return -1;

}

static
int MakePotion(int potion){

    int i;

    i = GetPotionIndex(potion);
    if(i < 0)
        printf("Cette potions n'existe pas \n");
    else{
        printf("Vous avez confectionné une potion: %s\n", nomPotions[i]);
        potions_unlock[i] = 1;
    }

    return i;
}

static
int AfficherPotion(){
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
    if(noPotion){
        printf("Vous n'avez pas encore créer de potion !\n");
        return 1;
    }else{
        return 0;
    }
}

int main(){

    printf("-- TEST POTION --\n");

    printf("-- Test affichage potion pas débloqué --\n");
    if(AfficherPotion() == 1)
        printf("OK !\n");
    else
        printf("KO !\n");

    printf("-- Test sur potion qui existe --\n");
    if(MakePotion(123) >= 0)
        printf("OK !\n");
    else
        printf("KO !\n");
    
    printf("-- Test sur potion avec qui n'existe pas --\n");
    if(MakePotion(421) < 0)
        printf("OK !\n");
    else
        printf("KO !\n");

    printf("-- Test sur potion avec ingrédients inexistant --\n");
    if(MakePotion(421) < 0)
        printf("OK !\n");
    else
        printf("KO !\n");

    printf("-- Test affichage potion débloqué --\n");
    if(AfficherPotion() == 0)
        printf("OK !\n");
    else
        printf("KO !\n");

    printf("-- FIN DE TEST --\n");

    return 0;
}