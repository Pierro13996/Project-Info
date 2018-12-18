#include "crash.h"

long compte_elements(char *buffer, long taille)
{
  long nb_elements = 0;

  for(long i = 0; i<taille; i++)
  {
    if(*(buffer+i) == '\n')nb_elements++;//Dès qu'il y a un saut de ligne on incrémente le nombre d'éléments
  }
  return nb_elements-1;//-1 parce qu'il y a le titre des colonnes
}

//EN COUUUUUUUUUUUURS
void stocker_crashs(char *buffer, TypeDef_Crash *Crashs, long nb_crash)
{
  long i, element = 0;
  char *buffer2 = NULL;

  while(*(buffer+i) != '\n') i++;//On saute la première ligne (parce qu'il y a le titre des colonnes, je tiens à le rappeler)

  while(element < nb_crash)//Tant qu'il y a un crash à lire
  {
    //routine de lecture : ID, Date
    Crashs[element].id = element;//Stocke l'ID

    element++;
  }
}
