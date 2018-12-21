#include "main.h"

int main()
{
  FILE *fichier = NULL;
  char *buffer = NULL;
  TypeDef_Crash *Crashs = NULL;
  int taille, nb_crash = 0;

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

    Crashs = (TypeDef_Crash*)malloc(sizeof(TypeDef_Crash)*nb_crash);//On crée un tableau de structures de taille (nb_crash x taille_de_la_structure)

    if(Crashs != NULL)
    {
      stocker_crashs(buffer, Crashs, nb_crash);
    }
    else printf("Erreur (main) : Allocation memoire impossible\r\n");

    free(buffer);//Libère l'espace mémoire réservée au buffer
    free(Crashs);//Libère l'espace mémoire réservée aux Crashs
  }
}
