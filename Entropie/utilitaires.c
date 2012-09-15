#include "utilitaires.h"

long max(long a, long b){
    if (a<b) {
        return b;
    }
    return a;
}

long puissance(long n, long p){
    long res = 1;
    for(long i = 0; i<p; i++){
        res = res * n;
    }
    return res;
}

TabOfChar* newTabBinAdaptatifFromInt(unsigned long b){
    // cette version donne un tableau longueur variable (en fonction de la taille de b.
    if (b != 0) {
        long l = 1 + lnX(b,2);
        TabOfChar* res = newTabOfChar(l);
        unsigned long a = b;
        for (long i = l - 1; i >= 0; i--) {
            unsigned long q = a / 2;
            unsigned char r = a - q * 2;
            TabOfChar_put(res, r, i);
            //res[i] = r;
            a = q;
        }
        return res;
    }
    TabOfChar* res = newTabOfChar(1);
    return res;
}

TabOfChar* newTabofCharFromBin(TabOfChar* codeClef){
    int l = (int) ((codeClef->longueur)/8);
    TabOfChar* res = newTabOfChar(l);
    int j = 0;
    while (j < l) {
        int puiss = 128;
        int k = 0;
        for (int i = 0; i < 8; i++) {
            k = k + TabOfChar_get(codeClef, j * 8 + i) * puiss;
            puiss = puiss / 2;
        }
        TabOfChar_put(res, (char) k-128, j);
        j++;
    }
    return res;
}

TabOfChar* newTabWithClef(unsigned long clef){
    TabOfChar* clefBin = newTabBinAdaptatifFromInt(clef);
    unsigned long n = clefBin->longueur;
    unsigned long l = ((n - 1) / 7 + 1) * 8;
    TabOfChar* codeClef = newTabOfChar(l);
    unsigned long i = 0;
    unsigned long ii = 0;
    unsigned long difference = l - n - l / 8; 
    // difference est la différence entre la taille d'un octet et la taille necessaire au codage de la clef (qui est la taille de clefBin)
    while (i < l) {
        if (i < difference) {
            TabOfChar_put(codeClef, 0, i);
            //codeClef[i] = 0;
        } else {
            TabOfChar_put(codeClef, TabOfChar_get(clefBin, ii), i);
            //codeClef[i] = clefBin[ii];
            ii++;
        }
        i++;
        if (i - (i / 8) * 8 == 7) {
            if (i == l - 1) {
                TabOfChar_put(codeClef, 0, i); // On met 0 si c'est fini et 1 sinon.
            } else {
                TabOfChar_put(codeClef, 1, i);
            }
            i++;
        }
    }
    terminateTableau((Tableau*) clefBin);
    TabOfChar* res = newTabofCharFromBin(codeClef);
    terminateTableau((Tableau*) codeClef);
    return res;
}

unsigned long lnX(unsigned long n, unsigned long base){
    unsigned long compteur = n/base;
    unsigned long res = 0;
    while(compteur != 0){
        compteur = compteur/base;
        res++;
    }
    return res;
}

unsigned long quotienEntierSup(unsigned long a, unsigned long b){
    unsigned long res = a/b;
    if (res*b != a) {
        res++;
    }
    return res;
}