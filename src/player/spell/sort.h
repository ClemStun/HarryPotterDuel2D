#include "expelliarmus.h"

typedef struct sort_s{

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

    void (*deplacement)(struct sort_s *, int, int);
    void (*display)(struct sort_s *, window *);
    int (*collision_test)(struct sort_s **,int , int, int *);
    void (*destroy)(struct sort_s **);

} sort_t;