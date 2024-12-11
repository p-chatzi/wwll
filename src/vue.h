#ifndef VUE_H
#define VUE_H

#include "modele.h"

void waitForEnter();
int changeTextSpeed();
void afficherArmeActuelle(Personnage p, arme_s a);
void listeArmes();
void afficheMainMenu();
int choixPrinceroi();
bool estChoixConfirmer();
void dots(int wait);
void story1(int wait);
void story2(int wait);
void story3(int wait);
int settingsMenu();

#endif // VUE_H