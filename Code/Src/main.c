#include "main.h"

int main()
{
  FILE *fichier = NULL;

  fichier = ouvrir_fichier("BDD.csv");
  
  if(fichier == NULL)printf("NULL\r\n");

  printf("Talle fichier : %d octet(s)\r\n", taille_fichier(fichier));

  fclose(fichier);
}
