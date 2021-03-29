/**
 * \file hud_ingame.h
 * \brief Header de hud_ingame.c.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "move.h"

extern void update_hud_ingame(window * win, images_t * images, player_t * monPerso);
extern void update_hud_ingame_ennemie(window * win, images_t * images, text_t * text, player_t * ennemie, TTF_Font *font);
