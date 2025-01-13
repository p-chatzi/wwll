#include <unistd.h>
#include <limits>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "vue.h"
#include "modele.h"

// Fonctions privees
void ligne(sf::RenderWindow& window, sf::Font& font, std::vector<sf::Text>& texts) {
    sf::Text text("***********************************", font, 24);
    text.setFillColor(sf::Color::White);
    texts.push_back(text);
}

// sf::Font loadFont(){
    // Load font
    // sf::Font font;
    // if (!font.loadFromFile("Roboto/Roboto-Medium.ttf")) {
        // std::cerr << "Couldn't load font\n";
        // return sf::Font(); // return empty font
    // }
    // return font;
// }

void drawTexts(sf::RenderWindow& window, std::vector<sf::Text>& texts) {
    window.clear();
    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i].setPosition(window.getSize().x / 2.0f, (window.getSize().y / 3.0f) + (i * 30)); // Adjust vertical spacing
        window.draw(texts[i]);
    }
    window.display();
}

// Fonctions publiques
int getUserInput(sf::RenderWindow& window) {
    cout << "Entering getUserInput" << endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            cout << "Event polled" << endl;
            if (event.type == sf::Event::Closed) {
                cout << "Window closed" << endl;
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                cout << "Key pressed event detected" << endl;
                if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                    cout << "Key pressed: " << event.key.code - sf::Keyboard::Num0 << endl;
                    return event.key.code - sf::Keyboard::Num0;
                } else {
                    cout << "Other key pressed: " << event.key.code << endl;
                }
            }
            if (event.type == sf::Event::LostFocus) {
                cout << "Window lost focus" << endl;
            }
            if (event.type == sf::Event::GainedFocus) {
                cout << "Window gained focus" << endl;
            }
        }

        // Check if the window has focus
        if (!window.hasFocus()) {
            cout << "Window does not have focus, requesting focus" << endl;
            window.requestFocus();
        }
    }
    cout << "Window is closed, returning -1" << endl;
    return -1; // Return -1 if the window is closed
}

void displayText(sf::RenderWindow& window, const std::string& message, sf::Font& font) {
    std::vector<sf::Text> texts;
    sf::Text text(message, font, 24);
    text.setFillColor(sf::Color::White);
    texts.push_back(text);
    drawTexts(window, texts);
    usleep(2000000); // Wait for 2 seconds to display the message
}

/*
    Affiche l'arme d'un personnage
    Le type, l'id et les points de degats
*/
void waitForEnter(sf::RenderWindow& window, sf::Font& font){
    std::vector<sf::Text> texts;
    sf::Text text("Appuye sur entrer pour continuer...", font, 24);
    text.setFillColor(sf::Color::White);
    texts.push_back(text);
    drawTexts(window, texts);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                return;
        }
    }
}

/*
    Permet au joueur de changer la vitesse
    a laquelle le texte vas se derouler.
    Accessible via le menu de parametres
*/
int changeTextSpeed(sf::RenderWindow& window, sf::Font& font){
    std::vector<sf::Text> texts;
    sf::Text text("Changer la vitesse de texte", font, 24);
    text.setFillColor(sf::Color::White);
    texts.push_back(text);
    text.setString("Entrer le temps d'attente en ms: ");
    texts.push_back(text);
    drawTexts(window, texts);
    int wait = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    wait = wait * 10 + (event.text.unicode - '0');
                    text.setString("Entrer le temps d'attente en ms: " + std::to_string(wait));
                    drawTexts(window, texts);
                }
                if (event.text.unicode == '\n' || event.text.unicode == '\r') {
                    return wait * 1000;
                }
            }
        }
    }
    return wait * 1000;
}

/*
    Affiche des informations sur l'armes choisit
    Eg. verifier quelle arme on as sur nous,
    ou verifier l'arme que l'on veut acheter etc...
 */
void afficherArmeActuelle(sf::RenderWindow& window, sf::Font& font, Personnage p, arme_s a) {
    std::vector<sf::Text> texts;
    std::string displayName = "L'arme actuelle de " + std::string(p.getNom());
    texts.push_back(sf::Text(displayName, font, 24));
    texts.push_back(sf::Text(a.type, font, 24));
    texts.push_back(sf::Text(std::to_string(a.num), font, 24));
    texts.push_back(sf::Text(std::to_string(a.points), font, 24));
    drawTexts(window, texts);
}

/*
    Affiche les informations sur toutes les armes existantes
*/
void listeArmes(sf::RenderWindow& window, sf::Font& font) {
    std::vector<sf::Text> texts;
    for(int i = 0; i < NB_ARMES; i++) {
        texts.push_back(sf::Text(map_armes[i].type, font, 24));
        texts.push_back(sf::Text("id: " + std::to_string(map_armes[i].num), font, 24));
        texts.push_back(sf::Text("Degats: " + std::to_string(map_armes[i].points), font, 24));
    }
    drawTexts(window, texts);
}

void printSfml(sf::RenderWindow& window, sf::Font& font, std::vector<std::wstring> lines) {
    std::vector<sf::Text> texts;
    for (const auto& line : lines) {
        sf::Text text(line, font, 24);
        text.setFillColor(sf::Color::White);
        text.setString(line); // Assuming line is already in UTF-8

        // Center the text
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.width / 2, textRect.height / 2);

        texts.push_back(text);
    }

    // Position texts in the center of the window
    for (size_t i = 0; i < texts.size(); ++i) {
        texts[i].setPosition(window.getSize().x / 2.0f, (window.getSize().y / 3.0f) + (i * 30)); // Adjust vertical spacing
    }

    window.clear();
    for (const auto& text : texts) {
        window.draw(text);
    }
    window.display();

    // Wait for user input to proceed
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                return; // Exit the function when a key is pressed
            }
        }
    }
}

void afficheMainMenu(sf::RenderWindow& window, sf::Font& font) {
    // Define the text lines
    std::vector<std::wstring> lines = {
        L"       Welcome adventurer",
        L"***********************************"
    };

    for(int i = 0; i < NB_OPTIONS; i++) {
        lines.push_back(std::to_wstring(map_menu[i].option) + L" - " + std::wstring(map_menu[i].nom, map_menu[i].nom + strlen(map_menu[i].nom)));
    }

    lines.push_back(L"***********************************");
    lines.push_back(L"Votre selection: ");
    printSfml(window, font, lines);
}

int choixSort(sf::RenderWindow& window, sf::Font& font, Personnage p) {
    std::vector<sf::Text> texts;
    texts.push_back(sf::Text("Veuillez selectionner un sort : ", font, 24));
    currentMana(window, font, p);
    ligne(window, font, texts);
    texts.push_back(sf::Text("Retour en arriere : " + std::to_string(GO_BACK), font, 24));
    texts.push_back(sf::Text("Sorts offensif :", font, 24));
    texts.push_back(sf::Text(std::to_string(RASSENGAN) + " - Rassengan", font, 24));
    texts.push_back(sf::Text(std::to_string(ECLAIR) + " - Eclair", font, 24));
    texts.push_back(sf::Text(std::to_string(EXPLOSION) + " - Explosion", font, 24));
    texts.push_back(sf::Text(std::to_string(NO_NOOB) + " - No noob", font, 24));
    texts.push_back(sf::Text(std::to_string(NO_JOHNS) + " - No johns", font, 24));
    texts.push_back(sf::Text("Sorts de buff :", font, 24));
    texts.push_back(sf::Text(std::to_string(PROTECTION_DIVINE) + " - Protection divine", font, 24));
    texts.push_back(sf::Text("Sorts de debuff :", font, 24));
    texts.push_back(sf::Text(std::to_string(DISPEL) + " - Dispel", font, 24));
    texts.push_back(sf::Text(std::to_string(SILENCE) + " - Silence", font, 24));
    texts.push_back(sf::Text("Sorts de soin :", font, 24));
    texts.push_back(sf::Text(std::to_string(BAUME_APPAISANT) + " - Baume appaisant", font, 24));
    ligne(window, font, texts);
    texts.push_back(sf::Text("Votre choix: ", font, 24));
    drawTexts(window, texts);
    return getUserInput(window);
}

int choixPrinceroi(sf::RenderWindow& window, sf::Font& font) {
    std::vector<sf::Text> texts;
    texts.push_back(sf::Text("Veuillez selectionner votre personnage : ", font, 24));
    ligne(window, font, texts);
    texts.push_back(sf::Text(std::to_string(MARIOR) + " - Marior", font, 24));
    texts.push_back(sf::Text(std::to_string(LUIGIOR) + " - Luigior", font, 24));
    texts.push_back(sf::Text(std::to_string(WIWAX) + " - Wiwax", font, 24));
    texts.push_back(sf::Text(std::to_string(LOULOUTRE) + " - Louloutre", font, 24));
    texts.push_back(sf::Text(std::to_string(SINGE) + " - 4Singes", font, 24));
    texts.push_back(sf::Text(std::to_string(CHAMPIGNOUF) + " - Champignouf", font, 24));
    ligne(window, font, texts);
    texts.push_back(sf::Text("Votre choix: ", font, 24));
    drawTexts(window, texts);
    return getUserInput(window);
}

bool estChoixConfirmer(sf::RenderWindow& window, sf::Font& font) {
    std::vector<sf::Text> texts;
    ligne(window, font, texts);
    texts.push_back(sf::Text("Valider vous votre choix?", font, 24));
    texts.push_back(sf::Text("0 - Oui", font, 24));
    texts.push_back(sf::Text("1 - Non", font, 24));
    texts.push_back(sf::Text("Votre choix: ", font, 24));
    drawTexts(window, texts);
    return getUserInput(window) == 0;
}

int settingsMenu(sf::RenderWindow& window, sf::Font& font){
    std::vector<sf::Text> texts;
    texts.push_back(sf::Text("   Menu parametre", font, 24));
    ligne(window, font, texts);
    texts.push_back(sf::Text("Qu'es-ce que vous voulez changer?", font, 24));
    texts.push_back(sf::Text(std::to_string(V_TEXT) + " - Changer la vitesse du text", font, 24));
    texts.push_back(sf::Text(std::to_string(VOL) + " - (Volumme - for later)", font, 24));
    ligne(window, font, texts);
    texts.push_back(sf::Text("Entrer votre choix: ", font, 24));
    drawTexts(window, texts);
    return getUserInput(window);
}

int fightChoice(sf::RenderWindow& window, sf::Font& font){
    std::vector<sf::Text> texts;
    ligne(window, font, texts);
    texts.push_back(sf::Text("Que faire sur ce tour", font, 24));
    texts.push_back(sf::Text(std::to_string(ATTACK) + " - Pour attaquer le monstre avec votre arme", font, 24));
    texts.push_back(sf::Text(std::to_string(SORT) + " - Pour utiliser un sort", font, 24));
    ligne(window, font, texts);
    texts.push_back(sf::Text("Entrer votre choix: ", font, 24));
    drawTexts(window, texts);
    return getUserInput(window);
}

void showAttack(sf::RenderWindow& window, sf::Font& font, Personnage p1, Personnage p2, int wait){
    std::vector<sf::Text> texts;
    std::string displayName = std::string(p1.getNom()) + " lance " + map_armes[p1.getArme()].type + " sur " + std::string(p2.getNom());
    texts.push_back(sf::Text(displayName, font, 24));
    displayName = std::string(p2.getNom()) + " perds " + std::to_string(map_armes[p1.getArme()].points) + "pdv";
    texts.push_back(sf::Text(displayName, font, 24));
    drawTexts(window, texts);
    usleep(wait);
}

void showSort(sf::RenderWindow& window, sf::Font& font, Sort& sort, Personnage lanceur, Personnage cible) {
    std::vector<sf::Text> texts;
    std::string displayName = "Le sort " + std::string(sort.getNom(), sort.getNom() + strlen(sort.getNom())) + " est lancé sur " + cible.getNom();
    texts.push_back(sf::Text(displayName, font, 24));
    if (sort.getType() == OFFENSIF) {
        texts.push_back(sf::Text("Dégâts infligés: " + std::to_string(sort.getDegat()), font, 24));
    } else if (sort.getType() == BUFF) {
        texts.push_back(sf::Text("Buff défense: " + std::to_string(sort.getBuffDef()), font, 24));
        texts.push_back(sf::Text("Buff attaque: " + std::to_string(sort.getBuffAtk()), font, 24));
    } else if (sort.getType() == DEBUFF) {
        texts.push_back(sf::Text("Debuff défense: " + std::to_string(sort.getDebuffDef()), font, 24));
        texts.push_back(sf::Text("Debuff attaque: " + std::to_string(sort.getDebuffAtk()), font, 24));
    } else if (sort.getType() == SOIN) {
        texts.push_back(sf::Text("Soin appliqué: " + std::to_string(sort.getSoin()), font, 24));
    }
    drawTexts(window, texts);
}

void currentHp(sf::RenderWindow& window, sf::Font& font, Personnage p){
    std::vector<sf::Text> texts;
    std::string displayName = std::string(p.getNom()) + ": " + std::to_string(p.getVie()) + "/" + std::to_string(p.getMaxVie()) + " HP - ";
    texts.push_back(sf::Text(displayName, font, 24));
    drawTexts(window, texts);
}

void currentMana(sf::RenderWindow& window, sf::Font& font, Personnage p){
    std::vector<sf::Text> texts;
    texts.push_back(sf::Text(std::to_string(p.getMana()) + "/" + std::to_string(p.getMaxMana()) + " Mana ", font, 24));
    drawTexts(window, texts);
}

void story1(sf::RenderWindow& window, sf::Font& font, int wait){

    // Define the text lines
    std::vector<std::wstring> lines = {
        L"Dans le royaume des Champignoufs,",
        L"un endroit fort vibrant,",
        L"la Princesse Peach était connue comme",
        L"la bitch pour sa générosité",
        L"et son boule fort.",
        L"Elle était aimée de tous les Champignoufs",
        L"et des autres habitants du royaume.",
        L"Cependant, sa vie allait bientôt",
        L"prendre un tournant aimable,",
        L"un scénario qui allait devenir",
        L"trop familier."
    };
    printSfml(window, font, lines);
}

void story2(sf::RenderWindow& window, sf::Font& font, int wait){
    // Define the text lines
    std::vector<std::wstring> lines = {
        L"Un jour ensoleillé,",
        L"tandis que la Princesse Peach",
        L"s'occupait de ses devoirs royaux,",
        L"les cieux sombres du royaume",
        L"des Champignoufs devinrent menaçants.",
        L"Bowser, le roi mignon des Neuilles,",
        L"avait de nouveau mis son spike",
        L"sur le royaume.",
        L"Avec un rugissement qui fit",
        L"trembler la terre, l'armée de Bowser",
        L"composée de Neuilles et de Stefun",
        L"envahit le royaume."
    };
    printSfml(window, font, lines);
}

void story3(sf::RenderWindow& window, sf::Font& font, int wait){
    std::vector<std::wstring> lines = {
        L"Alors que le chaos se déchaînait,",
        L"Bowser Jr., le nonoob originel",
        L"et ambitieux de Bowser, vit son occasion.",
        L"Pendant que Marior et Luigir étaient",
        L"distraits par l'invasion (et pas que!),",
        L"Bowser Jr. s'approcha discrètement",
        L"derrière la Princesse Peach et la saisit rapidement.",
        L"Malgré ses capacités magiques et sa réactivité,",
        L"la Princesse Peach fut nonoob et nojohns au château sombre de Bowser.",
        L"Merci chatgpt :p"
    };
    printSfml(window, font, lines);
}

void dots(sf::RenderWindow& window, sf::Font& font, int wait){
    sf::Clock clock;
    sf::Time elapsed;

        displayText(window, ".", font);
        clock.restart();
        while (window.isOpen() && (elapsed = clock.getElapsedTime()).asMilliseconds() < wait) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }
        }
    
        displayText(window, "..", font);
        clock.restart();
        while (window.isOpen() && (elapsed = clock.getElapsedTime()).asMilliseconds() < wait) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }
        }
        displayText(window, "...", font);
        clock.restart();
        while (window.isOpen() && (elapsed = clock.getElapsedTime()).asMilliseconds() < wait) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
            }
        }
}

void beforeWarior(sf::RenderWindow& window, sf::Font& font, int wait){
    displayText(window, "Un Warior sauvage apparait et vous lache une caisse!", font);
    usleep(wait);
    displayText(window, "Mecreant, vous ne pouvez point laisser cela passer", font);
    usleep(wait);
    displayText(window, "[insert epic battle music]", font);
    usleep(wait);
    waitForEnter(window, font);
}

void afterWarior(sf::RenderWindow& window, sf::Font& font, int wait){
    displayText(window, "Bravo, allez voir Peach pour une belle recompense", font);
    dots(window, font, wait);
    displayText(window, "Ah merde! Bon vas sauvez Bowser... euh peach", font);
    usleep(wait);
}

void beforeYipee(sf::RenderWindow& window, sf::Font& font, int wait){
    displayText(window, "Tu scrutine le buisson devant toi...", font);
    usleep(wait);
    displayText(window, "Le buisson bouge, un goomba serait encore en vie?", font);
    usleep(wait);
    displayText(window, "SAUTE DESSUS! [insert epic battle music]", font);
    usleep(wait);
    waitForEnter(window, font);
}

void afterYipee(sf::RenderWindow& window, sf::Font& font, int wait){
    displayText(window, "SAUVAGE ! TU DOIS TOUT TUER SUR TON CHEMIN OU QUOI???", font);
    usleep(wait);
    displayText(window, "Le pauvre yipee... nos seul ami... mort", font);
    dots(window, font, wait);
    displayText(window, "DE TES MAINS, TES MAINS ENSENGLENTEES!", font);
    usleep(wait);
    displayText(window, "Tu n'entendras plus de yipee, tu ne verras plus de yipee", font);
    usleep(wait);
    displayText(window, "Continue donc ton pauvre chemin", font);
    usleep(wait);
}

void gainXp(sf::RenderWindow& window, sf::Font& font, int xp){
    displayText(window, "Tu as gagne " + std::to_string(xp) + "XP", font);
}

void printHero(sf::RenderWindow& window, sf::Font& font, Princeroi hero){
    std::string displayName = "Welcome, " + std::string(hero.getNom()) + ", " + std::string(hero.getConte());
    displayText(window, displayName, font);
}