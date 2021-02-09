#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/player/spell/expelliarmus.h"

int main(){

    expelliarmus_t * expe = createExpelliarmus(20, 20);

    int x_dest, y_dest;
    x_dest = 400;
    y_dest = 600;

    while(expe->collision_test(expe, x_dest, y_dest)){
        expe->deplacement(expe, x_dest, y_dest);
        system("clear");
        printf("x:%i y:%i\n", expe->pos_x, expe->pos_y);
        sleep(0.5);
        
    }

    expe->destroy(&expe);

}