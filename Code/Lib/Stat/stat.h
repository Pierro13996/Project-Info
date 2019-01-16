#ifndef STAT_H
#define STAT_H

#include <stdio.h>
#include <stdlib.h>
#include "../../Src/main.h"

void crashs_annee(TypeDef_Crash *, int );
void nb_crashs_lieu(TypeDef_Crash *, int, int *, TypeDef_Crash *);
int moyenne_crashs_annee(TypeDef_Crash *Crashs, int nb_crash);
int nb_passager(TypeDef_Crash *Crashs, int nb_crash);
void survivants_crash(TypeDef_Crash *Crashs, int nb_crash, int);
void crash_location_struct(TypeDef_Crash *, TypeDef_Crash *, int, char [20] );
int nb_crashs_annee(TypeDef_Crash *Crashs, int nb_crash, int annee);
int annee_min(TypeDef_Crash *Crashs, int nb_crash);
int annee_max(TypeDef_Crash *Crashs, int nb_crash);

#endif
