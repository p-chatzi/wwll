#ifndef MODELE_H
#define MODELE_H

#include <iostream>
#include <cstring>

using namespace std;

#define MAX_INPUT 100

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

    NB_OPTIONS
}menu_e;

typedef enum{
    V_TEXT,
    VOL,
    EXIT_SETTINGS,

    NB_SETTINGS
}settings_e;

typedef struct{
    char nom[MAX_INPUT];
    int option;
}menu_s;

extern menu_s map_menu[NB_OPTIONS];

typedef struct{
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

class Personnage{
    private:
        int num;
        char nom[MAX_INPUT];
        int age;
        int vie;
        char conte[MAX_INPUT];
        int arme;
    public:
    // Getters
        int getNum(){return num;}
        int getAge(){return age;}
        int getVie(){return vie;}
        int getArme(){return arme;}
        char* getNom(){return nom;}
        char* getConte(){return conte;}
    // Setters
        void setNum(int n){num = n;}
        void setAge(int a){age = a;}
        void setVie(int v){vie = v;}
        void setArme(int a){arme = a;}
        void setNom(const char n[MAX_INPUT]){strcpy(nom, n);}
        void setConte(const char c[MAX_INPUT]){strcpy(conte, c);}
    // Methods
        void changeArme(arme_s& arme, Personnage& p,int choix){
            strcpy(arme.type, map_armes[choix].type);
            arme.num = map_armes[choix].num;
            arme.points = map_armes[choix].points;
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
        void getPrincesse(){ // Afficher()
            cout << "ID/Num: " << getNum() << endl;
            cout << "Nom: " << getNom() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Vie: " << getVie() << endl;
            cout << "Conte: " << getConte() << endl;
            cout << "Arme: " << getArme() << endl;
            cout << "Faiblesse:" << faiblesse << endl;
            cout << "Etat:" << etat << endl;
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
        void getPrinceroi(){
            cout << endl;
            cout << "ID/Num: " << getNum() << endl;
            cout << "Nom: " << getNom() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Vie: " << getVie() << endl;
            cout << "Conte: " << getConte() << endl;
            cout << "Arme: " << getArme() << endl;
            cout << "Titre: " << titre << endl;
            cout << "Tribu: " << tribu << endl;
            cout << "Nature: " << nature << endl;
            cout << "Etat civil: " << etatCivil << endl << endl;
        }

        int attack(Personnage p){return p.getVie() - map_armes[getArme()].points;}
        // void sauve(Princesse p, int nbPoint){}
        // void heal(){if(getVie() <= 50){ (getVie() + 50); }}
};

class Monstre : public Personnage{
    private:
        char type[MAX_INPUT];
        char couleur[MAX_INPUT];
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

        void getMonstre(){
            cout << endl;
            cout << "ID/Num: " << getNum() << endl;
            cout << "Nom: " << getNom() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Vie: " << getVie() << endl;
            cout << "Conte: " << getConte() << endl;
            cout << "Arme: " << getArme() << endl;
            cout << "Type: " << getType() << endl;
            cout << "Couleur: " << getCouleur() << endl;
            cout << "Force: " << getForce() << endl;
            cout << "Gentil: " << getGentil() << endl;
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

#endif // MODELE_H