/**
 * \file menus.h
 * \brief Header de menus.c.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "hud_ingame.h"

typedef enum{QUIT, HOME, GAME, TRAINING, WAITING, OTHER} t_etat;

extern t_etat game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort);
extern t_etat home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font);
extern t_etat training_state(window *win, images_t * images, text_t * text, player_t * monPerso, player_t * mannequin, sort_t ** sort, TTF_Font *font);
extern t_etat waiting_state(window *win, text_t * text, TTF_Font *font);
extern void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color);
