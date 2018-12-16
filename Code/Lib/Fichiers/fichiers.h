#ifndef FICHIERS_H
#define FICHIERS_H

#include "stdio.h"
#include "stdlib.h"

void ouvrir_fichier(char *chemin, FILE *fichier);
int fermer_fichier(FILE *fichier);

void lire_fichier(char *buffer);//Stocke l'intégralité du fichier dans le buffer

int taille_fichier(FILE *fichier);
#endif
