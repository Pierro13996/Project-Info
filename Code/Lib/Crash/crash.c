#include "crash.h"

int longeur_element(char *buffer, int *position, char fin_chaine)//Retourne la longeur de la chaine jusqu'au séparateur
{
  int position_initiale = 0;
  int longeur = 0;
  char c = '\0';

  position_initiale = *position;//On marque un repère

  if(*(buffer + *position) == '"')//Si on a des guillements on prend tous les caractères just'au prochian guillements
  {
    (*position)++;
    c = '"';
    while(*(buffer + *position) != c) (*position)++;
    c = fin_chaine;
  }
  while(*(buffer + *position) != fin_chaine)(*position)++;

  longeur = *position - position_initiale;

  *position = position_initiale;//On remet notre position au repère

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
    position_initiale = *position;//On marque un repère
    while(*(buffer + *position) != '-')//Tant qu'il n'y a pas le séparateur on stocke nos données dans le buffer temporaire "buffer_date"
    {
      *(buffer_date + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_date + (*position - position_initiale)) = '\0';//On marque bien la fin de notre chaîne par un '\0'
    DateStruct.tm_year = atoi(buffer_date) - 1900;//On convertit notre chaîne en un nombre décimal

    //Mois
    position_initiale = *position;
    while(*(buffer + *position) != '-')
    {
      *(buffer_date + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_date + (*position - position_initiale)) = '\0';
    DateStruct.tm_mon = atoi(buffer_date);

    //Jour
    position_initiale = *position;
    while(*(buffer + *position) != fin_chaine)
    {
      *(buffer_date + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_date + (*position - position_initiale)) = '\0';
    DateStruct.tm_mday = atoi(buffer_date);
    free(buffer_date);
  }
  else
  {
    DateStruct.tm_year = 0 - 1900;//On convertit notre chaîne en un nombre décimal
    DateStruct.tm_mon = 0 - 1;
    DateStruct.tm_mday = 0;
    (*position)++;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    position_initiale = *position;
    if(*(buffer + *position + 2) != ':')*(buffer + *position) = ':';//Je dédicace cette ligne à l'indien qui a fait cettte BDD bancale
    while(*(buffer + *position) != ':')
    {
      *(buffer_heure + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_heure + (*position - position_initiale)) = '\0';
    DateStruct.tm_hour = atoi(buffer_heure) - 1;


    //Minute
    position_initiale = *position;
    while(*(buffer + *position) != fin_chaine)
    {
      *(buffer_heure + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    (*position)++;
    *(buffer_heure + (*position - position_initiale)) = '\0';
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
    (*position)++;
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
  //printf("longeur : %d\r\n", longeur);
  if(longeur > 0)
  {
    buffer_long = malloc( longeur * sizeof(char)+1);//On alloue la mémoire nécessaire au stockage + un espace pour le '\0' (fin de chaîne)

    if(buffer_long == NULL)//Si la mémoire n'a pas étée alouée, on renvoie une erreur à l'utilisateur
    {
      printf("Erreur (lire_int) : Allocation memoire impossible\r\n");
      exit(1);
    }

    position_initiale = *position;
    while((*(buffer + *position) != fin_chaine) && (*(buffer + *position) != '.'))//Tant qu'il n'y a pas le séparateur on stocke nos données dans le buffer temporaire "buffer_date"
    {
      *(buffer_long + (*position - position_initiale)) = *(buffer+*position);
      (*position)++;
    }
    if(*(buffer + *position) == '.')
    {
      while(*(buffer + *position) != fin_chaine)(*position)++;;
    }
    (*position)++;
    *(buffer_long + (*position - position_initiale)) = '\0';//On marque bien la fin de notre chaîne par un '\0'

    variable = atoi(buffer_long);

    free(buffer_long);//On libère la mémoire prise par "buffer_long"
  }
  else
  {
    variable = 0;
    (*position)++;
  }
  return variable;
}

void lire_chaine(char *buffer, char *chaine, int *position, char fin_chaine)
{
  int longeur = 0;
  int i = 0;
  int position_initiale = 0;

  position_initiale = *position;

  longeur = longeur_element(buffer, position, fin_chaine);

  if(longeur > 0)
  {
    while( (*position - position_initiale)<longeur)
    {
      if(*(buffer + *position) != '"')
      {
        *(chaine + i) = *(buffer + *position);
        i++;
      }
      (*position)++;
    }
    i++;
    *(chaine + i) = '\0';
  }
  else
  {
    *chaine = '\0';
  }
  (*position)++;
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

  while(*(buffer+position) != '\n')position++;//On saute la première ligne (parce qu'il y a le titre des colonnes, je tiens à le rappeler)
  position++;//Et on saute le '\n'

  while(element < nb_crash)//Tant qu'il y a un crash à lire on stocke les infos dans Crashs[element] (element étant la case du tableau de type 'TypeDef_Crash')
  {
    (Crashs+element)->Id = lire_int(buffer, &position, ',');
    (Crashs+element)->Date = lire_date(buffer, &position, ',');
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

void afficher_crashs(TypeDef_Crash *Crashs, int nb_crash)
{
  int element = 0;
  char date[30];

  while(element < nb_crash)//Tant qu'il y a un crash à lire on stocke les infos dans Crashs[element] (element étant la case du tableau de type 'TypeDef_Crash')
  {
    printf("Id[%d] : %d\r\n",element, (Crashs+element)->Id);
    strftime(date,30,"le %x à %X", &(Crashs+element)->Date);
    printf("Date[%d] : %s\r\n",element, date);
    printf("Lieu[%d] : %s\r\n",element, (Crashs+element)->Lieu);
    printf("Operator[%d] : %s\r\n",element, (Crashs+element)->Operator);
    printf("Numéro de vol[%d] : %d\r\n",element, (Crashs+element)->Num_Vol);
    printf("Route[%d] : %s\r\n",element, (Crashs+element)->Route);
    printf("Type[%d] : %s\r\n",element, (Crashs+element)->Type);
    printf("Registration[%d] : %s\r\n",element, (Crashs+element)->Registration);
    printf("CN/IN[%d] : %s\r\n",element, (Crashs+element)->Cn_In);
    printf("Passagers[%d] : %d\r\n",element, (Crashs+element)->Passagers);
    printf("Morts[%d] : %d\r\n",element, (Crashs+element)->Morts);
    printf("Sol[%d] : %d\r\n",element, (Crashs+element)->Sol);
    printf("Rapport[%d] : %s\r\n",element, (Crashs+element)->Rapport);
    printf("Annee[%d] : %d\r\n",element, (Crashs+element)->Annee);
    printf("Survivants[%d] : %d\r\n",element, (Crashs+element)->Survivants);
    printf("Classification[%d] : %s\r\n",element, (Crashs+element)->Classification);
    printf("\r\n");

    element++;
  }
}
