#ifndef STAT_H
#define STAT_H

#include <stdio.h>
#include <stdlib.h>
#include "../../Src/main.h"

void nb_crash_year(TypeDef_Crash *, int );
void crash_location(TypeDef_Crash *, int, int *, TypeDef_Crash *);
int moyenne_crash_year(TypeDef_Crash *Crashs, int nb_crash);
int nb_passenger(TypeDef_Crash *Crashs, int nb_crash);
void survivants_crash(TypeDef_Crash *Crashs, int nb_crash, int);
void crash_location_struct(TypeDef_Crash *, TypeDef_Crash *, int, char [20] );





#endif
