#include "stat.h"



int nb_crash_year(TypeDef_Crash *Crashs, int *nb_crash, int *year)
{
int nbcrash =0;
{
for(int i=0; i<=nb_crash; i++)
{
    if (Crashs[i].Annee==year) nbcrash++;
}
}
    return nbcrash;
}

