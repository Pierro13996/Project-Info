#include "crash.h"

time_t lire_date(char *buffer, long *position)//C'est moins compliqué que ça en a l'air ~(°u°~)
{
  long position_initiale = 0;
  char *buffer_date = NULL;
  char *buffer_heure = NULL;

  position_initiale = *position;//On marque un repère

  while(*buffer + *position != ',')*position++;//On incrémente tant qu'un séparateur n'a pas été vu

  buffer_date = malloc( (*position - position_initiale) * sizeof(char)+1);//On alloue la mémoire nécessaire au stockage + un espace pour le '\0' (fin de chaîne)

  if(buffer_date == NULL)//Si la mémoire n'a pas étée alouée, on renvoie une erreur à l'utilisateur
  {
    printf("Erreur (lire_date) : Allocation memoire impossible\r\n");
    exit(1);
  }
  *position = position_initiale;//On se remet au début de l'info !


  //Année
  position_initiale = *position;//On marque un repère
  while(*(buffer + *position) != '-')//Tant qu'il n'y a pas le séparateur on stocke nos données dans le buffer temporaire "buffer_date"
  {
    *(buffer_date + (*position - position_initiale)) = *(buffer+position);
    *position++;
  }
  *position++;
  *(buffer_date + (*positon - position_initiale)) = '\0';//On marque bien la fin de notre chaîne par un '\0'
  DateStruct.tm_year = atoi(buffer_date) - 1900;//On convertit notre chaîne en un nombre décimal


  //Mois
  position_initiale = *position;
  while(*(buffer + *position) != '-')
  {
    *(buffer_date + (*position - position_initiale)) = *(buffer+position);
    *position++;
  }
  *position++;
  *(buffer_date + (*positon - position_initiale)) = '\0';
  DateStruct.tm_mon = atoi(buffer_date) - 1;


  //Jour
  position_initiale = *position;
  while(*(buffer + *position) != ',')
  {
    *(buffer_date + (*position - position_initiale)) = *(buffer+position);
    *position++;
  }
  *position++;
  *(buffer_date + (*positon - position_initiale)) = '\0';
  DateStruct.tm_mday = atoi(buffer_date);

  free(buffer_date);


  position_initiale = *position;

  while(*buffer + *position != ',')*position++;

  buffer_heure = malloc( (*position - position_initiale) * sizeof(char)+1);

  if(buffer_heure == NULL)
  {
    printf("Erreur (lire_date) : Allocation memoire impossible\r\n");
    exit(1);
  }
  *position = position_initiale;

  //Heure
  position_initiale = *position;
  while(*(buffer + *position) != ':')
  {
    *(buffer_heure + (*position - position_initiale)) = *(buffer+position);
    *position++;
  }
  *position++;
  *(buffer_heure + (*positon - position_initiale)) = '\0';
  DateStruct.tm_hour = atoi(buffer_heure) - 1;


  //Minute
  position_initiale = *position;
  while(*(buffer + *position) != ',')
  {
    *(buffer_heure + (*position - position_initiale)) = *(buffer+position);
    *position++;
  }
  *position++;
  *(buffer_heure + (*positon - position_initiale)) = '\0';
  DateStruct.tm_min = atoi(buffer_heure);

  DateStruct.tm_sec = 0;
  DateStruct.tm_isdst = -1;

  free(buffer_heure);

  return (time_t)mktime(&DateStruct);//Convertit la structure "DateStruct" en variable temporelle facile à manipuler et la renvoie
}

void lire_lieu()
{

}

void lire_chaine()
{

}

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
      printf("Erreur (stocker_crashs) : Allocation memoire impossible\r\n");
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

    Crashs[element].date = lire_date(buffer, &i);

    element++;
  }
}
/*
Ecrire le code en dûr est trop long, il faut créer les fonctions suivantes :

-lire_date
-lire_lieu
-lire_chaîne
*/
