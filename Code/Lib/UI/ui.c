#include "ui.h"

void ui_bienvenue(void)
{
  printf(" -------------- Bienvenue dans l'application TryToSurvive ------------- \n");
  printf("\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur ENTER\r\n");
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
        while(getchar()!='\n');
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
        while(getchar()!='\n');
        break;
    }
  } while(choix!=0);
}

void ui_statistiques(TypeDef_Crash *Crashs,int nb_crash)
{
  int choix;//Choix Menu
  int id_crash;//ID Crash

  double dx[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  double dy[11] = {1,  10,  49, 142, 313, 586, 985, 1534, 2257, 3178, 4321};
  double resultat[4];
  double facteur_correlation = 0;

  do
  {
    system("clear");

    printf(
      "STATISTIQUES\r\n\n"

      "1. Afficher le nombre de Crashs\r\n"
      "2. Afficher le nombre de Victimes\r\n\n"
      "3. Test regression polynomiale\r\n\n"

      "0. Retour au Menu\r\n");

    scanf("%d", &choix);

    switch (choix)
    {
        case 1:
        system("clear");
        printf(
          "AFFICHER NOMBRE CRASHS\r\n\n"
          "Nombre de crashs depuis %d : %d",annee_min(Crashs, nb_crash), nb_crash);
        while(getchar()!='\n');
        printf("\n\nAppuyez sur ENTRER\r\n");
        while(getchar()!='\n');
        break;


        case 2:
        system("clear");

        int victimes = 0;
        for(int i = 0; i<nb_crash; i++)
        {
          victimes += Crashs[i].Morts;
        }
        printf(
          "AFFICHER NOMBRE VICTIMES\r\n\n"
          "Il y a eu %d victimes depuis %d.", victimes, annee_min(Crashs, nb_crash));

        while(getchar()!='\n');
        printf("\n\nAppuyez sur ENTRER\r\n");
        while(getchar()!='\n');
        break;


        case 3:
        system("clear");

        printf("TEST REGRESSION POLYNOMIALE\r\n\n");

        facteur_correlation = regression_polynomiale(11, 4, dx, dy, resultat);

        for(int i=0; i<11; i++)printf("%f\t%f\r\n", dx[i], dy[i]);
        printf("\r\n%.f,%.f,%.f, %.f. r = %.f",resultat[0],resultat[1],resultat[2],resultat[3], facteur_correlation);

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
