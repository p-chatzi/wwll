#include <unistd.h>
#include <limits>

#include "vue.h"
#include "modele.h"

// Fonctions privees
void ligne() {
    cout << "***********************************" << endl;
}

// Fonctions publiques
/*
    Affiche l'arme d'un personnage
    Le type, l'id et les points de degats
*/
void waitForEnter(){
    cout << endl << "Appuye sur entrer pour continuer..." << endl << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int changeTextSpeed(){
    int wait;
    cout << "Changer la vitesse de texte" << endl;
    cout << "Entrer le temps d'attente en ms: ";
    cin >> wait;
    wait = wait * 1000;
    cout << endl;
    return wait;
}

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

bool estChoixConfirmer() {
    ligne();
    cout << "Valider vous votre choix?" << endl;
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

int settingsMenu(){
    int choix;
    cout << "   Menu parametre" << endl;
    ligne();
    cout << "Qu'es-ce que vous voulez changer?" << endl;
    cout << V_TEXT << " - Changer la vitesse du text" << endl;
    cout << VOL << " - (Volumme - for later)" << endl;
    ligne();
    cout << "Entrer votre choix: ";
    cin >> choix;
    return choix;
}

void story1(int wait) {
    cout << endl;
    cout << "Dans le royaume des Champignoufs," << endl;
    usleep(wait);
    cout << "un endroit fort vibrant," << endl;
    usleep(wait);
    cout << "la Princesse Peach était connue comme" << endl;
    usleep(wait);
    cout << "la bitch pour sa générosité" << endl;
    usleep(wait);
    cout << "et son boule fort." << endl;
    usleep(wait);
    cout << "Elle était aimée de tous les Champignoufs" << endl;
    usleep(wait);
    cout << "et des autres habitants du royaume." << endl;
    usleep(wait);
    cout << "Cependant, sa vie allait bientôt" << endl;
    usleep(wait);
    cout << "prendre un tournant aimable," << endl;
    usleep(wait);
    cout << "un scénario qui allait devenir" << endl;
    usleep(wait);
    cout << "trop familier." << endl;
    usleep(wait);
}

void story2(int wait){
    cout << endl;
    cout << "Un jour ensoleillé," << endl;
    usleep(wait);
    cout << "tandis que la Princesse Peach" << endl;
    usleep(wait);
    cout << "s'occupait de ses devoirs royaux," << endl;
    usleep(wait);
    cout << "les cieux sombres du royaume" << endl;
    usleep(wait);
    cout << "des Champignoufs devinrent menaçants." << endl;
    usleep(wait);
    cout << "Bowser, le roi mignon des Neuilles," << endl;
    usleep(wait);
    cout << "avait de nouveau mis son spike" << endl;
    usleep(wait);
    cout << "sur le royaume." << endl;
    usleep(wait);
    cout << "Avec un rugissement qui fit" << endl;
    usleep(wait);
    cout << "trembler la terre, l'armée de Bowser" << endl;
    usleep(wait);
    cout << "composée de Neuilles et de Stefun" << endl;
    usleep(wait);
    cout << "envahit le royaume." << endl;
    usleep(wait);
}

void story3(int wait){
    cout << endl;
    cout << "Alors que le chaos se déchaînait," << endl;
    usleep(wait);
    cout << "Bowser Jr., le nonoob originel" << endl;
    usleep(wait);
    cout << "et ambitieux de Bowser, vit son occasion." << endl;
    usleep(wait);
    cout << "Pendant que Marior et Luigir étaient" << endl;
    usleep(wait);
    cout << "distraits par l'invasion (et pas que!)," << endl;
    usleep(wait);
    cout << "Bowser Jr. s'approcha discrètement" << endl;
    usleep(wait);
    cout << "derrière la Princesse Peach et la saisit rapidement." << endl;
    usleep(wait);
    cout << "Malgré ses capacités magiques et sa réactivité," << endl;
    usleep(wait);
    cout << "la Princesse Peach fut nonoob et nojohns au château sombre de Bowser." << endl;
    usleep(wait);
    cout << "Merci chatgpt :p" << endl << endl;
    usleep(wait);
}

void dots(int wait){
    cout << "..." << endl;
    usleep(wait);
    cout << "..." << endl;
    usleep(wait);
    cout << "..." << endl;
    usleep(wait);
}