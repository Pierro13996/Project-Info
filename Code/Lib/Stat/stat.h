#ifndef STAT_H
#define STAT_H

#include <stdio.h>
#include <stdlib.h>
#include "../../Src/main.h"

void nb_crash_year(TypeDef_Crash *, int );
void crash_location(TypeDef_Crash *, int);
TypeDef_Crash crash_location2(TypeDef_Crash *Crashs, int nb_crash, char* location);
int moyenne_crash_year(TypeDef_Crash *Crashs, int nb_crash);
int nb_passenger(TypeDef_Crash *Crashs, int nb_crash);
void crash_survivor(TypeDef_Crash *Crashs, int nb_crash, int);




#endif