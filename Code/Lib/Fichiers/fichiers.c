#include "fichiers.h"

//OK
FILE *ouvrir_fichier(char *chemin)
{
  FILE *fichier = NULL;

  fichier = fopen(chemin, "a");

  if(fichier == NULL)printf("Ouverture impossible...\r\n");
  else printf("Fichier ouvert !\r\n");

  return fichier;
}

//OK
int fermer_fichier(FILE *fichier)
{
  int status = 0;

  status = fclose(fichier);

  if(status == 0)printf("Fichier fermé !\r\n");
  else printf("Fermeture impossible...\r\n");

  return status;
}

void lire_fichier(char *buffer, FILE *fichier)
{
  int taille = taille_fichier(fichier);

  buffer = (char*)malloc(sizeof(char)*taille);

  if(buffer != NULL)
  {
    fseek(fichier, 0, SEEK_SET);
    if(fread(buffer,1,taille,fichier) == taille)
    {
      printf("Buffer rempli !\r\n");
    }
    else printf("Erreur : Lecture BDD.csv\r\n");
  }
  else printf("Buffer : NULL !\r\n");
}

int taille_fichier(FILE *fichier)
{
  int taille = 0;

  fseek(fichier, 0, SEEK_END);
  taille = ftell(fichier);
  return taille;
}
