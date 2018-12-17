#include "main.h"

int main()
{
  FILE *fichier = NULL;
  char *buffer = NULL;

  fichier = ouvrir_fichier("BDD.csv");

  if(fichier != NULL)
  {
    printf("Talle fichier : %d octet(s)\r\n", taille_fichier(fichier));

    lire_fichier(buffer, fichier);

    for(int i=0; i<5; i++)
    {
      printf("%c", buffer[i]);
    }

    fermer_fichier(fichier);
  }
}
