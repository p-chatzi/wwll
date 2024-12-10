#ifndef CONTROLLEUR_H
#define CONTROLLEUR_H

#include "modele.h"

void changementArme(arme_s& a, Personnage& p);
void menu();

void initPeach(Princesse& peach);
void initMarior(Princeroi& marior);
void initLuigior(Princeroi& luigior);
void initChampignouf(Princeroi& champignouf);
void initWiwax(Princeroi& wiwax);
void initLouloutre(Princeroi& louloutre);
void initSinge(Princeroi& singe);

#endif // CONTROLLEUR_H