/**
 * \file trait_donnees.c
 * \brief Fonction de chargement et sauvegarde de donnees
 * \author COUTANT Hugo
 * \version 0.1
 * \date 14 feb 2021
 *
 */

#include "../../lib/trait_donnees.h"

/**
 * \fn static void load_data(player_t ** monPerso, images_t * images, cd_t setSort[])
 * \brief Fonction de chargement de donnees à partir d'un fichier.
 *
 * \param monPerso Double pointeur sur une structure player_t représentant les infos d'un personnage.
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param setSort Tableau de sort d'un personnage.
 *
 */
static
void load_data(player_t ** monPerso, images_t * images, cd_t setSort[]){
    FILE * fichier;
    char pseudo[20];
    char fname[25] = "./svg/";
    char cherche[40];
    char house;
    int trouve = 0, id, xp;

    printf("Quel est le pseudo du personnage à charger : ");
    scanf("%s", pseudo);

    strcat(fname, pseudo);
    strcat(fname, ".hpb");

    fichier = fopen(fname, "r");

    if(fichier == NULL){
        printf("Impossible d'ouvrir le fichier de données.\n");
        exit(2);
    }

    fscanf(fichier, "%s", cherche);
    if(strcmp(cherche, pseudo) == 0)
        trouve = 1;

    if(feof(fichier) || !trouve){
        printf("Personnage non trouvé...\n");
        fclose(fichier);
        exit(3);
    }
    else{
        rewind(fichier);
        fscanf(fichier, "%s : %i : %i : %c", cherche, &id, &xp, &house);

        if(searchTexture(images, pseudo) == NULL){
            *monPerso = createPlayer(id, pseudo, xp, searchTexture(images, "Mannequin.png"), setSort, 200, 250);
        }
        else{
            *monPerso = createPlayer(id, pseudo, xp, searchTexture(images, pseudo), setSort, 200, 250);
        }
        (*monPerso)->house = house;
    }
    fclose(fichier);
}

/**
 * \fn static void save_data(player_t * monPerso)
 * \brief Fonction de sauvegarde de donnees dans un fichier.
 *
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage à sauvegarder.
 *
 */
static
void save_data(player_t * monPerso){
    FILE * fichier;
    char fname[25] = "./svg/";

    strcat(fname, monPerso->name);
    strcat(fname, ".hpb");

    fichier = fopen(fname, "w");

    if(fichier == NULL){
        printf("Impossible d'ouvrir le fichier de données.\n");
        exit(2);
    }

    if(monPerso == NULL)
        exit(4);

    fprintf(fichier, "%s : %i : %i : %c", monPerso->name, monPerso->id_player, monPerso->pt_xp, monPerso->house);
    //potion peut etre a venir

    fclose(fichier);
}

extern
player_t * accueil_connexion(images_t * images, cd_t setSort[]){
    int choix;
    char pseudo[20];

    player_t * monPerso;

    printf("\n\n\n\n\nVoulez-vous vous connecter à un personnage existant ou en créer un nouveau ?\n\n");
    printf("\t1- Connexion à un personnage existant.\n");
    printf("\t2- Création d'un nouveau personnage.\n");

    do{
        printf("\nSaisissez 1 ou 2 : ");
        scanf("%i", &choix);
    }while(choix != 1 && choix != 2);

    switch (choix) {
        case 1:
            load_data(&monPerso, images, setSort);
        break;
        case 2:
            printf("\n\nQuel est le pseudo de votre personnage : ");
            scanf("%s", pseudo);
            if(searchTexture(images, pseudo) == NULL){
                monPerso = createPlayer(1, pseudo, 0, searchTexture(images, "Mannequin.png"), setSort, 200, 250);
            }
            else{
                monPerso = createPlayer(1, pseudo, 0, searchTexture(images, pseudo), setSort, 200, 250);
            }
        break;
    }

    return monPerso;
}

extern
void accueil_deconnexion(player_t * monPerso){
    int choix;

    printf("\n\n\n\n\nVoulez vous sauvegarder votre avancement de personnage ?\n\n");
    printf("\t1- Sauvegarder et quitter.\n");
    printf("\t2- Quitter sans sauvegarder.\n\n");

    do{
        printf("Saisissez 1 ou 2 : ");
        scanf("%i", &choix);
    }while(choix != 1 && choix != 2);

    switch (choix) {
        case 1:
            save_data(monPerso);
            freePlayer(monPerso);
        break;
        case 2:
            freePlayer(monPerso);
        break;
    }
}
