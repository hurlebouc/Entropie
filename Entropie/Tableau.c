//
//  Tableau.c
//  Entropie
//
//  Created by hurlebouc on 29/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

#include "Tableau.h"

Tableau* newTableau(unsigned long longueur, unsigned char tailleElement){
    // Objets a liberer
    void* tableau = calloc(longueur, tailleElement);
    Tableau * obj = malloc(sizeof(Tableau));
    obj->tableau = tableau;
    obj->longueur = longueur;
    obj->tailleElement = tailleElement;
    return obj;
}

TabOfPoint* newTabOfPoint(unsigned long longueur){
    Tableau* tab = newTableau(longueur, sizeof(void*));
    return (TabOfPoint*) tab;
}

TabOfChar* newTabOfChar(unsigned long longueur){
    Tableau *obj = newTableau(longueur, sizeof(char));
    // objet a liberer
    return (TabOfChar*) obj;
}

TabOfInt* newTabOfInt(unsigned long longueur){
    Tableau* obj = newTableau(longueur, sizeof(int));
    // objet a liberer
    return (TabOfInt*) obj;
}

TabOfLong* newTabOfLong(unsigned long longueur){
    Tableau* obj = newTableau(longueur, sizeof(long));
    // objet a liberer
    return (TabOfLong*) obj;
}


void * Tableau_get(Tableau * obj, unsigned long index){
    if(index>=obj->longueur){
        printf("Array out of bounds : %lu (taille : %lu)\n", index, obj->longueur);
        exit(0);
    }
    return ((obj->tableau)+index*(obj->tailleElement));
}

void* TabOfPoint_get(TabOfPoint* tab, unsigned long index){
    void** res; 
    res = Tableau_get((Tableau*) tab, index);
    return *res;
}

char TabOfChar_get(TabOfChar * obj, unsigned long index){
    char * pRes;
    pRes = Tableau_get((Tableau*) obj, index);
    return *pRes;
}

unsigned int TabOfInt_get(TabOfInt * obj, unsigned long index){
    unsigned int * pRes;
    pRes = Tableau_get((Tableau*) obj, index);
    return *pRes;
}

unsigned long TabOfLong_get(TabOfLong * obj, unsigned long index){
    unsigned long * pRes;
    pRes = Tableau_get((Tableau*) obj, index);
    return *pRes;
}


unsigned long len(Tableau * obj){
    return obj->longueur;
}

void TabOfPoint_put(TabOfPoint* tab, void* val, unsigned long index){
    if(index>=tab->longueur){
        printf("Array out of bounds : %lu (taille : %lu)\n", index, tab->longueur);
        exit(0);
    }
    void* debutTab = tab->tableau;
    void** place = (debutTab +index*(tab->tailleElement));
    *place = val;
}

void TabOfChar_put(TabOfChar* tab, char val, unsigned long index){
    if(index>=tab->longueur){
        printf("Array out of bounds : %lu (taille : %lu)\n", index, tab->longueur);
        exit(0);
    }
    void* debutTab = tab->tableau;
    char* place = (debutTab +index*(tab->tailleElement));
    *place = val;
}

void TabOfInt_put(TabOfInt* tab, unsigned int val, unsigned long index){
    if(index>=tab->longueur){
        printf("Array out of bounds : %lu (taille : %lu)\n", index, tab->longueur);
        exit(0);
    }
    void* debutTab = tab->tableau;
    unsigned int* place = (debutTab +index*(tab->tailleElement));
    *place = val;
}

void TabOfLong_put(TabOfLong* tab, unsigned long val, unsigned long index){
    if(index>=tab->longueur){
        printf("Array out of bounds : %lu (taille : %lu)\n", index, tab->longueur);
        exit(0);
    }
    void* debutTab = tab->tableau;
    unsigned long* place = (debutTab +index*(tab->tailleElement));
    *place = val;
}


void afficheTableau(Tableau* tab){
    printf("[");
    for (unsigned long i = 0; i<tab->longueur-1; i++) {
        if (tab->tailleElement == sizeof(char)) {
            printf("%d, ", TabOfChar_get((TabOfChar*) tab, i));
        } else if (tab->tailleElement == sizeof(int)) {
            printf("%d, ", TabOfInt_get((TabOfInt*) tab, i));
        } else if (tab->tailleElement == sizeof(long)){
            printf("%lu, ", TabOfLong_get((TabOfLong*) tab, i));
        }
    }
    unsigned long i = tab->longueur-1;
    if (tab->tailleElement == sizeof(char)) {
        printf("%d", TabOfChar_get((TabOfChar*) tab, i));
    } else if (tab->tailleElement == sizeof(int)) {
        printf("%d", TabOfInt_get((TabOfInt*) tab, i));
    } else if (tab->tailleElement == sizeof(long)){
        printf("%lu", TabOfLong_get((TabOfLong*) tab, i));
    }
    printf("]\n");
}

void terminateTableau(Tableau* tab){
    free(tab->tableau);
    free(tab);
}