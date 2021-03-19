#include <stdio.h>

typedef struct petrificus_s{

    char * name;
    int speed;
    int damage;
    int manaCost;
    int pos_x;
    int pos_y;
    int destX;
    int destY;
    float posXf;
    float posYf;
    int width;
    int height;
    int sender;

    //SDL_Texture * sprite;

    void (*deplacement)(struct petrificus_s *, int, int);
    void (*display)(struct petrificus_s *, window *);
    int (*collision_test)(struct petrificus_s **,int , int, player_t *);
    void (*destroy)(struct petrificus_s **);

} petrificus_t;

extern petrificus_t * createPetrificus(player_t *);