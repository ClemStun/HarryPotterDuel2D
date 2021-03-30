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
SDL_Event event;

#include "game.h"
#include "train.h"
#include "waiting.h"
#include "menu.h"

