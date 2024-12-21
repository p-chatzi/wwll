#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

#include "controlleur.h"
#include "modele.h"
#include "vue.h"

// 2Fix
// Heal, heals 0 -> Might be fixed, updated initBaume. 2 Test
// Recheck all characters and stats
// Doule init of font - how does that work ? Might cause bugs later

int main() {
    system("clear");
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Centered Text Display");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("Roboto/Roboto-Medium.ttf")) {
        std::cerr << "Couldn't load font\n";
        return -1;
    }
    menu(window, font);
    return 0;
}
