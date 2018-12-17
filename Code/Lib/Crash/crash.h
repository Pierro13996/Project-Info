#ifndef CRASH_H
#define CRASH_H

typedef struct
{
  int id;
  char date[11];
  char time[6];
  char Location[100];
  char Operator[80];
  char Flight[20];
  char Route[50];
  char Type[30];
  char Registration[40];
  char cnIn[20];
  int Aboard;
  int Fatalities;
  int Ground;
  char Summary[600];
  int Year;
  int Survived;
  char Label[100];
}TypeDef_Crash;

long compte_elements(char *buffer, long taille);//renvoie le nombre de crashs

#endif
