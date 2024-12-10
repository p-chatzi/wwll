#include "modele.h"
#include "controlleur.h"

arme_s map_armes[NB_ARMES] = {
    {"Gros tuyeau", 0, 20},
    {"Fist", 1, 10},
    {"Bad trip", 2, 15},
    {"Poele", 3, 50},
    {"Pipe", 4, 25},
    {"Poulax", 5, 22},
    {"Calin", 6, 0}};

menu_s map_menu[NB_OPTIONS] = {
    {"START", START},
    {"LOAD", LOAD},
    {"SETTINGS", SETTINGS},
    {"QUIT", QUIT}};

Princeroi::Princeroi(int num){
    setNum(num);
    switch(num){
        case MARIOR:
            initMarior(*this);
            break;
        case LUIGIOR:
            initLuigior(*this);
            break;
        case WIWAX:
            initWiwax(*this);
            break;
        case LOULOUTRE:
            initLouloutre(*this);
            break;
        case SINGE:
            initSinge(*this);
            break;
        case CHAMPIGNOUF:
            initChampignouf(*this);
            break;
        default:
            cout << "Choix invalide" << endl;
            break;
    }
}