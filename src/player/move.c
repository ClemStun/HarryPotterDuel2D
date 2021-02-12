#include "../sdl/sdl.h"

int posX = 50, posY = 50;
double posXfloat = 0, posYfloat = 0;
double vitesse = 0;
double vX = 0, vY = 0, norme = 0;

extern
void updatePosition(window * win, images_t * images, int deplX, int deplY){
    vX = (double)deplX - posXfloat;
    vY = (double)deplY - posYfloat;

    norme = sqrt(vX*vX + vY*vY);

    posXfloat += (vX/norme)*vitesse;
    posYfloat += (vY/norme)*vitesse;

    posX = (int)posXfloat;
    posY = (int)posYfloat;

    if((posX < deplX-2 || posX > deplX+2) || (posY < deplY-2 || posY > deplY+2)){
        vitesse = 1.01;
    }
    else{
        vitesse = 0;
    }

    DrawImage(win->pRenderer, images, "insta.png", posX, posY, 100, 100);
}
