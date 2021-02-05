#include <string.h>

#include "expelliarusmus.h"
#include "../player.h"

void deplacement(expelliarusmus_t *, int, int);
void display(expelliarusmus_t *);
int collision_test(expelliarusmus_t *, player_t *);

extern
expelliarusmus_t * createexpelliarusmus(player_t * player){

    expelliarusmus_t * spell = malloc(sizeof(expelliarusmus_t));

    strcpy(spell->name, "Expelliarusmus");
    spell->speed = 1;
    spell->damage = 10;
    spell->pos_x = player->pos_x;
    spell->pos_y = player->pos_y;
    spell->width = 10;
    spell->heihgt = 10;
    spell->sender = player->id_player;

    spell->sprite = NULL;

    spell->deplacement = deplacement;
    spell->display = display;
    spell->collision_test = collision_test;

}

static
void deplacement(expelliarusmus_t * spell, int dx, int dy){

    spell->pos_x += dx;
    spell->pos_y += dy;

}

static
void display(expelliarusmus_t * spell){

    //Hugo je te laisse faire ça

    //TU VEUX QUE TE DEMARRRRE

}

static 
int collision_test(expelliarmus_t * spell, player_t * player){

    if(((spell->pos_x + spell->width >= player->pos_x) && (spell->pos_x + spell->width <= player->width)) || ((spell->pos_x >= player->pos_x) && (spell->pos_x  <= player->width)))
        if(((spell->pos_y + spell->height >= player->pos_y) && (spell->pos_y + spell->height <= player->height + player->pos_y)) || ((spell->pos_y >= player->pos_y) && (spell->pos_y  <= player->pos_y + player->heihgt))){
            player->pt_life -= spell->damamge;

        }
        //pouette
        //camion sexe

}

static
void destroy(expelliarmus_t ** spell){
    
}
//pouette