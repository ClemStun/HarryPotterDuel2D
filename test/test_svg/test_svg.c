#include "../../lib/trait_donnees.h"


int main(int argc, char **argv) {
    images_t *images = NULL;
    cd_t *setSort = NULL;
    char data_storage[] = "./jeu_svg/";
    player_t * player;

    printf("\n-----------------Test de connexion avec un fichier deja creer ou creation d'un personnage-----------------\n\n");
    printf("Fichiers disponible a tester : Valable( et 2).hpb - Probleme( , 2, 3, 4, 5).hpb\n");
    player = accueil_connexion(images, setSort, data_storage);

    printf("\n\n\nPseudo : %s\nId de joueur : %i\nXp du joueur : %i\nLettre de la maison : %c\n\n", player->name, player->id_player, player->pt_xp, player->house);

    printf("-----------Deconnexion du joueur Valable---------------\n\n");
    accueil_deconnexion(player, data_storage);
    return 0;
}
