#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/player/spell/petrificus.h"

int main(){

    if(SDL_Init(SDL_INIT_TIMER) != 0){
        printf("Error : %s", SDL_GetError());
    }
        

    player_t * player = createPlayer(1, "Clement", NULL);
    petrificus_t * petri = createPetrificus(player);

    int x_dest, y_dest;
    x_dest = 300;
    y_dest = 20;

    while(petri->collision_test(petri, x_dest, y_dest, player)){
        petri->deplacement(petri, x_dest, y_dest);
        system("clear");
        printf("x:%i y:%i\n", petri->pos_x, petri->pos_y);
        sleep(0.5);
    }

    printf("Y a eu collision\n");
    petri->destroy(&petri);

    SDL_Delay(3000);

    SDL_Quit();

}