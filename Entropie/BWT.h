//
//  BWT.h
//  Entropie
//
//  Created by hurlebouc on 26/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file BWT.h
 * \author hurlebouc 
 * 
 * Implémente le codage de Burrow-Wheeler
 */

#include <math.h>

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

#ifndef TABCIRC
#define TABCIRC
#include "TabCirc.h"
#endif

#ifndef FICHIER
#define FICHIER
#include "Fichier.h"
#endif

#ifndef UTILITAIRES
#define UTILITAIRES
#include "utilitaires.h"
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef MATH
#define MATH
#include <math.h>
#endif

#ifndef PTHREAD
#define PTHREAD
#include <pthread.h>
#endif

#ifndef UNISTD
#define UNISTD
#include <unistd.h>
#endif

typedef struct condNbrTheads {
    pthread_mutex_t* triggering;
    pthread_cond_t* condition;
    unsigned long currentNbrThreads;
    unsigned long maxNbrThreads;

} CondNbrTheads;

typedef struct ParamLanceur {
    CondNbrTheads* runningThreads;
    Fichier* fichier;
    LinkedList* listeTache;
    unsigned long tailleDecoupage;
    Compteur* sem;
    pthread_mutex_t* accesListe;

} ParamLanceur;

typedef struct Commande {
    unsigned long refCommande;
    TabOfChar* buffer;
    Compteur* sem;
    TabOfChar* res;
    pthread_attr_t* attribut;
    pthread_t* pid;
    CondNbrTheads* runningThreads;

} CommandeBWT;

/**
 * Codage BWT du fichier original en découpant le fichier en segments de taille 
 * tailleDecoupage. Cette algorythme en mono-thread.
 * @param compteur
 * @param original
 * @param tailleDecoupage taille de ségmentation du fichier. Plus cette taille
 * est grande, plus la compression est efficace au sens de Huffman.
 * @return fichier codé
 */
Fichier* newFichier_BWT_transfo(
        Compteur* compteur,
        Fichier* original,
        unsigned long tailleDecoupage);

/**
 * Codage BWT du fichier original. Cette algorythme en multi-threads.
 * @param compteurs
 * @param original
 * @param tailleDecoupage taille de ségmentation du fichier. Plus cette taille
 * est grande, plus la compression est efficace au sens de Huffman.
 * @param nbrMaxThreads nombre maximal de threads utilisables
 * @return fichier codé
 */
Fichier* newFichier_BWT_transfo_thread(
        Compteur* compteur,
        Fichier* original,
        unsigned long tailleDecoupage,
        unsigned long nbrMaxThreads);

/**
 * Décodage BWT du fichier compresse.
 * @param compteur
 * @param compresse
 * @return fichier décodé
 */
Fichier* newFichier_BWT_inv(Compteur* compteur, Fichier* compresse);


////-------------------------------------------------------------------------
//
//unsigned long readClefFromArray(TabOfChar* L);
//unsigned long readClefFromArray2(TabOfChar* L);
//
//long readTailleSegment(FILE* lecteur);
//long readTailleSegment2(FILE* lecteur);