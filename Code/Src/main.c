#include "main.h"

int main()
{
  FILE *fichier = NULL;

  ouvrir_fichier("BDD.csv", fichier);
  //fichier = fopen("BDD.csv", "a");
  if(fichier == NULL)printf("NULL\r\n");

  printf("Talle fichier : %d octet(s)\r\n", taille_fichier(fichier));

  fclose(fichier);
}
