#include "main.h"

int main()
{
  FILE *fichier = NULL;

  fichier = ouvrir_fichier("BDD.csv");
  fclose(fichier);
}
