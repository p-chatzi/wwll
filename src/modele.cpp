#include "modele.h"
#include "controlleur.h"

arme_s map_armes[NB_ARMES] = {
    {"gros tuyeau", 0, 20},
    {"fist", 1, 10},
    {"bad trip", 2, 15},
    {"poele", 3, 50},
    {"pipe", 4, 25},
    {"poulax", 5, 22},
    {"calin", 6, 0}};

menu_s map_menu[NB_OPTIONS] = {
    {"START", START},
    {"LOAD", LOAD},
    {"SETTINGS", SETTINGS},
    {"QUIT", QUIT}};


Sort::Sort(int num){
    setNum(num);
    switch(num){
        case RASSENGAN:
            initRassengan(*this);
            break;
        case ECLAIR:
            initEclair(*this);
            break;
        case EXPLOSION:
            initExplosion(*this);
            break;
        case NO_NOOB:
            initNoNoob(*this);
            break;
        case NO_JOHNS:
            initNoJohns(*this);
            break;
        case PROTECTION_DIVINE:
            initProtectionDivine(*this);
            break;
        case DISPEL:
            initDispel(*this);
            break;
        case BAUME_APPAISANT:
            initBaumeAppaisant(*this);
            break;
        default:
            break;
    }
}

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
            break;
    }
}
