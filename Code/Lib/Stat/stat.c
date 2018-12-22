#include "stat.h"


TypeDef_Crash tab[3];

void remplir_tab(TypeDef_Crash tab[])
{
    for (int i=0; i<3; i++)
    {
        printf("\n ID \n");
        scanf("%d", tab[i].Id);
        printf("\n Date? \n");
        scanf("%d", tab[i].date);
        printf("\n Lieu \n");
        scanf("%s", tab[i].Lieu);
        printf("\n Operator \n");
        scanf("%s", tab[i].Operator);
        printf("\n Num vol (long) \n");
        scanf("%ld", tab[i].Num_Vol);
        printf("\n Route \n");
        scanf("%s", tab[i].Route);
        printf("\n Type \n ");
        scanf("%s", tab[i].Type);
        printf("\n Registration \n");
        scanf("%s", tab[i].Registration);
        printf("\n CnIn \n");
        scanf("%s", tab[i].Cn_In);
        printf("\n Passagers \n");
        scanf("%ld", tab[i].Passagers);
        printf("\n Morts \n");
        scanf("%ld", tab[i].Morts);
        printf("\n Sol \n");
        scanf("%ld", tab[i].Sol);
        printf("\n Rapport \n ");
        scanf("%s", tab[i].Rapport);
        printf("\n Annee \n");
        scanf("%d", tab[i].Annee);
        printf("\n Survivants \n");
        scanf("%d", tab[i].Survivants);
        printf("\n Classification \n");
        scanf("%s", tab[i].Classification);

    }
}

void afficher_tab(TypeDef_Crash tab[])
{

    for (int i=0; i<3; i++)
    {
        printf("\n ID : %d", tab);
        printf("\n Date ");
        printf("\n Lieu ");
        printf("\n Operator ");
        printf("\n Num vol (long) ");
        printf("\n Route ");
        printf("\n Type ");
        printf("\n Registration ");
        printf("\n CnIn ");
        printf("\n Passagers ");
        printf("\n Morts ");
        printf("\n Sol ");
        printf("\n Rapport  ");
        printf("\n Annee ");
        printf("\n Survivants ");
        printf("\n Classification ");
    }
}


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

