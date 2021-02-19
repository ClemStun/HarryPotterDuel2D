#include <stdio.h>

typedef struct expelliarmus_s{

    char * name;
    int speed;
    int damage;
    int pos_x;
    int pos_y;
    int width;
    int height;
    int sender;

    //SDL_Texture * sprite;

    void (*deplacement)(struct expelliarmus_s *, int, int);
    void (*display)(struct expelliarmus_s *);
    int (*collision_test)(struct expelliarmus_s *,int , int);
    void (*destroy)(struct expelliarmus_s **);

} expelliarmus_t;

extern expelliarmus_t * createExpelliarmus(int, int);