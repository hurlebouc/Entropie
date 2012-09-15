//
//  Arbre.c
//  Entropie
//
//  Created by hurlebouc on 30/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

//---------------------- LEAKS FREE ---------------------------

#include "Arbre.h"

Arbre* newFeuille(char caractere, unsigned long poids){
    Arbre* arbre = malloc(sizeof(Arbre));
    arbre->poids = poids;
    arbre->droit = NULL;
    arbre->gauche = NULL;
    arbre->lettre = caractere;
    arbre->codage_moyen = 0;
    arbre->profondeur = 0;
    arbre->codage_caracteres = newTabOfPoint(256);
    TabOfPoint_put(arbre->codage_caracteres, newLinkedList(), arbre->lettre+128);
    arbre->liste_caracteres = newTabOfChar(1);
    TabOfChar_put(arbre->liste_caracteres, arbre->lettre, 0);
    return arbre;
}

Arbre* newArbre(Arbre* fDroit, Arbre* fGauche){
    Arbre* arbre = malloc(sizeof(Arbre));
    arbre->poids = fDroit->poids + fGauche->poids;
    arbre->droit = fDroit;
    arbre->gauche = fGauche;
    arbre->profondeur = max(fGauche->profondeur, fDroit->profondeur) + 1;
    arbre->codage_moyen = ((1 + arbre->gauche->codage_moyen) * arbre->gauche->poids + (1 + arbre->droit->codage_moyen) * arbre->droit->poids) / arbre->poids;
    unsigned long tailleG = fGauche->liste_caracteres->longueur;
    unsigned long tailleD = fDroit->liste_caracteres->longueur;
    arbre->liste_caracteres = newTabOfChar(tailleD+tailleG);
    arbre->codage_caracteres = newTabOfPoint(256);
    for (unsigned long i = 0; i<tailleG; i++) {
        char caractere = TabOfChar_get(fGauche->liste_caracteres, i);
        TabOfChar_put(arbre->liste_caracteres, caractere, i);
        //ArrayList* codage = copieArrayList((TabOfPoint_get(fGauche->codage_caracteres, caractere+128)));
        LinkedList* codage = TabOfPoint_get(fGauche->codage_caracteres, caractere+128);
        
        //afficheListe(codage, sizeof(char));
        
        char* boolean = malloc(sizeof(char));
        *boolean = 0;
        addFirstLL(codage, boolean);
        TabOfPoint_put(arbre->codage_caracteres, codage, caractere+128);
    }
    for (unsigned long i = tailleG; i<tailleG+tailleD; i++) {
        char caractere = TabOfChar_get(fDroit->liste_caracteres, i-tailleG);
        TabOfChar_put(arbre->liste_caracteres, caractere, i);
        //ArrayList* codage = copieArrayList(TabOfPoint_get(fDroit->codage_caracteres, caractere+128));
        LinkedList* codage = TabOfPoint_get(fDroit->codage_caracteres, caractere+128);
        
        //afficheListe(codage, sizeof(char));
        
        char* boolean = malloc(sizeof(char));
        *boolean = 1;
        addFirstLL(codage, boolean);
        TabOfPoint_put(arbre->codage_caracteres, codage, caractere+128);
    }
    return arbre;
}

void merge(Arbre* recepteur, Arbre* modele){
    
}

Arbre* newCopieArbre(Arbre* a){
    Arbre* arbre = malloc(sizeof(Arbre));
    merge(arbre, a);
    return a;
}

LinkedList* getCode(Arbre* arbre, char b){
    return TabOfPoint_get(arbre->codage_caracteres, b+128);
}

char* afficheArbre(Arbre* arbre){
    char* res = malloc(33*puissance(2, arbre->profondeur) - 22);
    if(arbre->droit == NULL && arbre->gauche == NULL){
        sprintf(res, "[%d, %lu]", arbre->lettre, arbre->poids);
    } else {
        char* gauche = afficheArbre(arbre->gauche);
        char* droite = afficheArbre(arbre->droit);
        sprintf(res, "%lu, gauche(%s), droit(%s)", arbre->poids, gauche, droite);
        free(gauche);
        free(droite);
    }
    return res;
}


void terminateArbre(Arbre* arbre){
    /* Lors de la construction de l'arbre, les éléments de arbre->codage_caractère
     * du père pointent vers ce que pointent les éléments de arbre->codage_caractère
     * des fils.
     * la suppressions des objets pointés par les éléments de arbre->codage_caractère
     * des feuilles suffit donc à suprimmer les opbjets pointés par les éléments de 
     * arbre->codage_caractère de la racine.
     */
    if(arbre->droit == NULL && arbre->gauche == NULL){          // cas d'arret
        terminateTableau((Tableau*) arbre->liste_caracteres);
        for (int i = 0; i<256; i++) {
            LinkedList* aSupprimer = TabOfPoint_get(arbre->codage_caracteres, i);
            if(aSupprimer!= NULL){
                terminateLinkedListTotal(aSupprimer);
            }
        }
        terminateTableau((Tableau*) arbre->codage_caracteres);
        free(arbre);
    } else {                                                    // appel reccurent
        terminateTableau((Tableau*) arbre->liste_caracteres);
        terminateArbre(arbre->droit);
        terminateArbre(arbre->gauche);
        terminateTableau((Tableau*) arbre->codage_caracteres);
        free(arbre);
    }
}