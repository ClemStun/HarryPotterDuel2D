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
 * \param fname Chaine de caractere du fichier où se trouve les sauvegardes
 *
 */
static
void load_data(player_t ** monPerso, images_t * images, cd_t setSort[], char fname[]){
    FILE * fichier;
    char pseudo[20];
    char cherche[40];
    char data_storage[30];
    char house, car;
    int trouve = 0, id, xp, compte = 0;

    strcpy(data_storage, fname);

    printf("Quel est le pseudo du personnage à charger : ");
    scanf("%s", pseudo);

    strcat(data_storage, pseudo);
    strcat(data_storage, ".hpb");

    fichier = fopen(data_storage, "r");

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
        while(!feof(fichier)){
            fscanf(fichier, "%c", &car);
            if(car == ':') compte++;
        }

        if(compte != 3){
            printf("Nombre de champs trop élevé.\n");
            exit(4);
        }

        rewind(fichier);
        fscanf(fichier, "%s : %i : %i : %c", cherche, &id, &xp, &house);

        if(feof(fichier)) printf("fin de fichier\n");

        if(id < 0 || id > 100){
            printf("Id du joueur impossible, fichier corrompu.\n");
            exit(5);
        }
        if(xp < 0) xp = 0;

        if(searchTexture(images, pseudo) == NULL){
            *monPerso = createPlayer(id, pseudo, xp, searchTexture(images, "Mannequin.png"), setSort, 200, 250);
        }
        else{
            *monPerso = createPlayer(id, pseudo, xp, searchTexture(images, pseudo), setSort, 200, 250);
        }
        if(house != 'g' && house != 's' && house != 'r' && house != 'p' && house != 'n') house = 'n';
        (*monPerso)->house = house;
    }
    fclose(fichier);
}

/**
 * \fn static void save_data(player_t * monPerso)
 * \brief Fonction de sauvegarde de donnees dans un fichier.
 *
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage à sauvegarder.
 * \param fname Chaine de caractere du fichier où se trouve les sauvegardes.
 *
 */
static
void save_data(player_t * monPerso, char fname[]){
    FILE * fichier;
    char data_storage[30];

    strcpy(data_storage, fname);

    strcat(data_storage, monPerso->name);
    strcat(data_storage, ".hpb");

    fichier = fopen(data_storage, "w");

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

/**
 * \fn extern player_t * accueil_connexion(images_t * images, cd_t setSort[], char fname[])
 * \brief Fonction d'accueil de la connexion à un personnage sauvegardé ou création d'un personnage.
 *
 * \param images Pointeur sur une structure images_t, bibliothèque de textures des images.
 * \param setSort Tableau de sort d'un personnage.
 * \param fname Chaine de caractere du fichier où se trouve les sauvegardes.
 *
 * \return p Pointeur sur une structure player_s étant le nouveau personnage créé.
 */
extern
player_t * accueil_connexion(images_t * images, cd_t setSort[], char fname[]){
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
            load_data(&monPerso, images, setSort, fname);
        break;
        case 2:
            printf("\n\nQuel est le pseudo de votre personnage : ");
            scanf("%s", pseudo);

            if(strlen(pseudo) > 15){
                printf("Pseudo trop long.\n");
                exit(10);
            }
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

/**
 * \fn extern void accueil_deconnexion(player_t * monPerso, char fname[])
 * \brief Fonction d'accueil de la deconnexion du jeu avec le choix de sauvergarder ou non.
 *
 * \param monPerso Pointeur sur une structure player_t représentant les infos d'un personnage à sauvegarder.
 * \param fname Chaine de caractere du fichier où se trouve les sauvegardes.
 *
 */
extern
void accueil_deconnexion(player_t * monPerso, char fname[]){
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
            save_data(monPerso, fname);
            freePlayer(monPerso);
        break;
        case 2:
            freePlayer(monPerso);
        break;
    }
}
