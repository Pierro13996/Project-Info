#include "stat.h"
#include "string.h"


void nb_crash_year(TypeDef_Crash *Crashs, int nb_crash)
{
    int year=0;
    printf(" Pour quelle année ? \n");
    scanf("%d", &year);

    int n=0;
    for(int i=0; i<=nb_crash; i++)
    {
        if (Crashs[i].Annee==year) n++;
    }
    printf("Il y'a eu %d crashs d'avions en %d \n", n, year);

    char choix[4];
    printf("Voulez-vous les afficher ? OUI/NON \n");
    scanf("%s", choix);
    if (strcmp("OUI", choix)==0)
    {
   for(int i=0; i<=nb_crash; i++)
    {
        if (Crashs[i].Annee==year) 
        afficher_un_crash(Crashs, i);
    }
    }
    
}

