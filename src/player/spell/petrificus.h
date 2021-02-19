#include <stdio.h>
#include "../player.h"

typedef struct petrificus_s{

    char * name;
    int speed;
    int damage;
    int pos_x;
    int pos_y;
    float posXf;
    float posYf;
    int width;
    int height;
    int sender;

    //SDL_Texture * sprite;

    void (*deplacement)(struct petrificus_s *, int, int);
    void (*display)(struct petrificus_s *);
    int (*collision_test)(struct petrificus_s *,int , int, player_t *);
    void (*destroy)(struct petrificus_s **);

} petrificus_t;

extern petrificus_t * createPetrificus(player_t *);