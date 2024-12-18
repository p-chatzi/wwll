#ifndef CONTROLLEUR_H
#define CONTROLLEUR_H

#include "modele.h"

void changementArme(arme_s& a, Personnage& p);
void menu();

// Initialisation des Personnages
void initPeach(Princesse& peach);
void initMarior(Princeroi& marior);
void initLuigior(Princeroi& luigior);
void initChampignouf(Princeroi& champignouf);
void initWiwax(Princeroi& wiwax);
void initLouloutre(Princeroi& louloutre);
void initSinge(Princeroi& singe);

// Initialisation des sorts
void initRassengan(Sort& rassengan);
void initEclair(Sort& eclair);
void initExplosion(Sort& explosion);
void initNoNoob(Sort& noNoob);
void initNoJohns(Sort& noJohns);
void initProtectionDivine(Sort& pd);
void initDispel(Sort& dispel);
void initBaumeAppaisant(Sort& bp);

#endif // CONTROLLEUR_H