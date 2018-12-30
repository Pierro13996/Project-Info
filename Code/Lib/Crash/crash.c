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
    free(buffer_date);
  }
  else
  {
    DateStruct.tm_year = 0 - 1900;//On convertit notre chaîne en un nombre décimal
    DateStruct.tm_mon = 0 - 1;
    DateStruct.tm_mday = 0;
    (*position)++;
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
    memset(buffer_heure, '\0', longeur);
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
    memset(buffer_heure, '\0', longeur);
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

int lire_int(char *buffer, int *position, char fin_chaine)//Convertit une chaîne en entier
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

void lire_chaine(char *buffer, char *chaine, int *position, char fin_chaine)//Lis une chaîne
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

int compte_elements(char *buffer, int taille)//Compte le nombre de crashs
{
  int nb_elements = 0;

  for(int i = 0; i<taille; i++)
  {
    if(*(buffer+i) == '\n')nb_elements++;//Dès qu'il y a un saut de ligne on incrémente le nombre d'éléments
  }
  return nb_elements-1;//-1 parce qu'il y a le titre des colonnes
}

void stocker_crashs(char *buffer, TypeDef_Crash *Crashs, int nb_crash)//Stocke les crashs sous forme de tableau de structures
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

void afficher_un_crash(TypeDef_Crash *Crashs, int element) // Afficher un seul crash (Pour le tri)
{
    char date[30];
    char heure[10];
    char morts_vol[50];
    char morts_sol[100];
    char rapport[SIZEOF_RAPPORT];


    //Formattage du texte
    if((Crashs+element)->Date.tm_hour != -1)
    {
      strftime(heure,10," à %H:%M", &(Crashs+element)->Date);
    }
    else sprintf(heure, "");

    if((Crashs+element)->Morts > 0)
    {
      sprintf(morts_vol,"Sur %d Passager(s), %d personne(s) décédé(e)-s."
      ,(Crashs+element)->Passagers, (Crashs+element)->Morts);
    }
    else sprintf(morts_vol, "");

    if((Crashs+element)->Sol > 0)
    {
      sprintf(morts_sol, "%d personnes ont perdu la vie au sol, %d personnes on survécu en tout."
      , (Crashs+element)->Sol, (Crashs+element)->Survivants);
    }
    else
    if((Crashs+element)->Survivants > 0)
    {
      sprintf(morts_sol, "%d personnes on survécu en tout.", (Crashs+element)->Survivants);
    }
    else sprintf(morts_sol, "");


    //Affichage du texte
    printf("Crash n°%d :\r\n\n",(Crashs+element)->Id);

    strftime(date,30,"%d %B %Y", &(Crashs+element)->Date);
    printf("Le %s%s à %s en direction de %s.\r\n"
    , date, heure, (Crashs+element)->Lieu, (Crashs+element)->Route);
    printf("Responsable : %s en %s immatriculé %s avec le numéro de vol %d.\r\n\n"
    , (Crashs+element)->Operator, (Crashs+element)->Type, (Crashs+element)->Registration, (Crashs+element)->Num_Vol);

    printf("Cause du crash : '%s'.\r\n\n", (Crashs+element)->Classification);

    printf("%s\r\n", morts_vol);
    printf("%s\r\n\n", morts_sol);

    printf("Rapport :\r\n%s\r\n", (Crashs+element)->Rapport);
}

void afficher_crashs(TypeDef_Crash *Crashs, int nb_crash)//Affiche l'ensemble des crashs du tableau de structures
{
  int element = 0;

  while(element < nb_crash)//Tant qu'il y a un crash à lire on stocke les infos dans Crashs[element] (element étant la case du tableau de type 'TypeDef_Crash')
  {
    printf("\r\n");
    afficher_un_crash(Crashs, element);
    printf("_______________________________________________________________________________________");
    printf("\r\n");
    element++;
  }
}
