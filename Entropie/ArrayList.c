//
//  ArrayList.c
//  Entropie
//
//  Created by hurlebouc on 26/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

#include "ArrayList.h"

/* -------------------------------------------------------------------- *
 *                          LINKEDLIST                                  *
 * -------------------------------------------------------------------- */

LinkedList* newLinkedList() {
    LinkedList* res = malloc(sizeof (LinkedList));
    res->valeur = NULL;
    res->prec = NULL;
    res->suiv = NULL;
    res->dernier = res;
    res->longueur = 0;
    return res;
}

unsigned long sizeExtLL(LinkedList* liste) {
    if (liste->valeur == NULL) {
        return 0;
    }
    LinkedList* position = liste;
    unsigned long res = 0;
    while (position != NULL) {
        res++;
        position = position->suiv;
    }
    return res;
}

unsigned long sizeLL(LinkedList* liste) {
    return liste->longueur;
}



void addLastLL(LinkedList* liste, void* element) {
    if (sizeLL(liste) == 0) {
        liste->longueur++;
        liste->valeur = element;
    } else {
        liste->longueur++;
        LinkedList* nouv = newLinkedList();
        nouv->valeur = element;
        (liste->dernier)->suiv = nouv;
        nouv->prec = liste->dernier;
        liste->dernier = nouv;
    }
}

void addFirstLL(LinkedList* liste, void* element) {
    if (sizeLL(liste) == 0) {
        liste->longueur++;
        liste->valeur = element;
    } else {
        liste->longueur++;
        LinkedList* nouv = newLinkedList();
        nouv->valeur = liste->valeur;
        nouv->suiv = liste->suiv;
        nouv->prec = liste;
        if (liste->suiv != NULL) {
            (liste->suiv)->prec = nouv;
        }
        liste->valeur = element;
        liste->suiv = nouv;
        if (nouv->suiv == NULL) {
            liste->dernier = nouv;
        }
    }
}

void addLL(LinkedList* liste, void* element, unsigned long index) {
    if (index == 0) {
        addFirstLL(liste, element);
        return;
    }
    unsigned long l = sizeLL(liste);
    if (index == l) {
        addLastLL(liste, element);
        return;
    }
    if (index > l) {
        printf("list out of bounds : %lu (taille : %lu)", index, l);
        exit(1);
    }
    liste->longueur++;
    LinkedList* position = liste->suiv;
    for (unsigned long i = 1; i < index; i++) {
        position = position->suiv;
    }
    LinkedList* nouv = newLinkedList();
    nouv->valeur = element;
    nouv->prec = position->prec;
    nouv->suiv = position;
    (position->prec)->suiv = nouv;
    position->prec = nouv;
}

void addAllLL(LinkedList* recepteur, LinkedList* source) {
    if (source->longueur == 0) {
        return;
    }
    LinkedList* position = source;
    while (position != NULL) {
        addLastLL(recepteur, position->valeur);
        position = position->suiv;
    }
}

void addAllLL2(LinkedList* recepteur, LinkedList* source) {
    printf("taille de la recepteur: %lu et du source:%lu\n",recepteur->longueur,source->longueur);
    afficheLinkedList(recepteur, 1);
    afficheLinkedList(source, 1);
    if (source->longueur == 0) {
        afficheLinkedList(recepteur, 1);
        return;
    }
    if (recepteur->longueur == 0) {
        recepteur->dernier=source->dernier;
        recepteur->suiv=source->suiv;
        recepteur->longueur=source->longueur;
        recepteur->valeur = source->valeur;
        afficheLinkedList(recepteur, 1);
        return;
        
    }
    LinkedList* nouv = newLinkedList();
    nouv->valeur = source->valeur;
    nouv->suiv = source->suiv;
    nouv->prec = source->prec;
    nouv->longueur = source->longueur;
    nouv->dernier = source->dernier;
    
    recepteur->dernier->suiv = nouv;
    nouv->prec = recepteur->dernier;
    recepteur->dernier = nouv->dernier;
    recepteur->longueur += nouv->longueur;
    afficheLinkedList(recepteur, 1);
    return;
}

void addLastCharLL(LinkedList* liste, char c) {
    char* element = malloc(sizeof (char));
    *element = c;
    addLastLL(liste, element);
}

void* getLastLL(LinkedList* liste) {
    return (liste->dernier)->valeur;
}

void* getFirstLL(LinkedList* liste) {
    return liste->valeur;
}

void* getLL(LinkedList* liste, unsigned long index) {
    if (index >= liste->longueur) {
        printf("list out of bounds : %lu (taille : %lu)", index, liste->longueur);
        exit(1);
    }
    LinkedList* position = liste;
    for (unsigned long i = 0; i < index; i++) {
        position = position->suiv;
    }
    return position->valeur;
}

char getCharLL(LinkedList* liste, unsigned long index) {
    return *((char*) getLL(liste, index));
}

void* removeLastLL(LinkedList* liste) {
    unsigned long l = liste->longueur;
    if (l == 0) {
        printf("La liste est deja vide");
        exit(2);
    }
    if (l == 1) {
        liste->longueur--;
        void* res = liste->valeur;
        liste->valeur = NULL;
        return res;
    }
    LinkedList* dernier = liste->dernier;
    (dernier->prec)->suiv = NULL;
    liste->dernier = dernier->prec;
    liste->longueur--;
    void* res = dernier->valeur;
    free(dernier);
    dernier = NULL;
    return res;
}

void* removeFirstLL(LinkedList* liste) {
    if (liste->longueur == 0) {
        printf("La liste est deja vide");
        exit(2);
    }
    if (liste->longueur == 1) {
        liste->longueur--;
        void* res = liste->valeur;
        liste->valeur = NULL;
        return res;
    }
    LinkedList* deuxieme = liste->suiv;
    void* res = liste->valeur;
    liste->valeur = deuxieme->valeur;
    liste->suiv = deuxieme->suiv;
    liste->longueur--;
    if (liste->dernier == deuxieme) {
        liste->dernier = liste;
    } else {
        (deuxieme->suiv)->prec = liste;
    }
    free(deuxieme);
    deuxieme = NULL;
    return res;
}

void* removeAtIndexLL(LinkedList* liste, unsigned long index) {
    if (index == 0) {
        return removeFirstLL(liste);
    }
    if (index == liste->longueur - 1) {
        return removeLastLL(liste);
    }
    liste->longueur--;
    LinkedList* aSupprimer = liste;
    for (unsigned long i = 0; i < index; i++) {
        aSupprimer = aSupprimer->suiv;
    }
    //ArrayList* aSupprimer = get(liste, index);
    (aSupprimer->prec)->suiv = aSupprimer->suiv;
    (aSupprimer->suiv)->prec = aSupprimer->prec;
    void* res = aSupprimer->valeur;
    free(aSupprimer);
    aSupprimer = NULL;
    return res;
}

void removeElementLL(LinkedList* liste, void* element) {
    unsigned long l = liste->longueur;
    LinkedList* position = liste;
    void* val = position->valeur;
    unsigned long i = 0;
    while (i < l && val != element) {
        i++;
        position = position->suiv;
        val = position->valeur;
    }
    if (val != element) { // en fait val = NULL
        printf("Element non present dans la liste");
        exit(3);
    }
    if (i == 0) {
        removeFirstLL(liste);
        return;
    }
    if (i == l - 1) {
        removeLastLL(liste);
        return;
    }
    liste->longueur--;
    (position->prec)->suiv = position->suiv;
    (position->suiv)->prec = position->prec;
    free(position);
    position = NULL;
}

unsigned long indexOfLL(LinkedList* liste, void* element) {
    unsigned long l = liste->longueur;
    unsigned long index = 0;
    LinkedList* position = liste;
    void* val = position->valeur;
    while (index < l && val != element) {
        index++;
        position = position->suiv;
        val = position->valeur;
    }
    if (val != element) { // en fait val = NULL
        printf("Element non present dans la liste");
        exit(3);
    }
    return index;
}

/**
 *
 * @param liste
 * @param element
 * @return
 */
long indexOfCharLL(LinkedList* liste, char element) {
    unsigned long l = liste->longueur;
    if (l == 0) {
        return -1;
    }
    long index = 0;
    LinkedList* position = liste;
    char val = *((char*) position->valeur);
    while (index < l && val != element) {
        index++;
        position = position->suiv;
        if (position != NULL) {
            val = *((char*) position->valeur);
        }
    }
    if (val != element) { // en fait val = NULL
        return -1;
    }
    return index;
}

void terminateLinkedList(LinkedList* liste) {
    LinkedList* position = liste->dernier;
    while (position != liste) {
        LinkedList* prec = position->prec;
        free(position);
        position = prec;
    }
    free(liste);
    liste = NULL;
}

void terminateLinkedListTotal(LinkedList* liste) {
    LinkedList* position = liste->dernier;
    while (position != liste) {
        LinkedList* prec = position->prec;
        free(position->valeur);
        free(position);
        position = prec;
    }
    free(liste);
    liste = NULL;
}

void afficheLinkedList(LinkedList* liste, short tailleElement) {
    if (liste->longueur == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    if (tailleElement == sizeof (char)) {
        LinkedList* position = liste;
        while (position != NULL) {
            char val = *((char*) position->valeur);
            printf("%d", val);
            if (position->suiv != NULL) {
                printf(", ");
            }
            position = position->suiv;
        }
    } else if (tailleElement == sizeof (int)) {
        LinkedList* position = liste;
        while (position != NULL) {
            int val = *((int*) position->valeur);
            printf("%d", val);
            if (position->suiv != NULL) {
                printf(", ");
            }
            position = position->suiv;
        }
    } else if (tailleElement == sizeof (long)) {
        LinkedList* position = liste;
        while (position != NULL) {
            long val = *((long*) position->valeur);
            printf("%ld", val);
            if (position->suiv != NULL) {
                printf(", ");
            }
            position = position->suiv;
        }
    }
    printf("]\n");
}

//----------- EXPERIMENTAL-------------------------------

LinkedList* newLinkedListFromCopieLinkedList(LinkedList* liste) {
    if (liste == NULL) {
        return NULL;
    }
    LinkedList* nouv = newLinkedList();
    nouv->valeur = liste->valeur;
    nouv->suiv = newLinkedListFromCopieLinkedList(liste->suiv);
    if (nouv->suiv != NULL) {
        (nouv->suiv)->prec = nouv;
        nouv->dernier = (nouv->suiv)->dernier;
    } else {
        nouv->dernier = nouv;
    }
    return nouv;
}

TabOfChar* LLversTOC(LinkedList* liste) {// Ne marche 
    TabOfChar* listeTrans = newTabOfChar(liste->longueur);
    unsigned long i = 0;
    while (liste->longueur > 0) {
        char* valeur=getFirstLL(liste);
        TabOfChar_put(listeTrans, *valeur, i);
        i++;
    }
    return listeTrans;
}

/* -------------------------------------------------------------------- *
 *                          ARRAYLIST                                   *
 * -------------------------------------------------------------------- */

ArrayList* newArrayListFromLinkedList(LinkedList* ll){//transforme en AL rempli
    ArrayList* al=newArrayList(ll->longueur);
    while(ll->longueur!=0){
        addLastAL(al,removeFirstLL(ll));}//je démonte la liste ll
    return al;
}

ArrayList* newArrayList(unsigned long l) {
    ArrayList* res = malloc(sizeof (ArrayList));
    res->tailleMax = l;
    res->nbrAssignees = 0;
    res->tableau = malloc(sizeof (void*) *l);
    //printf("borne inf tableau : %lu\n", res->tableau);
    //printf("borne sup tableau : %lu\n", res->tableau + sizeof(void*)*l);
    return res;
}

unsigned long sizeAL(ArrayList* liste) {
    return liste->nbrAssignees;
}

void addLastAL(ArrayList* liste, void* element) {
    // -------------- à supprimer après débogage -------------
    if (sizeAL(liste) >= liste->tailleMax) {
        printf("l'array liste est pleine");
        exit(EXIT_FAILURE);
    }
    //--------------------------------------------------------
    void** position = liste->tableau + (liste->nbrAssignees) * sizeof (void*); //pourquoi maintenant c'est des void**?

    *position = element;
    liste->nbrAssignees++;

}

void addAL(ArrayList* liste, void* element, unsigned long index) {

    if (index == liste->nbrAssignees) {
        addLastAL(liste, element);
        return;
    }

    // -------------- à supprimer après débogage -------------
    if (sizeAL(liste) >= liste->tailleMax) {
        printf("l'array liste est pleine");
        exit(EXIT_FAILURE);
    }
    //--------------------------------------------------------


    void* position = (liste->tableau) + sizeof (void*) *(liste->nbrAssignees);
    void** actuel = position;
    void** precedent = position - sizeof (void*);
    for (unsigned long i = liste->nbrAssignees; i >= index + 1; i--) {
        //printf("i dans addfirst: %lu\n",i);
        //tab[i] = tab[i-1];
        *actuel = *precedent;
        position = position - sizeof (void*);
        actuel = position;
        precedent = position - sizeof (void*);
    }
    *actuel = element;
    liste->nbrAssignees++;
}

void addFirstAL(ArrayList* liste, void* element) {
    addAL(liste, element, 0);
    return;
}

void addAllAL(ArrayList* recepteur, ArrayList* source) {

    // -------------- à supprimer après débogage -------------
    if (recepteur->nbrAssignees + source->nbrAssignees > recepteur->tailleMax) {
        printf("l'array liste est pleine");
        exit(EXIT_FAILURE);
    }
    //--------------------------------------------------------
    if (source->nbrAssignees == 0) {
        return;
    }
    memcpy(recepteur->tableau + recepteur->nbrAssignees * sizeof (void*), source->tableau, source->nbrAssignees * sizeof (void*));
    recepteur->nbrAssignees += source->nbrAssignees;
}

void addLastCharAL(ArrayList* liste, char c) {
    char* element = malloc(sizeof (char));
    *element = c;
    addLastAL(liste, element);
}

void* getAL(ArrayList* liste, unsigned long index) {

    // -------------- à supprimer après débogage -------------
    if (index >= liste->nbrAssignees) {
        printf("L'arrayList n'est pas assez longue"); //modif
        exit(EXIT_FAILURE);
    }
    //--------------------------------------------------------

    void** res = (liste->tableau) + index * sizeof (void*);
    return *res;
}

char getCharAL(ArrayList* liste, unsigned long index) {//un get qui renvoie l'element lu comme un char
    char* res = getAL(liste, index);
    //printf("%lx\n", res);
    return *res;
}

void* getLastAL(ArrayList* liste) {
    return getAL(liste, liste->nbrAssignees - 1);
}

void* getFirstAL(ArrayList* liste) {
    return getAL(liste, 0);
}

void* removeLastAL(ArrayList* liste) {//renvoie l'élément supprimé

    // -------------- à supprimer après débogage -------------
    if (liste->nbrAssignees == 0) {
        printf("la liste est vide");
        exit(EXIT_FAILURE);
    }
    //--------------------------------------------------------

    void* aSupprimer = getLastAL(liste);
    liste->nbrAssignees--;
    return aSupprimer;
}

void* removeAtIndexAL(ArrayList* liste, unsigned long index) {//renvoie l'élément enlevé
    // -------------- à supprimer après débogage -------------
    if (index >= liste->nbrAssignees) {
        printf("L'arrayList n'est pas assez longue"); //modif
        exit(EXIT_FAILURE);
    }
    //--------------------------------------------------------
    if (index == liste->nbrAssignees - 1) {
        return removeLastAL(liste);
    }
    void* aSupprimer = getAL(liste, index);
    //tab[i] = tab[i+1]
    void* position = liste->tableau + index * sizeof (void*);
    void** actuel = position;
    void** suivant = position + sizeof (void*);
    for (unsigned long i = index; i <= liste->nbrAssignees - 2; i++) {
        *actuel = *suivant;
        position += sizeof (void*);
        actuel = position;
        suivant = position + sizeof (void*);
    }
    liste->nbrAssignees--;
    return aSupprimer;
}

long indexOfAL(ArrayList* liste, void* element) {
    unsigned long l = liste->nbrAssignees;
    unsigned long i = 0;
    while (i < l && getAL(liste, i) != element) {
        i++;
    }
    if (i == l) {
        return -1;
    }
    return (long) i;
}

long indexOfCharAL(ArrayList* liste, char element) {
    unsigned long l = liste->nbrAssignees;
    unsigned long i = 0;
    while (i < l && getCharAL(liste, i) != element) {
        i++;
    }
    if (i == l) {
        return -1;
    }
    return (long) i;
}

void terminateArrayList(ArrayList* liste) {
    free(liste->tableau);
    free(liste);
}

/* cette fonction ne marche que lorsque l'arraylist ne contient que 
 * des types simples. OUI MAIS PK?
 */
void terminateArrayListTotal(ArrayList* liste) {
    for (unsigned long i = 0; i < liste->nbrAssignees; i++) {
        free(getAL(liste, i));
    }
    terminateArrayList(liste);
}

void afficheArrayList(ArrayList* liste) { // ne marche que pour des char
    void* position = liste->tableau;
    void** tab = position;
    unsigned long l = liste->nbrAssignees;
    if (l == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (unsigned long i = 0; i < l - 1; i++) {
        char* val = *tab;
        printf("%d, ", *val);
        position = position + sizeof (void*);
        tab = position;
    }
    char* derniereVal = *tab;
    printf("%d]\n", *derniereVal);
}

