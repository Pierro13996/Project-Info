#include "main.h"


int main()
{
  FILE *fichier = NULL;
  char *buffer = NULL;
  TypeDef_Crash *Crashs = NULL;
  TypeDef_Crash *Crash_Loc=NULL;
  int taille, nb_crash = 0;
  int nb_crash_loc=0;
  int choix=0;
  int moyenne=0;
  int passagers=0;

  fichier = ouvrir_fichier("BDD.csv");

  if(fichier != NULL)
  {
    printf("Taille fichier : %ld octet(s)\r\n", taille_fichier(fichier));

    taille = taille_fichier(fichier);//Renvoie la taille du fichier
    buffer = (char*)malloc((sizeof(char)*taille));//Alloue la mémoire du buffer en fontion de la taille de la BDD

    lire_fichier(buffer, fichier);//Replit le buffer des données de la BDD
    fermer_fichier(fichier);//Données récupérées, on ferme le fichier

    nb_crash =  compte_elements(buffer, taille);//Comptabilise le nombre de crashs

    printf("Il y a %d crashs dans le fichier...\r\n", nb_crash);
    
    //On crée un tableau de structures de taille (nb_crash x taille_de_la_structure)

    Crashs = (TypeDef_Crash*)malloc(sizeof(TypeDef_Crash)*nb_crash);//On crée un tableau de structures de taille (nb_crash x taille_de_la_structure)
    if(Crashs != NULL)
    {
      memset(Crashs, '\0', sizeof(TypeDef_Crash)*nb_crash);
      stocker_crashs(buffer, Crashs, nb_crash);
    }
    else printf("Erreur (main) : Allocation memoire impossible\r\n");

    free(buffer);//Libère l'espace mémoire réservée au buffer

    //On fait les stats ici !
    free(Crashs);//Libère l'espace mémoire réservée aux Crashs

    
  }
  do
    
    {
    printf(" -------------- Bienvenue dans l'application TryToSurvive ------------- \n");
    printf("\n \n                 MENU :\n");
    printf("    Appuyez sur : \n");
    printf("0 pour quitter \n");
    printf("1. Pour afficher l'ensemble des crashs d'avions depuis 1908 \n");
    printf("2. Pour afficher le nombre de crash pour une année choisie  \n");
    printf("3. Pour afficher  tous les crashs dans un pays \n");
    printf("4. Pour afficher la moyenne de crashs par an \n");
    printf("5. Pour afficher le nombre de passager impliqué dans des accidents \n");
    printf("6. Pour afficher le nombre de survivor (Personnes ayant survécu a un crash) \n");
    scanf("%d", &choix);

    switch (choix)
    {
        case 0:
        break;
        
        case 1:
        afficher_crashs(Crashs,nb_crash);
        break;

        case 2:
        nb_crash_year(Crashs,nb_crash);
        break;

        case 3:
        crash_location(Crashs, nb_crash, &nb_crash_loc, Crash_Loc);
        break;

        case 4:
        moyenne= moyenne_crash_year(Crashs, nb_crash);
        printf("Il y'a en moyenne %d crash par an \n", moyenne);
        break;

        case 5:
        passagers=nb_passenger(Crashs, nb_crash);
        printf("Il y a eu %d passagers impliqué dans des crashs \n", passagers);
        break;


        case 6:
        passagers=nb_passenger(Crashs, nb_crash);
        crash_survivor(Crashs, nb_crash, passagers);
        break;

        case 7:
        break;
 
        default: 
        printf("Mauvais choix");
        break;
    }
  }   while(choix!=0);

  return 0;
}
