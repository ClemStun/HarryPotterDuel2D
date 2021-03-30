#define NB_SORT 5

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
    
    void (*deplacement)(struct sort_s *, int, int);
    void (*display)(struct sort_s *, window *, struct images_s *);
    int (*collision_test)(struct sort_s **,int , int, void *);
    void (*destroy)(struct sort_s **);

} sort_t;

typedef struct cd_s{
    int timer;
    sort_t * (*createSort)(void *);
    sort_t * sort;
}cd_t;
