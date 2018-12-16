#ifndef FICHIERS_H
#define FICHIERS_H

#inclide "stdlib.h"

FILE* ouvrir_fichier(char *chemin, char *nom);//Renvoie le pointeur du fichier
void fermer_fichier(void);//Ferme le fichier

void lire_fichier(char *buffer);//Stocke l'intégralité du fichier dans le buffer

#endif
