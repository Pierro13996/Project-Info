#include "fichiers.h"

//OK
FILE *ouvrir_fichier(char *chemin)
{
  FILE *fichier = NULL;

  fichier = fopen(chemin, "r+");

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
  long taille = taille_fichier(fichier);

  if(fichier != NULL)
  {
    if(buffer != NULL)
    {
      fseek(fichier, 0, SEEK_SET);

      if(fread(buffer,sizeof(char),taille,fichier) == taille)
      {
        printf("(fichiers.c) Buffer rempli !\r\n");
      }
      else printf("(fichiers.c) Erreur : Lecture BDD.csv\r\n");
    }
    else printf("(fichiers.c) Buffer : NULL !\r\n");
  }
  else printf("(fichiers.c) Erreur : Lecture BDD.csv (fichier == NULL)\r\n");
}

long taille_fichier(FILE *fichier)
{
  long taille = 0;

  fseek(fichier, 0, SEEK_END);
  taille = ftell(fichier);
  return taille;
}
