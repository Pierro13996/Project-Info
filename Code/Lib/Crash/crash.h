#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "string.h"

#ifndef CRASH_H
#define CRASH_H

#define SIZEOF_LIEU 40
#define SIZEOF_OPERATOR 800
#define SIZEOF_ROUTE 20
#define SIZEOF_TYPE 40
#define SIZEOF_REGISRATION 40
#define SIZEOF_CN_IN 200
#define SIZEOF_RAPPORT 1000
#define SIZEOF_CLASSIFICATION 50

typedef struct TypeDef_Crash
{
  int Id;
  struct tm Date;//On stocke la date sous forme time_t, on pourra jouer plus facilement avec !
  char Lieu[SIZEOF_LIEU];
  char Operator[SIZEOF_OPERATOR];
  int Num_Vol;
  char Route[SIZEOF_ROUTE];
  char Type[SIZEOF_TYPE];
  char Registration[SIZEOF_REGISRATION];
  char Cn_In[SIZEOF_CN_IN];
  int Passagers;
  int Morts;
  int Sol;
  char Rapport[SIZEOF_RAPPORT];
  int Annee;
  int Survivants;
  char Classification[SIZEOF_CLASSIFICATION];
}TypeDef_Crash;

int compte_elements(char *buffer, int taille);//Renvoie le nombre de crashs
void stocker_crashs(char *buffer, TypeDef_Crash *Crashs, int nb_crash);//Stocke les crashs sous forme de tableau de structures
void afficher_crashs(TypeDef_Crash *Crashs, int nb_crash);
void afficher_un_crash(TypeDef_Crash *Crashs, int element);


#endif
