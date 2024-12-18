#include <iostream>
#include <unistd.h>

#include "controlleur.h"
#include "modele.h"
#include "vue.h"

using namespace std;

// testing branch change

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

void evolve(Princeroi& p, int wait){
    if(p.getLevel() % 5 == 0){
        cout << endl << p.getNom() << " que se passe t-il?..." << endl;
        usleep(wait);
        cout << p.getNom() << " se tranforme..." << endl;
        usleep(wait);
        cout << p.getNom() << " evolue en: ";
        evolutionChampignouf(p);
        cout << p.getNom() << "!" << endl << endl;
    }
}

void levelUp(Princeroi& p, int gainXp, int wait){
    if((p.getXp() / 100) > p.getLevel()){
        // Up max vie et mana et regen
        p.setLevel(p.getLevel() + 1);
        p.setMaxVie(p.getMaxVie() + 10);
        p.setMaxMana(p.getMaxMana() + 5);
        p.setVie(p.getMaxVie());
        p.setMana(p.getMaxMana()); 
        cout << endl << "Level up - Vous passez Lvl." << p.getLevel() << endl;
        currentHp(p);
        currentMana(p);
        evolve(p, wait);
    }
}

void appliqueSort(Sort& sort, Personnage& lanceur, Personnage& cible){
    if(sort.getType() == OFFENSIF){
        cible.setVie(cible.getVie() - sort.getDegat());
    }
    if(sort.getType() == DEBUFF){
        cout << "WIP" << endl;
    }
    if(sort.getType() == BUFF){
        cout << "WIP" << endl;
    }
    if(sort.getType() == SOIN)
        cible.setVie(cible.getVie() + sort.getSoin());
}

bool lancerSort(Princeroi& p, Monstre& m){
    while (1) {
        // Selection d'un sort
        int choix = choixSort(p);
        if(choix >= 0 && choix < NB_SORTS){
            // On affiche les details de ce sort
            Sort sort(choix);
            sort.getSort();
            if(estChoixConfirmer() && p.getMana() >= sort.getCoutMana()){
                // On applique si la selection est confirmer
                p.setMana(p.getMana() - sort.getCoutMana());
                if(sort.getType() == OFFENSIF || sort.getType() == DEBUFF){
                    appliqueSort(sort, p, m);
                    showSort(sort, p, m);
                }
                else{
                    appliqueSort(sort, p, p);
                    showSort(sort, p, p);
                }
                return true;
            }
            else if(p.getMana() < sort.getCoutMana()){
                cout << "Mana insufisant" << endl;
                continue;
            }
            // On revient a la liste des sorts si on change davis
            else if(!estChoixConfirmer()){
                continue;
            }
        }
        else if(choix == GO_BACK){
            return false;
        }
        else{
            cout << "Choix invalide" << endl;
            continue;
        }
        }
}

bool isFightWon(Princeroi& p, Monstre m, int wait){
    while(p.getVie() > 0 && m.getVie() > 0){
        currentHp(p);
        currentMana(p);
        currentHp(m);
        currentMana(m);
        int choix = fightChoice(); 
        switch(choix){ // Tour du hero
            case ATTACK:
                m.setVie(p.attack(m));
                showAttack(p, m, wait);
                break;
            case SORT:
                if(lancerSort(p, m))  
                    break;
                else
                    continue;
            default:
                cout << "Choix invalide, reesayer" << endl;
                break;
        }

        if(m.getVie() > 0){ /// Le tour du monstre
            p.setVie(m.attack(p));
            showAttack(m, p, wait);
        }
        else{ // Le monstre est mort
            cout << m.getNom() << " est mort" << endl;
            usleep(wait);
            int gainXp = p.getXp() + m.getMaxVie();
            p.setXp(gainXp);
            levelUp(p, gainXp, wait);
            return true;
        }
        if(p.getVie() <= 0){ // L'hero meurt
            cout << p.getNom() << " est mort" << endl;
            usleep(wait);
            return false;
        }
    }
    return false;
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
    if(!isFightWon(hero, warior, wait))
        return;
    cout << "Bravo, allez voir Peach pour une belle recompense" << endl;
    dots(wait);
    cout << "Ah merde!" << endl << "Bon vas sauvez Bowser... euh peach" << endl;
    usleep(wait);
    waitForEnter();

    // Fight vs Yipee
    Monstre yipee;
    initYipee(yipee);
    cout << "Tu scrutine le buisson devant toi..." << endl;
    usleep(wait);
    cout << "Le buisson bouge, un goomba serait encore en vie?" << endl;
    usleep(wait);
    cout << "SAUTE DESSUS!" << endl << "[insert epic battle music]" << endl;
    usleep(wait);
    waitForEnter();
    if(!isFightWon(hero, yipee, wait))
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

    // Post story for testing
    cout << endl << "Vous avez fini le mode histoire" << endl;
    cout << "Vous allez taper des warior en boucle pour l'xp" << endl;
    Monstre w1, w2, w3, w4;
    initWarior(w1);
    initWarior(w2);
    initWarior(w3);
    initWarior(w4);
    usleep(wait);
    cout << "[insert epic battle music]" << endl << endl;
    waitForEnter();
    if(!isFightWon(hero, w1, wait))
        return;
    usleep(wait);
    cout << "[insert epic battle music]" << endl << endl;
    waitForEnter();
    if(!isFightWon(hero, w2, wait))
        return;
    usleep(wait);
    cout << "[insert epic battle music]" << endl << endl;
    waitForEnter();
    if(!isFightWon(hero, w3, wait))
        return;
    usleep(wait);
    cout << "[insert epic battle music]" << endl << endl;
    waitForEnter();
    if(!isFightWon(hero, w4, wait))
        return;
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
    cout << "Votre choix: " << endl;
    int choix;
    cin >> choix;
    p.changeArme(a, p, choix);
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
}