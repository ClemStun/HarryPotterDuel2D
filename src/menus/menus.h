#include "../HUD/hud_ingame.h"

typedef enum{HOME, GAME} t_etat;

extern int game_state(window *win, images_t * images, player_t * monPerso, player_t * mannequin, sort_t ** sort, const Uint8 *keyboard_state_array);
extern int home_state(window *win, images_t * images, text_t * text, player_t * monPerso, TTF_Font *font);
extern void createButton(window *win, text_t * text, int posX, int posY, int rectW, int rectH, const char *texte, TTF_Font *fontButton, const char color);
int zone_detect(int x, int y, int w, int h, int mouseX, int mouseY);
