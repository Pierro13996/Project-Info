#include "fichiers.h"

//OK
void ouvrir_fichier(char *chemin, FILE *fichier)
{
  fichier = fopen(chemin, "a");

  if(fichier == NULL)printf("Ouverture impossible...\r\n");
  else printf("Fichier ouvert !\r\n");
}

//OK
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

int taille_fichier(FILE *fichier)
{
  int taille = 0;

  fseek(fichier, 0, SEEK_END);
  taille = ftell(fichier);
  return taille;
}
