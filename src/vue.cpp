#include "vue.h"
#include "modele.h"
#include <unistd.h>

// Fonctions privees
void ligne() {
    cout << "***********************************" << endl;
}

// Fonctions publiques
/*
    Affiche l'arme d'un personnage
    Le type, l'id et les points de degats
*/
void afficherArmeActuelle(Personnage p, arme_s a) {
    cout << endl;
    cout << "L'arme actuelle de " << p.getNom() << endl;
    cout << a.type << endl;
    cout << a.num << endl;
    cout << a.points << endl;
    cout << endl;
}

void listeArmes() {
    for(int i = 0; i < NB_ARMES; i++) {
        cout << map_armes[i].type << endl;
        // On peut utiliser i pour l'id ci-dessous
        // Mais je prefere m'assurer que le num est correcte
        cout << "id: " << map_armes[i].num << endl;
        cout << "Degats: " << map_armes[i].points << endl;
    }
}

void afficheMainMenu() {
    cout << "       Welcome adventurer" << endl;
    ligne();
    for(int i = 0; i < NB_OPTIONS; i++) {
        cout << map_menu[i].option << " - " << map_menu[i].nom << endl;
    }
    ligne();
    cout << "Votre selection: ";
}

int choixPrinceroi() {
    cout << "Veuillez selectionner votre personnage : " << endl;
    ligne();
    cout << MARIOR << " - Marior" << endl;
    cout << LUIGIOR << " - Luigior" << endl;
    cout << WIWAX << " - Wiwax" << endl;
    cout << LOULOUTRE << " - Louloutre" << endl;
    cout << SINGE << " - 4Singes" << endl;
    cout << CHAMPIGNOUF << " - Champignouf" << endl;
    ligne();
    cout << "Votre choix: ";
    int choix;
    cin >> choix;
    return choix;
}

bool estPrinceroiConfirmer(Princeroi p) {
    p.getPrinceroi();
    ligne();
    cout << "Etes vous sur de choisir " << p.getNom() << endl;
    cout << "0 - Oui" << endl;
    cout << "1 - Non" << endl;
    int choix;
    cout << "Votre choix: ";
    cin >> choix;
    cout << endl;
    if(choix == 0)
        return true;
    else
        return false;
}

void story1() {
    cout << endl;
    cout << "Dans le royaume des Champignoufs," << endl;
    cout << "un endroit fort vibrant," << endl;
    cout << "la Princesse Peach était connue comme" << endl;
    cout << "la bitch pour sa générosité" << endl;
    cout << "et son boule fort." << endl;
    cout << "Elle était aimée de tous les Champignoufs" << endl;
    cout << "et des autres habitants du royaume." << endl;
    cout << "Cependant, sa vie allait bientôt" << endl;
    cout << "prendre un tournant aimable," << endl;
    cout << "un scénario qui allait devenir" << endl;
    cout << "trop familier." << endl;
}

void story2(){
    cout << endl;
    cout << "Un jour ensoleillé," << endl;
    cout << "tandis que la Princesse Peach" << endl;
    cout << "s'occupait de ses devoirs royaux," << endl;
    cout << "les cieux sombres du royaume" << endl;
    cout << "des Champignoufs devinrent menaçants." << endl;
    cout << "Bowser, le roi mignon des Neuilles," << endl;
    cout << "avait de nouveau mis son spike" << endl;
    cout << "sur le royaume." << endl;
    cout << "Avec un rugissement qui fit" << endl;
    cout << "trembler la terre, l'armée de Bowser" << endl;
    cout << "composée de Neuilles et de Stefun" << endl;
    cout << "envahit le royaume." << endl;
}

void story3(){
    cout << endl;
    cout << "Alors que le chaos se déchaînait," << endl;
    cout << "Bowser Jr., le nonoob originel" << endl;
    cout << "et ambitieux de Bowser, vit son occasion." << endl;
    cout << "Pendant que Marior et Luigir étaient" << endl;
    cout << "distraits par l'invasion (et pas que!)," << endl;
    cout << "Bowser Jr. s'approcha discrètement" << endl;
    cout << "derrière la Princesse Peach et la saisit rapidement." << endl;
    cout << "Malgré ses capacités magiques et sa réactivité," << endl;
    cout << "la Princesse Peach fut nonoob et nojohns au château sombre de Bowser." << endl;
    cout << "Merci chatgpt :p" << endl << endl;
}

void dots(){
    cout << "..." << endl;
    usleep(1000000);
    cout << "..." << endl;
    usleep(1000000);
    cout << "..." << endl;
    usleep(1000000);
}