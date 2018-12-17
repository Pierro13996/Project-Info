#include "crash.h"

long compte_elements(char *buffer, long taille)
{
  long nb_elements = 0;

  for(long i = 0; i<taille; i++)
  {
    if(*(buffer+i) == '\n')nb_elements++;
  }
  return nb_elements-1;//-1 parce qu'il y a le titre des colonnes
}
