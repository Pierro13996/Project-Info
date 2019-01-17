#include "stat.h"
#include "string.h"


void crashs_annee(TypeDef_Crash *Crashs, int nb_crash) //Tri Crash par année
{
  int year=0;
  int n=0;
  char choix[4];

  printf("Pour quelle année ? \n");
  scanf("%d", &year);

  for(int i=0; i<nb_crash; i++)
  {
    if (Crashs[i].Annee==year) n++;
  }

  printf("Il y'a eu %d crashs d'avions en %d \n", n, year);
  printf("Voulez-vous les afficher ? OUI/NON \n");

  scanf("%s", choix);

  if (strcmp("OUI", choix)==0)
  {
    for(int i=0; i<=nb_crash; i++)
    {
      if (Crashs[i].Annee == year)
      {
        printf("\r\n");
        afficher_un_crash(Crashs, i);
        printf("_______________________________________________________________________________________");
        printf("\r\n");
      }
    }
  }
}

void nb_crashs_lieu(TypeDef_Crash *Crashs,int nb_crash, int *nb_crash_loc,TypeDef_Crash *crashloc) //Fonction tri crash par pays
{
    *nb_crash_loc=0;
    char location[20];
    char *ret=NULL;
    char choix[4];

    printf("De quels pays voulez-vous afficher les Crashs ? (nom du pays en anglais ex : Spain, India,...) \n");
    scanf("%s", location);

    for (int i=0; i<nb_crash; i++)
    {
        ret=strstr(Crashs[i].Lieu, location); // Compare si la chaine Crashs[i].Lieu contient le lieu
        if (ret!=NULL)  //Si elle le contient
        (*nb_crash_loc)++;
    }

    crashloc=(TypeDef_Crash*)malloc(sizeof(TypeDef_Crash)*(*nb_crash_loc));

    if(crashloc != NULL)
    {
      memset(crashloc, '\0', sizeof(TypeDef_Crash)*(*nb_crash_loc));
    }
    printf("Il y'a eu %d crashs d'avions dans le pays  %s \n",  *nb_crash_loc, location);

    crash_location_struct(Crashs, crashloc, nb_crash, location);

    printf("Voulez-vous les afficher ? OUI/NON \n");
    scanf("%s", choix);

    if (strcmp("OUI", choix)==0)
    {
      printf("\r\n");
      afficher_crashs(crashloc, *nb_crash_loc);
      printf("_______________________________________________________________________________________");
      printf("\r\n");
    }
}

/*
*Crashs : Tableau de Crashs.
int nb_crash : Dimension du Tableau de Crashs.
int annee : L'année choisie.

Renvoie le nombre de crashs dans une année choisie*/
int nb_crashs_annee(TypeDef_Crash *Crashs, int nb_crash, int annee)
{
  int crashs = 0;

  for(int i = 0; i < nb_crash; i++)
  {
    if(Crashs[i].Annee == annee) crashs++;
  }

  return crashs;
}

/*
*Crashs : Tableau de Crashs.
int nb_crash : Dimension du Tableau de Crashs.

Renvoie l'année du plus vieux crash enregistré*/
int annee_min(TypeDef_Crash *Crashs, int nb_crash)
{
  int min;

  min = Crashs[0].Annee;

  for(int i = 1; i < nb_crash; i++)
  {
    if(Crashs[i].Annee < min) min = Crashs[i].Annee;
  }

  return min;
}

/*
*Crashs : Tableau de Crashs.
int nb_crash : Dimension du Tableau de Crashs.

Renvoie l'année du dernier crash enregistré*/
int annee_max(TypeDef_Crash *Crashs, int nb_crash)
{
  int max;

  max = Crashs[0].Annee;

  for(int i = 1; i < nb_crash; i++)
  {
    if(Crashs[i].Annee > max) max = Crashs[i].Annee;
  }

  return max;
}

int moyenne_crashs_annee(TypeDef_Crash *Crashs, int nb_crash)
{
    int annee=0;
    int moy=0;
    annee = Crashs[nb_crash-1].Annee - Crashs[0].Annee;
    moy = nb_crash/annee ;
    return moy;
}

int nb_passager(TypeDef_Crash *Crashs, int nb_crash)
{
    int nb=0;
    for (int i=0; i<nb_crash; i++) nb=nb+Crashs[i].Passagers;
    return nb;
}

void survivants_crash(TypeDef_Crash *Crashs, int nb_crash, int nb_passager)
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

void regression_polynomiale(int obs, int degree, double *dx, double *dy, double *store)
{
  gsl_multifit_linear_workspace *ws;
  gsl_matrix *cov, *X;
  gsl_vector *y, *c;
  double chisq;

  int i, j;

  X = gsl_matrix_alloc(obs, degree);
  y = gsl_vector_alloc(obs);
  c = gsl_vector_alloc(degree);
  cov = gsl_matrix_alloc(degree, degree);

  for(i=0; i < obs; i++) {
    for(j=0; j < degree; j++) {
      gsl_matrix_set(X, i, j, pow(dx[i], j));
    }
    gsl_vector_set(y, i, dy[i]);
  }

  ws = gsl_multifit_linear_alloc(obs, degree);
  gsl_multifit_linear(X, y, c, cov, &chisq, ws);

  /* store result ... */
  for(i=0; i < degree; i++)
  {
    store[i] = gsl_vector_get(c, i);
  }

  gsl_multifit_linear_free(ws);
  gsl_matrix_free(X);
  gsl_matrix_free(cov);
  gsl_vector_free(y);
  gsl_vector_free(c);
}
