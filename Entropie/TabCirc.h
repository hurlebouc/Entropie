//
//  TabCirc.h
//  Entropie
//
//  Created by hurlebouc on 26/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file TabCirc.h
 * \author hurlebouc 
 */

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#include <stdio.h>

#ifndef TABLEAU
#define TABLEAU
#include "Tableau.h"
#endif

#ifndef ARRAYLIST
#define ARRAYLIST
#include "ArrayList.h"
#endif

typedef struct {
    TabOfChar * tableau;
    unsigned long clef;
} TabCirc;

/**
 * Construit un tableau circulaire à partir d'un tableau. 
 * Tout objet issu de cette fonction nécessite d'être détruit.
 * @param tableau
 */
TabCirc* newTabCirc(TabOfChar * tableau);

/**
 * Donne la valeur du caractère à la place index pour un décalage donné.
 * @param obj
 * @param decalage
 * @param index
 */
char TabCirc_get(TabCirc * obj, unsigned long decalage, unsigned long index);

/**
 * Fait un tri de t en utilisant un quicksort.
 * @param tabC référence permettant de lier chaque décalage à une chaine de caractère
 * @param t tableau des décalages
 * @param taille taille du tableau t
 * @return place de l'entier 0 dans t
 */
unsigned long triRapide_r(TabCirc* tabC, unsigned long t[], unsigned long taille);

/**
 * Donne un tableau composé des deniers éléments des chaines de caractères paramétrées.
 * N'est utilisé qu'en mono-thread
 * par les décalages contenus dans i2d.
 * @param obj reference des chaines de caractère
 * @param i2d liste des décalages
 */
TabOfChar* newTabOfCharWithDerniereColonne(TabCirc* obj, ArrayList* i2d);

/**
 * Insert une chaine de caractère (qui est sous forme d'un décalage de la chaine 
 * de référence dans la liste des décalage de manière alphabetique.
 * Cette fonction n'est utilisée qu'en mono-tread
 * @param ref chaine de référence à partir duquel sont décalées les autres.
 * @param decalage 
 * @param i2d liste des décalages
 * @param positionRef position de la chaine intitiale (aucun décalage par rapport
 * à la chaine de référence) avant insertion
 * @return position de la chaine initiale (aucun décalage par rapport
 * à la chaine de référence) après insertion.
 */
unsigned long insertionTabCirc(TabCirc* ref, unsigned long decalage, ArrayList* i2d, unsigned long positionRef);


/**
 * Détruit un tableau circulaire mais pas ses champs.
 * @param tab
 */
void terminateTabCirc(TabCirc* tab);

//TabCirc* tabCircGlobal;