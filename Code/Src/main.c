#include "main.h"

int main()
{
  FILE *fichier = NULL;
  char *buffer = NULL;
  long taille = 0;

  fichier = ouvrir_fichier("BDD.csv");

  if(fichier != NULL)
  {
    printf("Talle fichier : %ld octet(s)\r\n", taille_fichier(fichier));

    taille = taille_fichier(fichier);
    buffer = (char*)malloc((sizeof(char)*taille));

    lire_fichier(buffer, fichier);

    if(buffer == NULL)
    {
      printf("(main.c) : Buffer == NULL !\r\n");
    }
    else printf("%s", buffer);

    fermer_fichier(fichier);
  }
}
