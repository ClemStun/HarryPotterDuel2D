#define NB_POT 3

#define FELICIS 123
#define POLYNECTAR 213
#define HEALING 132

int potions[NB_POT] = {FELICIS, POLYNECTAR, HEALING};
int potions_unlock[NB_POT] = {0};
char nomPotions[NB_POT][20] = {"Felix Felicis",
                               "Polynectar",
                               "Healing"};

extern t_etat potion_state(void);