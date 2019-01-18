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

double regression_polynomiale(int nb_donnees, int degre, double *dx, double *dy, double *resultat)
{
  gsl_multifit_linear_workspace *ws;
  gsl_matrix *cov, *X;
  gsl_vector *y, *y_reg, *c;
  double chisq;
  double facteur_correlation = 0;

  double *dy_reg = NULL;

  dy_reg = (double*)calloc(sizeof(double), nb_donnees);

  int i, j;

  X = gsl_matrix_alloc(nb_donnees, degre);
  y = gsl_vector_alloc(nb_donnees);
  c = gsl_vector_alloc(degre);
  cov = gsl_matrix_alloc(degre, degre);

  for(i=0; i < nb_donnees; i++) {
    for(j=0; j < degre; j++) {
      gsl_matrix_set(X, i, j, pow(dx[i], j));
    }
    gsl_vector_set(y, i, dy[i]);
  }

  ws = gsl_multifit_linear_alloc(nb_donnees, degre);
  gsl_multifit_linear(X, y, c, cov, &chisq, ws);

  for(i=0; i < degre; i++)
  {
    resultat[i] = gsl_vector_get(c, i);
  }

  gsl_multifit_linear_free(ws);
  gsl_matrix_free(X);
  gsl_matrix_free(cov);
  gsl_vector_free(y);
  gsl_vector_free(c);

  for(int i=0; i<nb_donnees; i++)
  {
    for(int j=0; j<degre; j++)
    {
      dy_reg[i] += resultat[j] * pow(i, j);
    }
  }

  dy[3] = 28659876;
  printf("dy : {");
  for(i=0; i < nb_donnees; i++)
  {
    printf("%.f ", dy[i]);
  }
  printf("}\r\n");

  printf("dy_reg : {");
  for(i=0; i < nb_donnees; i++)
  {
    printf("%.f ", dy_reg[i]);
  }
  printf("}\r\n");

  //
  // gsl_vector_view ranks1 = gsl_vector_view_array(&work[0], nb_donnees);
  // gsl_vector_view ranks2 = gsl_vector_view_array(&work[n], nb_donnees);
  //
  // for (i = 0; i < n; ++i)
  //   {
  //     gsl_vector_set(&ranks1.vector, i, data1[i * stride1]);
  //     gsl_vector_set(&ranks2.vector, i, data2[i * stride2]);
  //   }
  //
  // /* sort data1 and update data2 at same time; compute rank of data1 */
  // gsl_sort_vector2(&ranks1.vector, &ranks2.vector);
  // compute_rank(&ranks1.vector);
  //
  // /* now sort data2, updating ranks1 appropriately; compute rank of data2 */
  // gsl_sort_vector2(&ranks2.vector, &ranks1.vector);
  // compute_rank(&ranks2.vector);
  //
  // /* compute correlation of rank vectors in double precision */
  // r = gsl_stats_correlation(ranks1.vector.data, ranks1.vector.stride,
  //                           ranks2.vector.data, ranks2.vector.stride,
  //                           n);

  for(i=0; i < nb_donnees; i++)
  {
    gsl_vector_set(y, i, dy[i]);
    gsl_vector_set(y_reg, i, dy_reg[i]);
  }

  facteur_correlation = gsl_stats_correlation(dy, sizeof(double), dy_reg, sizeof(double), nb_donnees);

  gsl_vector_free(y);
  gsl_vector_free(y_reg);

  return facteur_correlation;
}
