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
  long i, j, element = 0;
  char *buffer2 = NULL;
  struct tm DateStruct;

  while(*(buffer+i) != '\n') i++;//On saute la première ligne (parce qu'il y a le titre des colonnes, je tiens à le rappeler)

  i++;

  while(element < nb_crash)//Tant qu'il y a un crash à lire
  {
    //_________________ID________________
    buffer2 = malloc(6*sizeof(char));
    if(buffer2 == NULL)
    {
      printf("Erreur (stocker_crashs) : Allocation mémoire impossible\r\n");
      exit(1);
    }

    while(*(buffer+i) != ',')//Tant qu'il n'y a pas le séparateur
    {
      *(buffer2 + j) = *(buffer+i);
      i++;
      j++;
    }

    i++;
    j++;

    *(buffer2 + j) = '\0';

    Crashs[element].id = atoi(buffer2);//Stocke l'ID

    free(buffer2);

    //_________________Date________________
    //2008-12-15
    buffer2 = malloc(6*sizeof(char));
    if(buffer2 == NULL)
    {
      printf("Erreur (stocker_crashs) : Allocation mémoire impossible\r\n");
      exit(1);
    }

    //Année
    j = 0;
    while(*(buffer+i) != '-')//Tant qu'il n'y a pas le séparateur
    {
      *(buffer2 + j) = *(buffer+i);
      i++;
      j++;
    }
    i++;
    j++;
    *(buffer2 + j) = '\0';
    DateStruct.tm_year = atoi(buffer2) - 1900;

    //Mois
    j = 0;
    while(*(buffer+i) != '-')//Tant qu'il n'y a pas le séparateur
    {
      *(buffer2 + j) = *(buffer+i);
      i++;
      j++;
    }
    i++;
    j++;
    *(buffer2 + j) = '\0';
    DateStruct.tm_mon = atoi(buffer2) - 1;

    //Jour
    j = 0;
    while(*(buffer+i) != ',')//Tant qu'il n'y a pas le séparateur
    {
      *(buffer2 + j) = *(buffer+i);
      i++;
      j++;
    }
    i++;
    j++;
    *(buffer2 + j) = '\0';
    DateStruct.tm_mday = atoi(buffer2);

    //Heure
    j = 0;
    while(*(buffer+i) != ':')//Tant qu'il n'y a pas le séparateur
    {
      *(buffer2 + j) = *(buffer+i);
      i++;
      j++;
    }
    i++;
    j++;
    *(buffer2 + j) = '\0';
    DateStruct.tm_hour = atoi(buffer2) - 1;

    //Minute
    j = 0;
    while(*(buffer+i) != ',')//Tant qu'il n'y a pas le séparateur
    {
      *(buffer2 + j) = *(buffer+i);
      i++;
      j++;
    }
    i++;
    j++;
    *(buffer2 + j) = '\0';
    DateStruct.tm_min = atoi(buffer2);

    DateStruct.tm_sec = 0;
    DateStruct.tm_isdst = -1;

    Crashs[element].date = mktime(&DateStruct);



    element++;
  }
}
/*
Ecrire le code en dûr est trop long, il faut créer les fonctions suivantes :

-lire_date
-lire_lieu
-lire_chaîne
*/
