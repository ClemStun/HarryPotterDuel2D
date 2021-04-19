/**
 * \file potions.h
 * \brief Header du fichier potion.c
 * \author COMTE Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

#define NB_POT 3
#define NB_IN 3

#define FELICIS 123
#define POLYNECTAR 213
#define HEALING 132

char ingredients[NB_IN][20] = {"Asphodele", "Ecrain de licorne", "Mandragore"};

int potions[NB_POT] = {FELICIS, POLYNECTAR, HEALING};
int potions_unlock[NB_POT] = {0};
char nomPotions[NB_POT][20] = {"Felix Felicis",
                               "Polynectar",
                               "Healing"};

extern t_etat potion_state(window *win, player_t *monPerso, text_t * text, TTF_Font *font);
