#include "crash.h"

int longeur_element(char *buffer, int *position, char fin_chaine)//Retourne la longeur de la chaine jusqu'au séparateur
{
  int position_initiale = 0;
  int longeur = 0;

  position_initiale = *position;//On marque un repère

  if(*(buffer + *position) == '"')
  {
    //printf("On a des guillements, wtf\r\n");
    fin_chaine = '"';
    //printf("%c,", *(buffer + *position));
    while(*(buffer + *position) != fin_chaine) (*position)++;//On incrémente tant qu'un séparateur n'a pas été vu
    (*position)++;
  }
  else
  {
    //printf("On n'a pas de guillements\r\n");
    while(*(buffer + *position) != fin_chaine)
    {
      //printf("%c,", *(buffer + *position));
      (*position)++;
    }
  }

  longeur = *position - position_initiale;

  *position = position_initiale;

  return longeur;
}

struct tm lire_date(char *buffer, int *position, char fin_chaine)//[C'est moins compliqué que ça en a l'air ~(°u°~)] Renvoie la date
{
  int position_initiale = 0;
  int longeur = 0;
  char *buffer_date = NULL;
  char *buffer_heure = NULL;
  struct tm DateStruct;
  time_t date;

  longeur = longeur_element(buffer, position, fin_chaine);
  if(longeur > 0)
  {
    buffer_date = malloc( longeur * sizeof(char)+1);//On alloue la mémoire nécessaire au stockage + un espace pour le '\0' (fin de chaîne)

    if(buffer_date == NULL)//Si la mémoire n'a pas étée alouée, on renvoie une erreur à l'utilisateur
    {
      printf("Erreur (lire_date) : Allocation memoire impossible\r\n");
      exit(1);
    }

    //Année
    memset(buffer_date, '\0', longeur);
    position_initiale = *position;//On marque un repère
    while(*(buffer + *position) != '-')//Tant qu'il n'y a pas le séparateur on stocke nos données dans le buffer temporaire "buffer_date"
    {
      *(buffer_date + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_date + (*position - position_initiale)) = '\0';//On marque bien la fin de notre chaîne par un '\0'
    DateStruct.tm_year = atoi(buffer_date) - 1900;//On convertit notre chaîne en un nombre décimal
    printf("Année : %s\r\n", buffer_date);

    //Mois
    memset(buffer_date, '\0', longeur);
    position_initiale = *position;
    while(*(buffer + *position) != '-')
    {
      *(buffer_date + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_date + (*position - position_initiale)) = '\0';
    DateStruct.tm_mon = atoi(buffer_date) - 1;
    printf("Mois : %s\r\n", buffer_date);

    //Jour
    memset(buffer_date, '\0', longeur);
    position_initiale = *position;
    while(*(buffer + *position) != fin_chaine)
    {
      *(buffer_date + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_date + (*position - position_initiale)) = '\0';
    DateStruct.tm_mday = atoi(buffer_date);
    printf("Jour : %s\r\n", buffer_date);
    free(buffer_date);
  }
  else
  {
    DateStruct.tm_year = 0 - 1900;//On convertit notre chaîne en un nombre décimal
    DateStruct.tm_mon = 0 - 1;
    DateStruct.tm_mday = 0;
  }

  longeur = longeur_element(buffer, position, fin_chaine);
  if(longeur > 0)
  {
    buffer_heure = malloc( longeur * sizeof(char)+1);

    if(buffer_heure == NULL)
    {
      printf("Erreur (lire_date) : Allocation memoire impossible\r\n");
      exit(1);
    }

    //Heure
    memset(buffer_date, '\0', longeur);
    position_initiale = *position;
    while(*(buffer + *position) != ':')
    {
      *(buffer_heure + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_heure + (*position - position_initiale)) = '\0';
    printf("Heure : %s\r\n", buffer_heure);
    DateStruct.tm_hour = atoi(buffer_heure) - 1;


    //Minute
    memset(buffer_date, '\0', longeur);
    position_initiale = *position;
    while(*(buffer + *position) != fin_chaine)
    {
      *(buffer_heure + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_heure + (*position - position_initiale)) = '\0';
    printf("Minute : %s\r\n", buffer_heure);
    DateStruct.tm_min = atoi(buffer_heure);

    DateStruct.tm_sec = 0;
    DateStruct.tm_isdst = -1;

    free(buffer_heure);
  }
  else
  {
    DateStruct.tm_hour = 0 - 1;
    DateStruct.tm_min = 0;
    DateStruct.tm_sec = 0;
    DateStruct.tm_isdst = -1;
  }

  //date = mktime(&DateStruct);//Convertit la structure "DateStruct" en variable temporelle facile à manipuler et la renvoie
  return DateStruct;
}

int lire_int(char *buffer, int *position, char fin_chaine)//Renvoie un long
{
  int position_initiale = 0;
  int variable = 0;
  int longeur = 0;
  char *buffer_long = NULL;

  //printf("Positiion (lire int avant 'longeur_element') : %d\r\n", *position);
  longeur = longeur_element(buffer, position, fin_chaine);
  //printf("Positiion (lire int après 'longeur_element') : %d\r\n", *position);
  if(longeur > 0)
  {
    buffer_long = malloc( longeur * sizeof(char)+1);//On alloue la mémoire nécessaire au stockage + un espace pour le '\0' (fin de chaîne)

    if(buffer_long == NULL)//Si la mémoire n'a pas étée alouée, on renvoie une erreur à l'utilisateur
    {
      printf("Erreur (lire_int) : Allocation memoire impossible\r\n");
      exit(1);
    }

    position_initiale = *position;
    while(*(buffer + *position) != fin_chaine)//Tant qu'il n'y a pas le séparateur on stocke nos données dans le buffer temporaire "buffer_date"
    {
      *(buffer_long + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_long + (*position - position_initiale)) = '\0';//On marque bien la fin de notre chaîne par un '\0'
    printf("Valeur str ID : %s\r\n", buffer_long);
    variable = atoi(buffer_long);

    free(buffer_long);//On libère la mémoire prise par "buffer_long"
  }
  else
  {
    variable = 0;
  }
  return variable;
}

void lire_chaine(char *buffer, char *chaine, int *position, char fin_chaine)
{
  long longeur, i, position_initiale = 0;

  position_initiale = *position;

  longeur = longeur_element(buffer, position, fin_chaine);

  if(longeur > 0)
  {
    while( (*position - position_initiale)<longeur)
    {
      if(*(buffer + *position) != '"')
      {
        i++;
      }
      *(chaine + i) = *(buffer + *position);
      i++;
      position++;
    }
  }
  else
  {
    *chaine = '\0';
  }
}

int compte_elements(char *buffer, int taille)
{
  int nb_elements = 0;

  for(int i = 0; i<taille; i++)
  {
    if(*(buffer+i) == '\n')nb_elements++;//Dès qu'il y a un saut de ligne on incrémente le nombre d'éléments
  }
  return nb_elements-1;//-1 parce qu'il y a le titre des colonnes
}

void stocker_crashs(char *buffer, TypeDef_Crash *Crashs, int nb_crash)
{
  int position = 0;
  int element = 0;
  char date[30];

  while(*(buffer+position) != '\n')
  {
    printf("%c", *(buffer+position));
    position++;//On saute la première ligne (parce qu'il y a le titre des colonnes, je tiens à le rappeler)
  }
  position++;//Et on saute le '\n'

  nb_crash = 1;

  printf("\r\nPosition : %d\r\n", position);

  while(element < nb_crash)//Tant qu'il y a un crash à lire on stocke les infos dans Crashs[element] (element étant la case du tableau de type 'TypeDef_Crash')
  {
    (Crashs+element)->Id = lire_int(buffer, &position, ',');
    printf("Id[%d] : %d, position : %d\r\n",element, (Crashs+element)->Id, position);
    (Crashs+element)->Date = lire_date(buffer, &position, ',');
    strftime(date,30,"%x %X", &(Crashs+element)->Date);
    printf("Date[%d] : %s, position : %d\r\n",element, date, position);
    lire_chaine(buffer, (Crashs+element)->Lieu, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Operator, &position, ',');
    (Crashs+element)->Num_Vol = lire_int(buffer, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Route, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Type, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Registration, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Cn_In, &position, ',');
    (Crashs+element)->Passagers = lire_int(buffer, &position, ',');
    (Crashs+element)->Morts = lire_int(buffer, &position, ',');
    (Crashs+element)->Sol = lire_int(buffer, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Rapport, &position, ',');
    (Crashs+element)->Annee = lire_int(buffer, &position, ',');
    (Crashs+element)->Survivants = lire_int(buffer, &position, ',');
    lire_chaine(buffer, (Crashs+element)->Classification, &position, '\n');

    element++;
  }
}
