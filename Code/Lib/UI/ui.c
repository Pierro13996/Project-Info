#include "ui.h"

void ui_bienvenue(void)
{
  printf(" -------------- Bienvenue dans l'application TryToSurvive ------------- \n");
  printf("\n\n\n\n\n\nAppuyez sur ENTER\r\n");
  while(getchar()!='\n');
}

void ui_menu(void)
{
  printf(
  "MENU\r\n\n"

  "1. Base de données\r\n"
  "2. Statistiques\r\n\n"

  "0. Quitter\r\n");
}

void ui_bdd(TypeDef_Crash *Crashs,int nb_crash)
{
  int choix;//Choix Menu
  int id_crash;//ID Crash

  do
  {
    system("clear");

    printf(
      "BASE DE DONNEES\r\n\n"

      "1. Afficher Base de données\r\n"
      "2. Afficher un Elément\r\n\n"

      "0. Retour au Menu\r\n");

    scanf("%d", &choix);

    switch (choix)
    {
        case 1:
        system("clear");
        afficher_crashs(Crashs,nb_crash);
        printf("\n\nAppuyez sur ENTRER\r\n");
        while(getchar()!='\n');
        break;


        case 2:
        do{
          system("clear");
          printf(
            "AFFICHER UN ELEMENT\r\n\n"
            "Afficher crash n°(0 - %d): ", nb_crash-1);

          scanf("%d", &id_crash);
        }while((id_crash >= nb_crash) || (id_crash < 0));

        system("clear");
        afficher_un_crash(Crashs, id_crash);

        while(getchar()!='\n');

        printf("\n\nAppuyez sur ENTRER\r\n");
        while(getchar()!='\n');
        break;


        default:
        printf("Mauvais choix\r\n");
        break;
    }
  } while(choix!=0);
}

void ui_statistiques(TypeDef_Crash *Crashs,int nb_crash)
{

}
