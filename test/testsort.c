#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/player/player.h"
#include "../src/player/spell/petrificus.h"

int main(){

    if(SDL_Init(SDL_INIT_TIMER) != 0){
        printf("Error : %s", SDL_GetError());
    }


    player_t * player = createPlayer(1, "Clement", NULL);
    petrificus_t * petri = createPetrificus(player, 300, 300);

    while(petri->collision_test(petri, petri->destX, petri->destY, player)){
        petri->deplacement(petri, petri->destX, petri->destY);
        system("clear");
        printf("x:%i y:%i\n", petri->pos_x, petri->pos_y);
        sleep(0.5);
    }

    printf("Y a eu collision du coup player stun\n");
    petri->destroy(&petri);
    printf("%p\n", petri);

    SDL_Delay(2500);

    SDL_Quit();

}
