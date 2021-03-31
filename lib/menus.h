/**
 * \file menus.h
 * \brief Header commun aux différents status du jeu
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */


#include "hud_ingame.h"

/**
 * \enum t_etat;
 * \brief Enumération des différents états du jeu
 * 
 */
typedef enum{QUIT, HOME, GAME, TRAINING, WAITING, OTHER} t_etat;
SDL_Event event;

#include "menu.h"
#include "game.h"
#include "train.h"
#include "waiting.h"

