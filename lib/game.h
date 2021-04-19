/**
 * \file game.h
 * \brief Header de game.c.
 * \author COUTANT Hugo & COMTE Clément
 * \version 1
 * \date 17 avril 2021
 *
 */

extern t_etat game_state(window *win, images_t * images, text_t * text, player_t * monPerso, player_t * j2, TTF_Font *font, int socketClient, socket_t *j1);
