//
//  Tableau.h
//  Entropie
//
//  Created by hurlebouc on 29/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file Tableau.h
 * \author hurlebouc 
 * 
 * Implémente la gestion de tableau
 */

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

typedef struct {
    void* tableau;
    unsigned long longueur;
    unsigned int tailleElement;
} Tableau;

typedef struct {
    void* tableau;
    unsigned long longueur;
    unsigned int tailleElement;
} TabOfPoint;

typedef struct {
    void* tableau;
    unsigned long longueur;
    unsigned int tailleElement;
} TabOfChar;

typedef struct {
    void* tableau;
    unsigned long longueur;
    unsigned int tailleElement;
} TabOfInt;

typedef struct {
    void* tableau;
    unsigned long longueur;
    unsigned int tailleElement;
} TabOfLong;

//typedef Tableau TabOfPoint;
//typedef Tableau TabOfChar;
//typedef Tableau TabOfInt;
//typedef Tableau TabOfLong;

/**
 * Crée un nouveau tableau de pointeur en mémoire. Ce type de tableau est un tableau 
 * dont les éléments sont des pointeurs.
 * Nécéssite la destruction par la fonction terminateTableau().
 * @param longueur taille du tableau
 * @return nouveau tableau
 */
TabOfPoint* newTabOfPoint(unsigned long longueur);

/**
 * Crée un nouveau tableau de caractères en mémoire.
 * Nécéssite la destruction par la fonction terminateTableau().
 * @param longueur
 * @return nouveau tableau
 */
TabOfChar* newTabOfChar(unsigned long longueur);

/**
 * Crée un nouveau tableau d'entiers en mémoire.
 * Nécéssite la destruction par la fonction terminateTableau().
 * @param longueur
 * @return 
 */
TabOfInt* newTabOfInt(unsigned long longueur);

/**
 * Crée un nouveau tableau de long en mémoire.
 * Nécéssite la destruction par la fonction terminateTableau().
 * @param longueur
 * @return 
 */
TabOfLong* newTabOfLong(unsigned long longueur);

/**
 * Donne l'adresse en mémoire du index-eme élément du tableau
 * @param obj
 * @param index
 */
void * Tableau_get(Tableau * obj, unsigned long index);

/**
 * Donne le index-eme pointeur du tableau
 * @param tab
 * @param index
 */
void* TabOfPoint_get(TabOfPoint* tab, unsigned long index);

/**
 * Donne le index-eme caractère du tableau
 * @param obj
 * @param index
 */
char TabOfChar_get(TabOfChar * obj, unsigned long index);

/**
 * Donne le index-eme entier du tableau
 * @param obj
 * @param index
 */
unsigned int TabOfInt_get(TabOfInt * obj, unsigned long index);

/**
 * Donne le index-eme long du tableau
 * @param obj
 * @param index
 */
unsigned long TabOfLong_get(TabOfLong * obj, unsigned long index);

/**
 * Écrit le pointeur au rang index.
 * @param tab
 * @param val
 * @param index
 */
void TabOfPoint_put(TabOfPoint* tab, void* val, unsigned long index);

/**
 * Écrit le caractère au rang index.
 * @param tab
 * @param val
 * @param index
 */
void TabOfChar_put(TabOfChar* tab, char val, unsigned long index);

/**
 * Écrit l'entier au rang index.
 * @param tab
 * @param val
 * @param index
 */
void TabOfInt_put(TabOfInt* tab, unsigned int val, unsigned long index);

/**
 * Écrit le long au rang index.
 * @param tab
 * @param val
 * @param index
 */
void TabOfLong_put(TabOfLong* tab, unsigned long val, unsigned long index);

/**
 * Affiche le tableau sur le log
 * @param tab
 */
void afficheTableau(Tableau* tab); //lit la valeur d'un tableau dont la longueur des cases est inférieurs à la taille d'un long

/**
 * Donne la longueur du tableau
 * @param obj
 */
unsigned long len(Tableau * obj);

/**
 * Détruit le tableau.
 * @param tab
 */
void terminateTableau(Tableau* tab);