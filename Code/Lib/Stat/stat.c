#include "stat.h"
#include "string.h"


void nb_crash_year(TypeDef_Crash *Crashs, int nb_crash) //Tri Crash par année
{
    int year=0;
    printf(" Pour quelle année ? \n");
    scanf("%d", &year);

    int n=0;
    for(int i=0; i<nb_crash; i++)
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

void crash_location(TypeDef_Crash *Crashs,int nb_crash, int *nb_crash_loc,TypeDef_Crash *crashloc) //Fonction tri crash par pays
{
    char location[20];
    char *ret=NULL;

    printf("De quels pays voulez-vous afficher les Crashs ? (nom du pays en anglais ex : Spain, India,...) \n");
    scanf("%s", location);
    for (int i=0; i<nb_crash; i++)
    {
        ret=strstr(Crashs[i].Lieu, location); // Compare si la chaine Crashs[i].Lieu contient le lieu
        if (ret!=NULL)  //Si elle le contient
        (*nb_crash_loc)++;
    }
    printf("Il y'a eu %d crashs d'avions dans le pays  %s \n",  *nb_crash_loc, location);

    crash_location_struct(Crashs, crashloc, nb_crash, location);

    char choix[4];

    printf("Voulez-vous les afficher ? OUI/NON \n");
    scanf("%s", choix);
    if (strcmp("OUI", choix)==0)
    {
        afficher_crashs(crashloc, *nb_crash_loc);
    }
}

int moyenne_crash_year(TypeDef_Crash *Crashs, int nb_crash)
{
    int annee=0;
    int moy=0;
    annee = Crashs[nb_crash-1].Annee - Crashs[0].Annee;
    moy = nb_crash/annee ;
    return moy;
}

int nb_passenger(TypeDef_Crash *Crashs, int nb_crash)
{
    int nb=0;
    for (int i=0; i<nb_crash; i++) nb=nb+Crashs[i].Passagers;
    return nb;
}

void crash_survivor(TypeDef_Crash *Crashs, int nb_crash, int nb_passager)
{
    int nbsurvivor=0;
    for (int i=0; i<nb_crash; i++)
    {
        if(Crashs[i].Survivants>=1) nbsurvivor++;
    }
    printf("Sur %d passagers il y a eu %d survivant \n", nb_passager, nbsurvivor);
}

void crash_location_struct(TypeDef_Crash *Crashs, TypeDef_Crash *crashloc, int nb_crash, char location[20])
{
    char *ret=NULL;
    
    int n=0;
    for (int i=0; i<nb_crash; i++)
    {
    ret=strstr(Crashs[i].Lieu, location); // Compare si la chaine Crashs[i].Lieu contient le lieu
    if (ret!=NULL)  //Si elle le contient
    {
        crashloc[n]=Crashs[i];
        n++;
    }
    }
}