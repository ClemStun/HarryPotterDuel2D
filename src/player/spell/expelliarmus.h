#include "../player.h"

typedef struct expelliarusmus_s{

    char name[20];
    int speed;
    int damage;
    int pos_x;
    int pos_y;
    int width;
    int heihgt;
    int sender;

    SDL_Texture * sprite;

    void (*deplacement)(struct expelliarusmus_s *, int, int);
    void (*display)(struct expelliarusmus_s *);
    int (*collision_test)(struct expelliarmus_s *, player_t *);
    void (*destroy)(struct expelliarusmus_s **);

} expelliarusmus_t;