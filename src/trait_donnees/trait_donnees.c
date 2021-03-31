#include "../../lib/trait_donnees.h"

static
void load_data(player_t ** monPerso, images_t * images, cd_t setSort[]){
    FILE * fichier;
    char pseudo[20];
    char fname[25] = "./svg/";
    char cherche[40];
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
        fscanf(fichier, "%i", &id);
        fscanf(fichier, "%i", &xp);

        *monPerso = createPlayer(id, pseudo, xp, searchTexture(images, pseudo), setSort, 200, 250);
    }
    fclose(fichier);
}

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

    fprintf(fichier, "%s : %i : %i", monPerso->name, monPerso->id_player, monPerso->pt_xp);
    //potion peut etre a venir

    fclose(fichier);
}

extern
player_t * accueil_connexion(images_t * images, cd_t setSort[]){
    int choix;
    char pseudo[20];

    player_t * monPerso;

    printf("Voulez-vous vous connecter à un personnage existant ou en créer un nouveau ?\n");
    printf("\t1- Connexion à un personnage existant.\n");
    printf("\t2- Création d'un nouveau personnage.\n");

    do{
        printf("Saisissez 1 ou 2 : ");
        scanf("%i", &choix);
    }while(choix != 1 && choix != 2);

    switch (choix) {
        case 1:
            load_data(&monPerso, images, setSort);
        break;
        case 2:
            printf("\nQuel est le pseudo de votre personnage : ");
            scanf("%s", pseudo);

            monPerso = createPlayer(1, pseudo, 0, searchTexture(images, pseudo), setSort, 200, 250);
        break;
    }

    return monPerso;
}

extern
void accueil_deconnexion(player_t * monPerso){
    int choix;

    printf("Voulez vous sauvegarder votre avancement de personnage ?\n");
    printf("\t1- Sauvegarder et quitter.\n");
    printf("\t2- Quitter sans sauvegarder.\n");

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
