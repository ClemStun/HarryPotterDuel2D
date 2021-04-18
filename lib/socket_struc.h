/**
 * \file socket_struc.h
 * \brief Structure envoyé par les clients au serveur
 * \author COLLET Matthieu
 * \version 1
 * \date 17 avril 2021
 *
 */

typedef struct socket_s{
    char pseudo[16];
    int x_click;
    int y_click;
    int sort;
    int quit;
}socket_t;
