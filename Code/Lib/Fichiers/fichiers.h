#ifndef FICHIERS_H
#define FICHIERS_H

#include "stdio.h"
#include "stdlib.h"

FILE *ouvrir_fichier(char *chemin);
int fermer_fichier(FILE *fichier);
void lire_fichier(char *buffer, FILE* fichier);
long taille_fichier(FILE *fichier);

#endif
