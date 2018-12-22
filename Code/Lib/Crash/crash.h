#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

#ifndef CRASH_H
#define CRASH_H

typedef struct TypeDef_Crash
{
  int Id;
  struct tm Date;//On stocke la date sous forme time_t, on pourra jouer plus facilement avec !
  char Lieu[40];
  char Operator[800];
  int Num_Vol;
  char Route[20];
  char Type[30];
  char Registration[40];
  char Cn_In[200];
  int Passagers;
  int Morts;
  int Sol;
  char Rapport[1000];
  int Annee;
  int Survivants;
  char Classification[50];
}TypeDef_Crash;

int compte_elements(char *buffer, int taille);//Renvoie le nombre de crashs
void stocker_crashs(char *buffer, TypeDef_Crash *Crashs, int nb_crash);//Stocke les crashs sous forme de tableau de structures
void afficher_crashs(TypeDef_Crash *Crashs, int nb_crash);

#endif
