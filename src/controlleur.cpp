#include <iostream>
#include <unistd.h>

#include "controlleur.h"
#include "modele.h"
#include "vue.h"


using namespace std;

// Fonctions privees
Princeroi selectionPrinceroi(){
    while(1){
    int selectionId = choixPrinceroi();
    cout << selectionId << endl;
    Princeroi princeroi(selectionId);
    princeroi.getPrinceroi();
    if(estChoixConfirmer())
        return princeroi;
    }
}

void initWarior(Monstre& warior){
    warior.setNum(WARIOR);
    warior.setNom("Warior");
    warior.setAge(33);
    warior.setVie(100);
    warior.setConte("Waaaaa");
    warior.setArme(FIST);
    warior.setType("Human");
    warior.setCouleur("Jaune");
    warior.setForce(1);
    warior.setGentil(false);
}

void initYipee(Monstre& yipee){
    yipee.setNum(YIPEE);
    yipee.setNom("Warior");
    yipee.setAge(33);
    yipee.setVie(1);
    yipee.setConte("Yipeeeee");
    yipee.setArme(CALIN);
    yipee.setType("Insecte mignon");
    yipee.setCouleur("vert");
    yipee.setForce(1);
    yipee.setGentil(true);
}

bool isFightWon(Princeroi p, Monstre m){
    while(p.getVie() > 0 && m.getVie() > 0){
        m.setVie(p.attack(m));
        cout << p.getNom() << " attack " << m.getNom() << " avec ";
        cout << map_armes[p.getArme()].type << " faisant ";
        cout << map_armes[p.getArme()].points << " degats." << endl;
        cout << "Il reste au monstre: " << m.getVie() << "HP" << endl << endl;
        usleep(500000);

        if(m.getVie() > 0){
            p.setVie(m.attack(p));
            cout << m.getNom() << " attack " << p.getNom() << " avec ";
            cout << map_armes[m.getArme()].type << " faisant ";
            cout << m.getForce() * map_armes[m.getArme()].points << " degats." << endl;
            cout << "Il reste au hero: " << p.getVie() << "HP" << endl << endl;
            usleep(500000);
        }
    }
    if(p.getVie() <= 0){
        cout << p.getNom() << " es mort" << endl;
        return false;
    }
    else{
        cout << m.getNom() << " est mort" << endl;
        usleep(1000000);
        return true;
    }
}

void debutAventure(int wait){
    Princeroi hero = selectionPrinceroi();
    cout << "Welcome, " << hero.getNom() << ", " << hero.getConte() << endl;
    story1(wait);
    story2(wait);
    story3(wait);
    waitForEnter();

    // Fight vs Warior
    Monstre warior;
    initWarior(warior);
    cout << "Un Warior sauvage apparait et vous lache une caisse!" << endl;
    usleep(wait);
    cout << "Mecreant, vous ne pouvez point laisser cela passer" << endl;
    usleep(wait);
    cout << "[insert epic battle music]" << endl << endl;
    waitForEnter();
    if(!isFightWon(hero, warior))
        return;
    cout << "Bravo, allez voir Peach pour une belle recompense" << endl;
    dots(wait);
    cout << "Ah merde!" << endl << "Bon vas sauvez Bowser... euh peach" << endl;
    usleep(wait);
    waitForEnter();

    // Fight vs Yipee
    Monstre yipee;
    initYipee(yipee);
    cout << "Tu scrutine le boisson devant toi..." << endl;
    usleep(wait);
    cout << "Le buisson bouge, un goomba serait encore en vie?" << endl;
    usleep(wait);
    cout << "SAUTE DESSUS!" << endl << "[insert epic battle music]" << endl;
    usleep(wait);
    waitForEnter();
    if(!isFightWon(hero, yipee))
        return;
    cout << "SAUVAGE ! TU DOIS TOUT TUER SUR TON CHEMIN OU QUOI???" << endl;
    usleep(wait);
    cout << "Le pauvre yipee... nos seul ami... mort" << endl;
    dots(wait);
    cout << "DE TES MAINS, TES MAINS ENSENGLENTEES!" << endl;
    usleep(wait);
    cout << "Tu n'entendras plus de yipee, tu ne verras plus de yipee" << endl;
    usleep(wait);
    cout << "Continue donc ton pauvre chemin" << endl << endl;
    usleep(wait);
    waitForEnter();
}

void settings(int* wait){
    int choix = settingsMenu();
    switch(choix){
        case V_TEXT:
            *wait = changeTextSpeed();
            break;
        case VOL:
            cout << "Pour plus tard" << endl;
            break;
        case EXIT_SETTINGS:
            return;
        default:
            cout << "Entree invalide, reesayer" << endl;
            break;
    }
}

// Fonctions publiques
/*
    Affiche la liste des options
*/
void menu(){
    while(1){
        afficheMainMenu();
        int choix, wait;
        cin >> choix;
        switch (choix)
        {
        case START:
            system("clear");
            debutAventure(wait);
            break;

        case LOAD:
            system("clear");
            cout << "WIP" << endl;
            break;

        case SETTINGS:
            system("clear");
            settings(&wait);
            break;

        case QUIT:
            cout << "A bientot" << endl;
            exit(0);

        default:
            cout << "Choix invalide, ressayer" << endl;
            break;
        }
    }
}

/*
    Change l'arme du personnage choisi
*/
void changementArme(arme_s& a, Personnage& p){
    listeArmes();
    cout << "Votre choix: ";
    int choix;
    cin >> choix;
    p.changeArme(a, p, choix);
}

void initPeach(Princesse& peach){
    // Princesse peach la bitch
    peach.setNum(PEACH);
    peach.setNom("Peach");
    peach.setAge(20);
    peach.setVie(100);
    peach.setConte("L'heureuse victimme de Bowser");
    peach.setArme(POELE);
    peach.setFaiblesse("Bowser");
    peach.setEtat(EVEILLE);
}

void initMarior(Princeroi& marior){
    // Marior - le fake plombier
    marior.setNum(MARIOR);
    marior.setNom("Marior");
    marior.setAge(66);
    marior.setVie(100);
    marior.setConte("Il adore les gros toyaux et les pipes");
    marior.setArme(GROS_TUYEAU);
    marior.setTitre("Plombier de l'extreme");
    marior.setTribu("64");
    marior.setNature("Cochon");
    marior.setEtatCivil("Stalker de Peach");
}

void initLuigior(Princeroi& luigior){
    // Luigior - le fake apprenti plombier 
    luigior.setNum(LUIGIOR);
    luigior.setNom("Luigior");
    luigior.setAge(66);
    luigior.setVie(100);
    luigior.setConte("Apprenti adorateur de tuyeau");
    luigior.setArme(GROS_TUYEAU);
    luigior.setTitre("Vicitimme de l'extreme");
    luigior.setTribu("64");
    luigior.setNature("Mouton");
    luigior.setEtatCivil("Suiveur");
}

void initChampignouf(Princeroi& champignouf){
    // Champignouf de l'extreme 
    champignouf.setNum(CHAMPIGNOUF);
    champignouf.setNom("Champignouf");
    champignouf.setAge(22);
    champignouf.setVie(100);
    champignouf.setConte("de l'extreme");
    champignouf.setArme(BAD_TRIP);
    champignouf.setTitre("A quand champignouf dans SSBU?");
    champignouf.setTribu("64");
    champignouf.setNature("Extreme");
    champignouf.setEtatCivil("Sponsor de Nintendo");
}

void initWiwax(Princeroi& wiwax){
    // Wiwax le chickenwiwi
    wiwax.setNum(WIWAX);
    wiwax.setNom("Wiwax");
    wiwax.setAge(20);
    wiwax.setVie(100);
    wiwax.setConte("Mangeur de pastaga");
    wiwax.setArme(POULAX);
    wiwax.setTitre("Ohoho c'est wiwi et...");
    wiwax.setTribu("64");
    wiwax.setNature("Poulet braise");
    wiwax.setEtatCivil("Chickenwiwi");
}

void initLouloutre(Princeroi& louloutre){
    // Louloutre la secretaire
    louloutre.setNum(LOULOUTRE);
    louloutre.setNom("Louloutre");
    louloutre.setAge(20);
    louloutre.setVie(100);
    louloutre.setConte("Investigateur de bureaux");
    louloutre.setArme(PIPE);
    louloutre.setTitre("Secretaire");
    louloutre.setTribu("64");
    louloutre.setNature("Awii");
    louloutre.setEtatCivil("Voler");
}

void initSinge(Princeroi& singe){
    // Les singes de 4tune
    singe.setNum(SINGE);
    singe.setNom("4singes");
    singe.setAge(4);
    singe.setVie(100);
    singe.setConte("Produits de laboratoire");
    singe.setArme(FIST);
    singe.setTitre("Anti-stress");
    singe.setTribu("Mystere");
    singe.setNature("Virulent");
    singe.setEtatCivil("Inconnu");
}
