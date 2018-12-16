#include "fichiers.h"

FILE* ouvrir_fichier(char *chemin)
{
  FILE *fichier = NULL;

  fichier = fopen(chemin, "a");

  if(fichier == NULL)printf("Ouverture impossible...\r\n");
  else printf("Fichier ouvert !\r\n");

  return fichier;
}

int fermer_fichier(FILE *fichier)
{
  int status = 0;

  status = fclose(fichier);

  if(status == 0)printf("Fermeture impossible...\r\n");
  else printf("Fichier fermé !\r\n");

  return status;
}

void lire_fichier(char *buffer)
{

}
