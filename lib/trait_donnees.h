/**
 * \file trait_donnees.h
 * \brief Header de trait_donnees.c.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "player.h"

extern player_t * accueil_connexion(images_t * images, cd_t setSort[], char fname[]);
extern void accueil_deconnexion(player_t * monPerso, char fname[]);
