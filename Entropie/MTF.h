//
//  MTF.h
//  Entropie
//
//  Created by hurlebouc on 07/10/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file MTF.h
 * \author hurlebouc 
 * 
 * Implémente l'agorithme Move-To-Front
 */

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef TABLEAU
#define TABLEAU
#include "Tableau.h"
#endif

#ifndef SEMAPHORE
#define SEMAPHORE
#include "Semaphore.h"
#endif

#ifndef ARRAYLIST
#define ARRAYLIST
#include "ArrayList.h"
#endif

#ifndef FICHIER
#define FICHIER
#include "Fichier.h"
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif


/**
 * Effectue un codage MTF
 * @param sem
 * @param original
 * @param tailleDecoupage taille de segmentation du fichier original. Cette taille
 * n'a aucune insidence sur le résultat obtenu. Il permet juste d'optimiser l'espace mémoire.
 * @return fichier codé
 */
Fichier* newFichier_MTF_transfo(Compteur* sem, Fichier* original, unsigned long tailleDecoupage);

/**
 * Décode un fichier en utilisant MTF
 * @param sem
 * @param compresse
 * @param tailleDecoupage taille de segmentation du fichier codé. Cette taille
 * n'a aucune insidence sur le résultat obtenu. Il permet juste d'optimiser l'espace mémoire.
 * @return fichier décodé
 */
Fichier* newFichier_MTF_inv(Compteur* sem, Fichier* compresse, unsigned long tailleDecoupage);