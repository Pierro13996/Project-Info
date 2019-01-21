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

void regression_polynomiale(int nb_donnees, int degre, double *dx, double *dy, double *resultat)
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

  free(dy_reg);
}

double prediction(TypeDef_Crash *Crashs, int nb_crash, int type_prediction)
{
  double *evenement_par_annee;
  double *annee;

  int annee_mini = 0;
  int annee_maxi = 0;
  int nb_annees = 0;
  int nb_crashs_annee = 0;
  int choix;

  double resultat[] = {0, 0, 0, 0};

  annee_mini = annee_min(Crashs, nb_crash);
  annee_maxi = annee_max(Crashs, nb_crash);

  nb_annees = annee_maxi - annee_mini;

  printf("Il y a %d annees en tout.\r\n", nb_annees);

  annee = (double *)calloc(sizeof(double), nb_annees);
  if(annee == NULL)
  {
    printf("Erreur allocation\r\n");
    exit(1);
  }

  evenement_par_annee = (double *)calloc(sizeof(double), nb_annees);
  if(evenement_par_annee == NULL)
  {
    printf("Erreur allocation\r\n");
    exit(1);
  }

  printf("Année : ");
  do
  {
    scanf("%d", &choix);
  }while (choix <= 0);

  printf("annee : %d\r\n",choix);

  if(type_prediction == PREDICTION_CRASH)
  {
    // X : Abscisses {1908, 1909, ..., 2009}
    for(int i=0; i<nb_annees; i++)
    {
      annee[i] = ((double)(annee_mini + i));
    }

    // Y : Ordonnées (Nombre de crashs)
    for(int i=0; i<nb_crash; i++)
    {
      evenement_par_annee[Crashs[i].Annee - annee_mini] += 1;
    }
    for(int i=0; i<nb_annees; i++)
    {
      printf("%.f\t%.f\r\n", annee[i], evenement_par_annee[i]);
    }

    regression_polynomiale(nb_annees, 4, annee, evenement_par_annee, resultat);

    for(int i=0; i<4; i++)
    {
      nb_crashs_annee += resultat[i] * pow(choix, i);
    }
    printf("Il y aura %d crashs en une annee en %d\r\n\n", nb_crashs_annee, choix);
    printf("Equation de régression : %.1f + %.1fX + %.1fX² + %.1fX³\r\n"
    , resultat[0], resultat[1], resultat[2], resultat[3]);
    printf("%.1f + (%.1f*%d) + (%.1f*%d²) + (%.1f*%d³) = %d\r\n"
    , resultat[0], resultat[1], choix, resultat[2], choix, resultat[3], choix, nb_crashs_annee);
  }
  else if(type_prediction == PREDICTION_VICTIMES)
  {
    // X : Abscisses {1908, 1909, ..., 2009}
    for(int i=0; i<nb_annees; i++)
    {
      annee[i] = ((double)(annee_mini + i));
    }

    // Y : Ordonnées (Nombre de morts)
    for(int i=0; i<nb_crash; i++)
    {
      evenement_par_annee[Crashs[i].Annee - annee_mini] += Crashs[i].Morts;
    }
    for(int i=0; i<nb_annees; i++)
    {
      printf("%.f\t%.f\r\n", annee[i], evenement_par_annee[i]);
    }

    regression_polynomiale(nb_annees, 4, annee, evenement_par_annee, resultat);

    for(int i=0; i<4; i++)
    {
      nb_crashs_annee += resultat[i] * pow(choix, i);
    }
    printf("Il y aura %d morts en une annee en %d\r\n\n", nb_crashs_annee, choix);
    printf("Equation de régression : %.1f + %.1fX + %.1fX² + %.1fX³\r\n"
    , resultat[0], resultat[1], resultat[2], resultat[3]);
    printf("%.1f + (%.1f*%d) + (%.1f*%d²) + (%.1f*%d³) = %d\r\n"
    , resultat[0], resultat[1], choix, resultat[2], choix, resultat[3], choix, nb_crashs_annee);
  }

  free(annee);
  free(evenement_par_annee);
}
