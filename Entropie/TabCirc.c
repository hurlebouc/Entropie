//
//  TabCirc.c
//  Entropie
//
//  Created by hurlebouc on 26/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

//----------------------- LEAKS FREE ------------------------------

#include "TabCirc.h"

TabCirc* newTabCirc(TabOfChar * tableau) {
    TabCirc* obj = malloc(sizeof (TabCirc));
    obj->tableau = tableau;
    obj->clef = 0;
    return obj;
}

/*
void iniTabCirc(TabOfChar * tableau){
    tabCircGlobal = malloc(sizeof(TabCirc));
    tabCircGlobal->tableau = tableau;
    tabCircGlobal->clef = 0;
}
 */

char TabCirc_get(TabCirc* obj, unsigned long decalage, unsigned long index) {
    TabOfChar * tab = obj->tableau;
    unsigned long i = (decalage + index) % (len((Tableau*) tab));
    char res = TabOfChar_get(tab, i);
    return res;
}

/**
 * retourne 1 si "d1>d2", 0 si "d1=d2", -1 sinon.
 */

int compare(TabCirc* tabC, unsigned long d1, unsigned long d2) {
    TabOfChar* tab = tabC->tableau;
    unsigned long l = tab->longueur;
    for (int i = 0; i < l; i++) {
        if (TabOfChar_get(tab, (i + d1) % l) < TabOfChar_get(tab, (i + d2) % l)) {
            return -1;
        }
        if (TabOfChar_get(tab, (i + d1) % l) > TabOfChar_get(tab, (i + d2) % l)) {
            return 1;
        }
    }
    return 0;
}

int compareQS_r(void* p, const void* d1, const void* d2) {
    TabCirc* tabC = (TabCirc*) p;
    unsigned long dep1 = *((unsigned long*) d1);
    unsigned long dep2 = *((unsigned long*) d2);
    return compare(tabC, dep1, dep2);
}

/*
 int compareQS(const void* d1, const void* d2){
    unsigned long dep1 = *( (unsigned long*) d1);
    unsigned long dep2 = *( (unsigned long*) d2);
    return compare(tabCircGlobal, dep1, dep2);
}
 */

unsigned long rechercheDecalageIni(unsigned long t[]) {
    unsigned long index = 0;
    while (t[index] != 0) {
        index++;
    }
    return index;
}

/*
 unsigned long triRapide(unsigned long t[], unsigned long taille){
    printf("          Tri\n");
    qsort(t, taille, sizeof(long), compareQS);
    printf("          Recherche\n");
    unsigned long decalageIni = rechercheDecalageIni(t);
    return decalageIni;
}
 */

unsigned long triRapide_r(TabCirc* tabC, unsigned long t[], unsigned long taille) {
    //printf("          Tri\n");
    qsort_r(t, taille, sizeof (long), tabC, compareQS_r);
    //printf("          Recherche\n");
    unsigned long decalageIni = rechercheDecalageIni(t);
    return decalageIni;
}

void swap(unsigned long *a, unsigned long *b){
    unsigned long t=*a; *a=*b; *b=t;
}

void sort(int arr[], int beg, int end){
    if (end > beg + 1)
    {
        int piv = arr[beg], l = beg + 1, r = end;
        while (l < r)
        {
            if (arr[l] <= piv)
                l++;
            else
                swap(&arr[l], &arr[--r]);
        }
        swap(&arr[--l], &arr[beg]);
        sort(arr, beg, l);
        sort(arr, r, end);
    }
}

void triRapide(TabCirc* ref, unsigned long t[], unsigned long beg, unsigned long end, unsigned long* clef){
    if (end>beg + 1) {
        unsigned long l = beg + 1, r = end;
        while (l < r)
        {
            if (compare(ref, beg, l) >= 0){
                l++;
            } else {
                if (l==*clef) {
                    *clef = r-1;
                } else if (r-1 == *clef){
                    *clef = l;
                }
                swap(&t[l], &t[--r]);
            }
        }
        if (l-1==*clef) {
            *clef = beg-1;
        } else if (beg-1 == *clef){
            *clef = l-1;
        }
        swap(&t[--l], &t[beg]);
        triRapide(ref, t, beg, l, clef);
        triRapide(ref, t, r, end, clef);
    }
}

TabOfChar* newTabOfCharWithDerniereColonne(TabCirc* obj, ArrayList* i2d) {
    unsigned long l = (obj->tableau)->longueur;
    TabOfChar* resultat = newTabOfChar(l);
    char* res = malloc(sizeof (char) *l);
    for (unsigned long i = 0; i < l; i++) {
        res[i] = TabCirc_get(obj, *((unsigned long*) getAL(i2d, i)), l - 1);
    }
    void* aSupprimer = resultat->tableau;
    free(aSupprimer);
    resultat->tableau = res;
    return resultat;
}

unsigned long insertionTabCirc(TabCirc* ref, unsigned long decalage, ArrayList* i2d, unsigned long positionRef) {
    unsigned long l = i2d->nbrAssignees;
    unsigned long debut = 0;
    unsigned long fin = l - 1;
    while (fin - debut + 1 > 0) {
        unsigned long milieu = debut + (fin - debut + 1) / 2;
        unsigned long version = *((unsigned long*) getAL(i2d, milieu));
        if (compare(ref, decalage, version) == -1) {
            fin = milieu - 1;
        } else if (compare(ref, decalage, version) == 1) {
            debut = milieu + 1;
        } else {
            unsigned long* element = malloc(sizeof (long));
            *element = decalage;
            addAL(i2d, element, milieu);
            //i2d.add(milieu, d√©calage);
            if (milieu <= positionRef) {
                return positionRef + 1;
            } else {
                return positionRef;
            }
        }
    }
    unsigned long* element = malloc(sizeof (long));
    *element = decalage;
    addAL(i2d, element, debut);
    //i2d.add(d√©but, d√©calage);
    if (debut <= positionRef) {
        return positionRef + 1;
    } else {
        return positionRef;
    }
}

void terminateTabCirc(TabCirc* tab) {
    free(tab);
}
