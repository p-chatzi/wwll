#ifndef MODELE_H
#define MODELE_H

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <string>

#include "vue.h"
#include "controlleur.h"

using namespace std;

#define MAX_INPUT 100
#define MAX_TEXT 256

typedef enum{
    MARIOR,
    LUIGIOR,
    WIWAX,
    LOULOUTRE,
    SINGE,
    CHAMPIGNOUF,
    PEACH,
    WARIOR,
    YIPEE,

    NB_PERSO
}perso_e;

typedef enum{
    START,
    LOAD,
    SETTINGS,
    QUIT,

    NB_OPTIONS,
    GO_BACK = -1
}menu_e;


typedef enum{
    V_TEXT,
    VOL,
    EXIT_SETTINGS,

    NB_SETTINGS
}settings_e;

typedef enum{
    ATTACK,
    SORT,
    
    NB_COMBAT
}combat_e;

typedef struct{
    char nom[MAX_INPUT];
    int option;
}menu_s;

extern menu_s map_menu[NB_OPTIONS];

typedef struct arme_s{
    char type[MAX_INPUT];
    int num;
    int points;
}arme_s;

typedef enum{
    GROS_TUYEAU,
    FIST,
    BAD_TRIP,
    POELE,
    PIPE,
    POULAX,
    CALIN,

    NB_ARMES
}arme_e;

extern arme_s map_armes[NB_ARMES];

typedef enum{
    ENDORMI,
    EVEILLE,
    RIP,

    NB_ETAT
}etat_e;

// Personnages
class Personnage{
    private:
        int num;
        char nom[MAX_INPUT];
        int age;
        int vie;
        int maxVie;
        int mana;
        int maxMana;
        char conte[MAX_INPUT];
        int arme;
        int atk;
        int def;
        char description[MAX_TEXT];
        int xp;
        int level;
    public:
    // Getters
        int getNum(){return num;}
        int getAge(){return age;}
        int getVie(){return vie;}
        int getMaxVie(){return maxVie;}
        int getMana(){return mana;}
        int getMaxMana(){return maxMana;}
        int getArme(){return arme;}
        char* getNom(){return nom;}
        char* getConte(){return conte;}
        int getAtk(){return atk;}
        int getDef(){return def;}
        char* getDescription(){return description;}
        int getXp(){return xp;}
        int getLevel(){return level;}
    // Setters
        void setNum(int n){num = n;}
        void setAge(int a){age = a;}
        void setVie(int v){vie = v;}
        void setMaxVie(int mv){maxVie = mv;}
        void setMana(int m){mana= m;}
        void setMaxMana(int mm){maxMana = mm;}
        void setArme(int a){arme = a;}
        void setNom(const char n[MAX_INPUT]){strcpy(nom, n);}
        void setConte(const char c[MAX_INPUT]){strcpy(conte, c);}
        void setAtk(int a){atk = a;}
        void setDef(int d){def = d;}
        void setDescription(const char d[MAX_TEXT]){strcpy(description, d);}
        void setXp(int x){xp = x;}
        void setLevel(int l){level = l;}
    // Methods
        void changeArme(arme_s& arme, Personnage& p, int choix, sf::RenderWindow& window, sf::Font& font){
            strcpy(arme.type, map_armes[choix].type);
            arme.num = map_armes[choix].num;
            std::string displayName = "Votre nouvelle arme: " + std::string(map_armes[choix].type);
            displayText(window, displayName, font);
            p.setArme(choix);
        }
};

class Princesse : public Personnage{
    private:
        char faiblesse[MAX_INPUT];
        int etat;
    public:
        // Getters
        char* getFaiblesse(){return faiblesse;}
        int getEtat(){return etat;}
        // Setters
        void setFaiblesse(const char f[MAX_INPUT]){strcpy(faiblesse, f);}
        void setEtat(int e){etat = e;}
        // Methods
        void getPrincesse(sf::RenderWindow& window, sf::Font& font){ // Afficher()
            std::string displayName = "Num: " + std::to_string(getNum()) ;
            displayText(window, displayName, font);
            displayName = "Nom: " + std::string(getNom());
            displayText(window, displayName, font);
            displayName = "Description: " + std::string(getDescription());
            displayText(window, displayName, font); 
            displayName = "Age: " + std::to_string(getAge());
            displayText(window, displayName, font);
            displayName = "Vie: " + std::to_string(getVie());
            displayText(window, displayName, font);
            displayName = "Conte: " + std::string(getConte());
            displayText(window, displayName, font); 
            displayName = "Arme: " + std::to_string(getArme());
            displayText(window, displayName, font);
            displayName = "Faiblesse: " + std::string(getFaiblesse());
            displayText(window, displayName, font);
            displayName = "Etat: " + std::to_string(getEtat());
            displayText(window, displayName, font); 
        }
        // void uniea(Princeroi p){}
        // void proteger(Fee f){}
        // void attackrPar(Sorciere s){}
};

class Princeroi : public Personnage{
    private:
        char titre[MAX_INPUT];
        char tribu[MAX_INPUT];
        char nature[MAX_INPUT];
        char etatCivil[MAX_INPUT];
    public:
        // Contructor
        Princeroi(int num);
        // Getters
        char* getTitre(){return titre;}
        char* getTribu(){return tribu;}
        char* getNature(){return nature;}
        char* getEtatCivil(){return etatCivil;}
        // Setters
        void setTitre(const char t[MAX_INPUT]){strcpy(titre, t);}
        void setTribu(const char t[MAX_INPUT]){strcpy(tribu, t);}
        void setNature(const char n[MAX_INPUT]){strcpy(nature, n);}
        void setEtatCivil(const char ec[MAX_INPUT]){strcpy(etatCivil, ec);}
        // Methods
        void getPrinceroi(sf::RenderWindow& window, sf::Font& font){
            std::string displayName = "Num: " + std::to_string(getNum()) ;
            displayText(window, displayName, font);
            displayName = "Nom: " + std::string(getNom());
            displayText(window, displayName, font);
            displayName = "Description: " + std::string(getDescription());
            displayText(window, displayName, font); 
            displayName = "Age: " + std::to_string(getAge());
            displayText(window, displayName, font);
            displayName = "Vie: " + std::to_string(getVie());
            displayText(window, displayName, font);
            displayName = "Conte: " + std::string(getConte());
            displayText(window, displayName, font); 
            displayName = "Arme: " + std::to_string(getArme());
            displayText(window, displayName, font);
            displayName = "Titre: " + std::string(getTitre());
            displayText(window, displayName, font);
            displayName = "Tribu: " + std::string(getTribu());
            displayText(window, displayName, font);
            displayName = "Nature: " + std::string(getNature());
            displayText(window, displayName, font); 
            displayName = "Etat civil: " + std::string(getEtatCivil());
            displayText(window, displayName, font);
        }

        int attack(Personnage p){ return p.getVie() - map_armes[getArme()].points; }
        // void sauve(Princesse p, int nbPoint){}
};

class Monstre : public Personnage{
    private:
        char type[MAX_INPUT];
        char couleur[MAX_INPUT];
        // Force est redondant avec atk de Personnage 
        // Mais j'utilise force pour repondre a la demande du projet
        int force; 
        bool gentil;
    public:
        // Getters
        char* getType(){return type;}
        char* getCouleur(){return couleur;}
        int getForce(){return force;}
        bool getGentil(){return gentil;}
        // Setters
        void setType(const char t[MAX_INPUT]){strcpy(type, t);}
        void setCouleur(const char c[MAX_INPUT]){strcpy(couleur, c);}
        void setForce(int f){force = f;}
        void setGentil(bool g){gentil = g;}
        // Methods
        int attack(Personnage p){
            return p.getVie() - (force * map_armes[getArme()].points);
        }

        void getMonstre(sf::RenderWindow& window, sf::Font& font){
            std::string displayName = "Num: " + std::to_string(getNum()); 
            displayText(window, displayName, font); 
            displayName = "Nom: " + std::string(getNom());
            displayText(window, displayName, font);
            displayName = "Age: " + std::to_string(getAge());
            displayText(window, displayName, font);
            displayName = "Vie: " + std::to_string(getVie());
            displayText(window, displayName, font); 
            displayName = "Conte: " + std::string(getConte());
            displayText(window, displayName, font); 
            displayName = "Arme: " + std::to_string(getArme());
            displayText(window, displayName, font);
            displayName = "Type: " + std::string(getType());
            displayText(window, displayName, font);
            displayName = "Couleur: " + std::string(getCouleur());
            displayText(window, displayName, font);
            displayName = "Force: " + std::to_string(getForce());
            displayText(window, displayName, font);
            displayName = "Gentil: " + std::to_string(getGentil());
            displayText(window, displayName, font);
        }

        // void appartient(Personnage p){}
};

class Magique : public Personnage{
    private:
        char specialite[MAX_INPUT];
    public:
        char* getSpecialite(){return specialite;}
        void setSpecialite(const char s[MAX_INPUT]){strcpy(specialite, s);}
};

class Sorciere : public Magique{
    private:
        char couleurMagie[MAX_INPUT];
    public:
        char* getCouleurMagie(){return couleurMagie;}
        void setCouleurMagie(const char cm[MAX_INPUT]){strcpy(couleurMagie, cm);}
        // void deteste(Princesse p){}
        // void attack(Princesse p){}
        // void getSorciere(){}
};

class Fee : public Magique{
    private:
        char famille[MAX_INPUT];
    public:
        char* getFamille(){return famille;}
        void setFamille(const char f[MAX_INPUT]){strcpy(famille, f);}
        // void aime(Princesse p){}
        // void aide(Princesse p){}
        // void getFee(){}
};

// Sorts
typedef enum{
    // Offensif
    RASSENGAN,
    ECLAIR,
    EXPLOSION,
    NO_NOOB,
    NO_JOHNS,

    // Buff
    PROTECTION_DIVINE,

    // Debuff
    DISPEL,
    SILENCE,

    // Soins 
    BAUME_APPAISANT,

    NB_SORTS
}sorts_e;

typedef enum{
    OFFENSIF,
    BUFF,
    DEBUFF,
    SOIN,

    NB_TYPE_SORTS
}type_sorts_e;

class Sort{
    private:        
        int num;
        char nom[MAX_INPUT];
        int mana;
        bool estDisponible;
        int degat;
        char element[MAX_INPUT];
        float BuffDef;
        float BuffAtk;
        float debuffDef;
        float debuffAtk;
        int soin;
        int type;
        char description[MAX_TEXT];
    public:
        // Constructor
        Sort(int num);
        // Getters
        int getNum(){return num;}
        char* getNom(){return nom;}
        int getCoutMana(){return mana;}
        bool getEstDisponible(){return estDisponible;}
        int getDegat(){return degat;}
        char* getElement(){return element;}
        float getBuffDef(){return BuffDef;}
        float getBuffAtk(){return BuffAtk;}
        float getDebuffDef(){return debuffDef;}
        float getDebuffAtk(){return debuffAtk;}
        int getSoin(){return soin;}
        int getType(){return type;}
        char* getDescription(){return description;}
        // Setters
        void setNum(int n){num = n;}
        void setNom(const char n[MAX_INPUT]){strcpy(nom, n);}
        void setCoutMana(int cm){mana = cm;}
        void setEstDisponible(bool ed){estDisponible = ed;}
        void setDegat(int d){degat = d;}
        void setElement(const char e[MAX_INPUT]){strcpy(element, e);}
        void setBuffDef(float bd){BuffDef = bd;}
        void setBuffAtk(float ba){BuffAtk = ba;}
        void setDebuffDef(float dd){debuffDef = dd;}
        void setDebuffAtk(float da){debuffAtk = da;}
        void setSoin(int s){soin = s;}
        void setType(int t){type = t;}
        void setDescription(const char d[MAX_TEXT]){strcpy(description, d);}
        // Methods
        void getSort(sf::RenderWindow& window, sf::Font& font){
            std::string displayName = "Num: " + std::to_string(getNum()) ;
            displayText(window, displayName, font);
            displayName = "Nom: " + std::string(getNom());
            displayText(window, displayName, font);
            displayName = "Description: " + std::string(getDescription());
            displayText(window, displayName, font);
            displayName = "Cout en mana: " + std::to_string(getCoutMana());
            displayText(window, displayName, font);
            if(type == OFFENSIF){
                displayName = "Degats: " + std::to_string(getDegat());
                displayText(window, displayName, font);
            }
            if(type == BUFF){
                displayName = "Buff def: " + std::to_string(getBuffDef());
                displayText(window, displayName, font);
                displayName = "Buff atk: " + std::to_string(getBuffAtk());
                displayText(window, displayName, font); 
            }
            if(type == DEBUFF){
                displayName = "Debuff def: " + std::to_string(getDebuffDef());
                displayText(window, displayName, font);
                displayName = "Debuff atk: " + std::to_string(getDebuffAtk());
                displayText(window, displayName, font);
            }
            if(type == SOIN){
                displayName = "Soin: " + std::to_string(getSoin());
                displayText(window, displayName, font); 
            } 
        }
};

#endif // MODELE_H