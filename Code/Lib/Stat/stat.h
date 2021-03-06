#ifndef STAT_H
#define STAT_H

#include <stdio.h>
#include <stdlib.h>
#include "../../Src/main.h"
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_statistics_double.h>
#include <math.h>

#define PREDICTION_CRASH      ((int)1)
#define PREDICTION_VICTIMES   ((int)2)

void crashs_annee(TypeDef_Crash *Crashs, int nb_crash);
void nb_crashs_lieu(TypeDef_Crash *, int, int *, TypeDef_Crash *);
int moyenne_crashs_annee(TypeDef_Crash *Crashs, int nb_crash);
int nb_passager(TypeDef_Crash *Crashs, int nb_crash);
void survivants_crash(TypeDef_Crash *Crashs, int nb_crash, int);
void crash_location_struct(TypeDef_Crash *, TypeDef_Crash *, int, char [20] );
int nb_crashs_annee(TypeDef_Crash *Crashs, int nb_crash, int annee);
int annee_min(TypeDef_Crash *Crashs, int nb_crash);
int annee_max(TypeDef_Crash *Crashs, int nb_crash);
void regression_polynomiale(int nb_donnees, int degre, double *dx, double *dy, double *resultat);//Renvoie le facteur de correlation
double prediction(TypeDef_Crash *Crashs, int nb_crash, int type_prediction);

#endif
