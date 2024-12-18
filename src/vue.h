#ifndef VUE_H
#define VUE_H

#include "modele.h"

void waitForEnter();
void afficherArmeActuelle(Personnage p, arme_s a);
void showAttack(Personnage p1, Personnage p2, int wait);
void showSort(Sort& sort, Personnage lanceur, Personnage cible);
void currentHp(Personnage p);
void currentMana(Personnage p);

// Liste
void listeArmes();

// Menus
int settingsMenu();
void afficheMainMenu();

// Choix
int choixPrinceroi();
int choixSort(Personnage p);
int fightChoice();
bool estChoixConfirmer();
int changeTextSpeed();

// Lore
void story1(int wait);
void story2(int wait);
void story3(int wait);
void dots(int wait);

#endif // VUE_H