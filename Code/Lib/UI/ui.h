#ifndef STAT_H
#define STAT_H

#include <stdio.h>
#include "../Crash/crash.h"

void ui_bienvenue(void);
void ui_menu(void);
void ui_bdd(TypeDef_Crash *Crashs,int nb_crash);//Menu Base de Données
void ui_statistiques(TypeDef_Crash *Crashs,int nb_crash);//Menu Statistiques

#endif
