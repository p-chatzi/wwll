#ifndef VUE_H
#define VUE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Forward declarations
class Personnage;
class arme_s;
class Sort;
class Princeroi;

void waitForEnter(sf::RenderWindow& window, sf::Font& font);
void afficherArmeActuelle(sf::RenderWindow& window, sf::Font& font, Personnage p, arme_s a);
void showAttack(sf::RenderWindow& window, sf::Font& font, Personnage p1, Personnage p2, int wait);
void showSort(sf::RenderWindow& window, sf::Font& font, Sort& sort, Personnage lanceur, Personnage cible);
void currentHp(sf::RenderWindow& window, sf::Font& font, Personnage p);
void currentMana(sf::RenderWindow& window, sf::Font& font, Personnage p);
void gainXp(sf::RenderWindow& window, sf::Font& font, int xp);
void printHero(sf::RenderWindow& window, sf::Font& font, Princeroi hero);

// SFML
void drawTexts(sf::RenderWindow& window, std::vector<sf::Text>& texts);
int getUserInput(sf::RenderWindow& window);
void displayText(sf::RenderWindow& window, const std::string& message, sf::Font& font);

// Liste
void listeArmes(sf::RenderWindow& window, sf::Font& font);

// Menus
int settingsMenu(sf::RenderWindow& window, sf::Font& font);
void afficheMainMenu(sf::RenderWindow& window, sf::Font& font);

// Choix
int choixPrinceroi(sf::RenderWindow& window, sf::Font& font);
int choixSort(sf::RenderWindow& window, sf::Font& font, Personnage p);
int fightChoice(sf::RenderWindow& window, sf::Font& font);
bool estChoixConfirmer(sf::RenderWindow& window, sf::Font& font);
int changeTextSpeed(sf::RenderWindow& window, sf::Font& font);

// Lore
void story1(sf::RenderWindow& window, sf::Font& font, int wait);
void story2(sf::RenderWindow& window, sf::Font& font, int wait);
void story3(sf::RenderWindow& window, sf::Font& font, int wait);
void dots(sf::RenderWindow& window, sf::Font& font, int wait);
void beforeWarior(sf::RenderWindow& window, sf::Font& font, int wait);
void afterWarior(sf::RenderWindow& window, sf::Font& font, int wait);
void beforeYipee(sf::RenderWindow& window, sf::Font& font, int wait);
void afterYipee(sf::RenderWindow& window, sf::Font& font, int wait);

#endif // VUE_H