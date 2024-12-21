#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "vue.h"
#include "modele.h"

using namespace std;

// Fonctions privees
Princeroi selectionPrinceroi(sf::RenderWindow& window, sf::Font& font){
    while(1){
        int selectionId = choixPrinceroi(window, font);
        displayText(window, std::to_string(selectionId), font);
        Princeroi princeroi(selectionId);
        princeroi.getPrinceroi(window, font);
        if(estChoixConfirmer(window, font))
            return princeroi;
    }
}

void initWarior(Monstre& warior){
    warior.setNum(WARIOR);
    warior.setNom("Warior");
    warior.setAge(33);
    warior.setVie(100);
    warior.setMaxVie(100);
    warior.setMana(100);
    warior.setMaxMana(100);
    warior.setConte("Waaaaa");
    warior.setArme(FIST);
    warior.setType("Human");
    warior.setCouleur("Jaune");
    warior.setForce(1);
    warior.setGentil(false);
}

void initYipee(Monstre& yipee){
    yipee.setNum(YIPEE);
    yipee.setNom("Yipee");
    yipee.setAge(33);
    yipee.setVie(1);
    yipee.setMaxVie(1);
    yipee.setMana(100);
    yipee.setMaxMana(100);
    yipee.setConte("Yipeeeee");
    yipee.setArme(CALIN);
    yipee.setType("Insecte mignon");
    yipee.setCouleur("vert");
    yipee.setForce(1);
    yipee.setGentil(true);
}

void evolutionChampignouf(Princeroi& p){
    p.setNom("Super champignouf");
}

void evolve(sf::RenderWindow& window, sf::Font& font, Princeroi& p, int wait){
    if(p.getLevel() % 5 == 0){
        std::string displayName = std::string(p.getNom()) + " que se passe t-il?...";
        displayText(window, displayName, font);
        usleep(wait);

        displayName = std::string(p.getNom()) + " se transforme...";
        displayText(window, displayName, font);
        usleep(wait);
        
        displayName = std::string(p.getNom()) + "evolue en: ";
        displayText(window, displayName, font);
        evolutionChampignouf(p);
        
        displayName = std::string(p.getNom()) + "!";
        displayText(window, displayName, font);
    }
}

void levelUp(sf::RenderWindow& window, sf::Font& font, Princeroi& p, int gainXp, int wait){
    if((p.getXp() / 100) > p.getLevel()){
        // Up max vie et mana et regen
        p.setLevel(p.getLevel() + 1);
        p.setMaxVie(p.getMaxVie() + 10);
        p.setMaxMana(p.getMaxMana() + 5);
        p.setVie(p.getMaxVie());
        p.setMana(p.getMaxMana()); 
        displayText(window, "Level up - Vous passez Lvl." + std::to_string(p.getLevel()), font);
        currentHp(window, font, p);
        currentMana(window, font, p);
        evolve(window, font, p, wait);
    }
}

void appliqueSort(Sort& sort, Personnage& lanceur, Personnage& cible){
    if(sort.getType() == OFFENSIF){
        cible.setVie(cible.getVie() - sort.getDegat());
    }
    if(sort.getType() == DEBUFF){
        std::cerr << "WIP" << endl;
    }
    if(sort.getType() == BUFF){
        std::cerr << "WIP" << endl;
    }
    if(sort.getType() == SOIN)
        cible.setVie(cible.getVie() + sort.getSoin());
}

bool lancerSort(sf::RenderWindow& window, sf::Font& font, Princeroi& p, Monstre& m){
    while (1) {
        // Selection d'un sort
        int choix = choixSort(window, font, p);
        if(choix >= 0 && choix < NB_SORTS){
            // On affiche les details de ce sort
            Sort sort(choix);
            sort.getSort(window, font);
            if(estChoixConfirmer(window, font) && p.getMana() >= sort.getCoutMana()){
                // On applique si la selection est confirmer
                p.setMana(p.getMana() - sort.getCoutMana());
                if(sort.getType() == OFFENSIF || sort.getType() == DEBUFF){
                    appliqueSort(sort, p, m);
                    showSort(window, font, sort, p, m);
                }
                else{
                    appliqueSort(sort, p, p);
                    showSort(window, font, sort, p, p);
                }
                return true;
            }
            else if(p.getMana() < sort.getCoutMana()){
                displayText(window, "Mana insufisant", font);
                continue;
            }
            // On revient a la liste des sorts si on change davis
            else if(!estChoixConfirmer(window, font)){
                continue;
            }
        }
        else if(choix == GO_BACK){
            return false;
        }
        else{
            displayText(window, "Choix invalide", font);
            continue;
        }
    }
}

bool isFightWon(sf::RenderWindow& window, sf::Font& font, Princeroi& p, Monstre m, int wait){
    while(p.getVie() > 0 && m.getVie() > 0){
        currentHp(window, font, p);
        currentMana(window, font, p);
        currentHp(window, font, m);
        currentMana(window, font, m);
        int choix = fightChoice(window, font); 
        switch(choix){ // Tour du hero
            case ATTACK:
                m.setVie(p.attack(m));
                showAttack(window, font, p, m, wait);
                break;
            case SORT:
                if(lancerSort(window, font, p, m))  
                    break;
                else
                    continue;
            default:
                displayText(window, "Choix invalide, reesayer", font);
                break;
        }

        if(m.getVie() > 0){ /// Le tour du monstre
            p.setVie(m.attack(p));
            showAttack(window, font, m, p, wait);
        }
        else{ // Le monstre est mort
            int xp = p.getXp() + m.getMaxVie();
            gainXp(window, font, xp);
            usleep(wait);
            p.setXp(xp);
            levelUp(window, font, p, xp, wait);
            return true;
        }
        if(p.getVie() <= 0){ // L'hero meurt
            std::string displayName = std::string(p.getNom()) + " est mort";
            displayText(window, displayName, font);            
            usleep(wait);
            return false;
        }
    }
    return false;
}

void debutAventure(sf::RenderWindow& window, sf::Font& font, int wait){
    Princeroi hero = selectionPrinceroi(window, font);
    std::string displayName = "Welcome, " + std::string(hero.getNom()) + ", " + std::string(hero.getConte());
    displayText(window, displayName, font);
    story1(window, wait);
    story2(window, wait);
    story3(window, wait);
    waitForEnter(window, font);

    // Fight vs Warior
    Monstre warior;
    initWarior(warior);
    beforeWarior(window, font, wait);
    waitForEnter(window, font);
    if(!isFightWon(window, font, hero, warior, wait))
        return;
}

void settings(sf::RenderWindow& window, sf::Font& font, int* wait){
    int choix = settingsMenu(window, font);
    switch(choix){
        case V_TEXT:
            *wait = changeTextSpeed(window, font);
            break;
        case VOL:
            displayText(window, "Pour plus tard", font);
            break;
        case EXIT_SETTINGS:
            return;
        default:
            displayText(window, "Entree invalide, reesayer", font);
            break;
    }
}

// Fonctions publiques
/*
    Affiche la liste des options
*/
void menu(sf::RenderWindow& window, sf::Font& font){
    while(1){
        afficheMainMenu(window);
        int choix = getUserInput(window); 
        cout << "choix = "<< choix << endl;
        int wait = 2000;
        switch (choix)
        {
        case START:
            debutAventure(window, font, wait);
            break;

        case LOAD:
            displayText(window, "WIP", font);
            break;

        case SETTINGS:
            system("clear");
            settings(window, font, &wait);
            break;

        case QUIT:
            displayText(window, "A bientot!", font);
            exit(0);

        default:
            displayText(window, "Choix invalide, reesayer", font);
            break;
        }
    }
}

/*
    Change l'arme du personnage choisi
*/
void changementArme(sf::RenderWindow& window, sf::Font& font, arme_s& a, Personnage& p){
    listeArmes(window, font);
    displayText(window, "Votre choix: ", font);
    int choix = getUserInput(window);
    p.changeArme(a, p, choix, window, font);
}

// Initiations des Personnages
void initPeach(Princesse& peach){
    // Princesse peach la bitch
    peach.setNum(PEACH);
    peach.setNom("Peach");
    peach.setAge(20);
    peach.setVie(100);
    peach.setMaxVie(100);
    peach.setMana(100);
    peach.setMaxMana(100);
    peach.setConte("Princesse bitch");
    peach.setArme(POELE);
    peach.setFaiblesse("Bowser");
    peach.setEtat(EVEILLE);
    peach.setDescription("L'heureuse victimme repetitive de Bowser, faut croire qu'elle fais expres.");
    peach.setXp(0);
    peach.setLevel(1);
}

void initMarior(Princeroi& marior){
    // Marior - le fake plombier
    marior.setNum(MARIOR);
    marior.setNom("Marior");
    marior.setAge(66);
    marior.setVie(100);
    marior.setMaxVie(100);
    marior.setMana(100);
    marior.setMaxMana(100);
    marior.setConte("Il adore les gros toyaux et les pipes");
    marior.setArme(GROS_TUYEAU);
    marior.setTitre("Plombier de l'extreme");
    marior.setTribu("64");
    marior.setNature("Cochon");
    marior.setEtatCivil("Stalker de Peach");
    marior.setDescription("Serait-il le cousin de mayro??");
    marior.setXp(0);
    marior.setLevel(1);
}

void initLuigior(Princeroi& luigior){
    // Luigior - le fake apprenti plombier 
    luigior.setNum(LUIGIOR);
    luigior.setNom("Luigior");
    luigior.setAge(66);
    luigior.setVie(100);
    luigior.setMaxVie(100);
    luigior.setMana(100);
    luigior.setMaxMana(100);
    luigior.setConte("Apprenti adorateur de tuyeau");
    luigior.setArme(GROS_TUYEAU);
    luigior.setTitre("Vicitimme de l'extreme");
    luigior.setTribu("64");
    luigior.setNature("Mouton");
    luigior.setEtatCivil("Suiveur");
    luigior.setDescription("On sen blc un peu de lui nn?");
    luigior.setXp(0);
    luigior.setLevel(1);
}

void initChampignouf(Princeroi& champignouf){
    // Champignouf de l'extreme 
    champignouf.setNum(CHAMPIGNOUF);
    champignouf.setNom("Champignouf");
    champignouf.setAge(22);
    champignouf.setVie(100);
    champignouf.setMaxVie(100);
    champignouf.setMana(100);
    champignouf.setMaxMana(100);
    champignouf.setConte("de l'extreme");
    champignouf.setArme(BAD_TRIP);
    champignouf.setTitre("A quand champignouf dans SSBU?");
    champignouf.setTribu("64");
    champignouf.setNature("Extreme");
    champignouf.setEtatCivil("Sponsor de Nintendo");
    champignouf.setDescription("[placeholder]");
    champignouf.setXp(0);
    champignouf.setLevel(1);
}

void initWiwax(Princeroi& wiwax){
    // Wiwax le chickenwiwi
    wiwax.setNum(WIWAX);
    wiwax.setNom("Wiwax");
    wiwax.setAge(20);
    wiwax.setVie(100);
    wiwax.setMaxVie(100);
    wiwax.setMana(100);
    wiwax.setMaxMana(100);
    wiwax.setConte("Mangeur de pastaga");
    wiwax.setArme(POULAX);
    wiwax.setTitre("Ohoho c'est wiwi et...");
    wiwax.setTribu("64");
    wiwax.setNature("Poulet braise");
    wiwax.setEtatCivil("Chickenwiwi");
    wiwax.setDescription("[placeholder]");
    wiwax.setXp(0);
    wiwax.setLevel(1);
}

void initLouloutre(Princeroi& louloutre){
    // Louloutre la secretaire
    louloutre.setNum(LOULOUTRE);
    louloutre.setNom("Louloutre");
    louloutre.setAge(20);
    louloutre.setVie(100);
    louloutre.setMaxVie(100);
    louloutre.setMana(100);
    louloutre.setMaxMana(100);
    louloutre.setConte("Investigateur de bureaux");
    louloutre.setArme(PIPE);
    louloutre.setTitre("Secretaire");
    louloutre.setTribu("64");
    louloutre.setNature("Awii");
    louloutre.setEtatCivil("Voler");
    louloutre.setDescription("[placeholder]");
    louloutre.setXp(0);
    louloutre.setLevel(1);
}

void initSinge(Princeroi& singe){
    // Les singes de 4tune
    singe.setNum(SINGE);
    singe.setNom("4singes");
    singe.setAge(4);
    singe.setVie(100);
    singe.setMaxVie(100);
    singe.setMana(100);
    singe.setMaxMana(100);
    singe.setConte("Produits de laboratoire");
    singe.setArme(FIST);
    singe.setTitre("Anti-stress");
    singe.setTribu("Mystere");
    singe.setNature("Virulent");
    singe.setEtatCivil("Inconnu");
    singe.setDescription("[placeholder]");
    singe.setXp(0);
    singe.setLevel(1);
}

// Initiations des sorts
void initRassengan(Sort& rassengan){
    rassengan.setNum(RASSENGAN);
    rassengan.setNom("rassengan");
    rassengan.setCoutMana(25);
    rassengan.setEstDisponible(true);
    rassengan.setDegat(33);
    rassengan.setElement("air");
    rassengan.setType(OFFENSIF);
    rassengan.setDescription("Azy continue a croire que t naruto...");
}

void initEclair(Sort& eclair){
    eclair.setNum(ECLAIR);
    eclair.setNom("eclair");
    eclair.setCoutMana(20);
    eclair.setEstDisponible(true);
    eclair.setDegat(30);
    eclair.setElement("electrique");
    eclair.setType(OFFENSIF);
    eclair.setDescription("T'est un pokemon maintenant?");
}

void initExplosion(Sort& explosion){
    explosion.setNum(EXPLOSION);
    explosion.setNom("explooosion !");
    explosion.setCoutMana(50);
    explosion.setEstDisponible(true);
    explosion.setDegat(80);
    explosion.setElement("neutre");
    explosion.setType(OFFENSIF);
    explosion.setDescription("Explooooooosion ! > naruto");
}

void initNoNoob(Sort& noNoob){
    noNoob.setNum(NO_NOOB);
    noNoob.setNom("no noob");
    noNoob.setCoutMana(33);
    noNoob.setEstDisponible(true);
    noNoob.setDegat(33);
    noNoob.setElement("ultime");
    noNoob.setType(OFFENSIF);
    noNoob.setDescription("cheh");
}

void initNoJohns(Sort& noJohns){
    noJohns.setNum(NO_JOHNS);
    noJohns.setNom("no johns");
    noJohns.setCoutMana(99);
    noJohns.setEstDisponible(true);
    noJohns.setDegat(99);
    noJohns.setElement("ultime");
    noJohns.setType(OFFENSIF);
    noJohns.setDescription("double cheh");
}

void initProtectionDivine(Sort& pd){
    pd.setNum(PROTECTION_DIVINE);
    pd.setNom("protection divine");
    pd.setCoutMana(15);
    pd.setEstDisponible(true);
    pd.setBuffDef(1.5);
    pd.setBuffAtk(1); 
    pd.setType(BUFF);
    pd.setDescription("Augemente la defense temporairement");
}

void initDispel(Sort& dispel){
    dispel.setNum(DISPEL);
    dispel.setNom("dispel");
    dispel.setCoutMana(10);
    dispel.setEstDisponible(true);
    dispel.setType(DEBUFF);
    dispel.setDescription("Permet d'enlever tout les buffs et debuffs. Que ce soit allie ou enemi.");
}

void initBaumeAppaisant(Sort& bp){
    bp.setNum(SOIN);
    bp.setNom("soin");
    bp.setCoutMana(15);
    bp.setEstDisponible(true);
    bp.setType(SOIN);
    bp.setDescription("Medic, I need a medic!");
    bp.setSoin(50);
}