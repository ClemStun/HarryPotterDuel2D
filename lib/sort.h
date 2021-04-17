/**
 * \file sort.h
 * \brief Structures générales des sorts
 * \author COMTE Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#define NB_SORT 5

/**
 * \struct sort_t
 * \brief Structure général d'un joueur
 */
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

/**
 * \struct cd_t
 * \brief Structure qui contient un sort et son couldown
 */
typedef struct cd_s{
    int timer; /*!< Timer de couldown du sort */
    sort_t * (*createSort)(void *, int, int); /*!< Fonction de création du sort */
    sort_t * sort; /*!< Sort lancé */
}cd_t;
