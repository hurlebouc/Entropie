//
//  Semaphore.h
//  Entropie
//
//  Created by hurlebouc on 03/10/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file Semaphore.h
 * \author hurlebouc 
 * 
 * Implémente un compteur
 */

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

typedef struct{
    unsigned long value;
    unsigned long maximum;
}Compteur;


/**
 * Création d'un compteur
 * @param max valeur maximal du compteur
 */
Compteur* newCompteur(unsigned long max);

/**
 * Ajoutustement de la valeur du compteur
 * @param sem
 * @param i
 */
void setValue(Compteur* sem, unsigned long i);