#include "fichiers.h"

FILE* ouvrir_fichier(char *chemin)
{
  FILE * fichier;

  fichier = fopen(chemin, "a");

  return fichier;
}

void fermer_fichier(void)
{

}

void lire_fichier(char *buffer)
{

}
