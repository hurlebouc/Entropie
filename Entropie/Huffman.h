//
//  Huffman.h
//  Entropie
//
//  Created by hurlebouc on 09/10/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file Huffman.h
 * \author hurlebouc 
 * 
 * Implémente l'algorithme de Huffman
 */

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef ARBRE
#define ARBRE
#include "Arbre.h"
#endif

#ifndef FICHIER
#define FICHIER
#include "Fichier.h"
#endif

#ifndef UTILITAIRES
#define UTILITAIRES
#include "utilitaires.h"
#endif

/**
 * Compresse le fichier original en utilisant l'agorithme de Huffman.
 * @param compteur
 * @param original
 * @param tailleDecoupage taille de segmentation du fichier à lire. Cette taille
 * n'a aucune insidence sur le résultat obtenu. Il permet juste d'optimiser l'espace mémoire.
 * @param nbrComp intensité de la compression. Représente le nombre de fois qu'est
 * répété l'agorithme.
 * @return fichier compressé
 */
Fichier* newFichier_Huff_transfo(
        Compteur* compteur,
        Fichier* original,
        unsigned long tailleDecoupage,
        int nbrComp);

/**
 * Décompresse le fichier compressé.
 * @param compteur
 * @param compresse
 * @param tailleDecoupage taille de segmentation du fichier compressé. Cette taille
 * n'a aucune insidence sur le résultat obtenu. Il permet juste d'optimiser l'espace mémoire.
 * @return fichier décompressé
 */
Fichier* newFichier_Huff_inv(
        Compteur* compteur,
        Fichier* compresse,
        unsigned long tailleDecoupage);