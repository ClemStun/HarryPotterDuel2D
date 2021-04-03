/**
 * \file menu.h
 * \brief Header de menu.c.
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

extern void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color);
extern int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY);
extern t_etat home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font);
