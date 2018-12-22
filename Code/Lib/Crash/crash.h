#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#ifndef CRASH_H
#define CRASH_H

typedef struct TypeDef_Crash
{
  int    Id;
  time_t  Date;//On stocke la date sous forme time_t, on pourra jouer plus facilement avec !
  char    Lieu[100];
  char    Operator[80];
  long    Num_Vol;
  char    Route[50];
  char    Type[30];
  char    Registration[40];
  char    Cn_In[20];
  long    Passagers;
  long    Morts;
  long    Sol;
  char    Rapport[60];
  int     Annee;
  int     Survivants;
  char    Classification[100];
}TypeDef_Crash;

long compte_elements(char *buffer, int taille);//Renvoie le nombre de crashs
void stocker_crashs(char *buffer, TypeDef_Crash *Crashs, int nb_crash);//Stocke les crashs sous forme de tableau de structures

#endif
