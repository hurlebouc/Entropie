//
//  Compression.c
//  Entropie
//
//  Created by hurlebouc  on 16/10/11.
//  Copyright (c) 2011 Mines de Nancy. All rights reserved.
//


#include "Compression.h"

Fichier* compression(Fichier* S, int n, unsigned long decoupageBWT, unsigned long decoupageMTF, unsigned long decoupageHuff, char* nom, int nbrMaxThreads) {
    printf("Fichier : %s\nNombre compression : %d\nDecoupage BWT : %lu\nDecoupage MTF : %lu\nDecoupage Huffman : %lu\nChemin final : %s\nNombre de threads : %d\n\n", S->chemin, n, decoupageBWT, decoupageMTF, decoupageHuff, nom, nbrMaxThreads);
    Compteur* sem = newCompteur(fsize(S)*2 * (n + 1));
    Fichier* L = newFichier_BWT_transfo_thread(sem, S, decoupageBWT, nbrMaxThreads);
    //Fichier* L = newFichier_BWT_transfo(sem, S, decoupageBWT);
    Fichier* M = newFichier_MTF_transfo(sem, L, decoupageMTF);
    removeFichier(L);
    Fichier* N = newFichier_Huff_transfo(sem, M, decoupageHuff, n);
    removeFichier(M);
    char* nouvChemin;
    if (strlen(nom) == 0) {
        nouvChemin = malloc(strlen(S->chemin) + 1 + 5);
        sprintf(nouvChemin, "%s.bmhx", S->chemin);
    } else {
        nouvChemin = nom; // attentio ici à la gestion mémoire ...
    }
    rename(N->chemin, nouvChemin);
    Fichier* compresse = newFichier(nouvChemin);
    return compresse;
}

Fichier* decompression(Fichier* N, unsigned long decoupageMTF, unsigned long decoupageHuff, char* nom) {
    printf("Fichier : %s\nDecoupage MTF : %lu\nDecoupage Huffman : %lu\nChemin final : %s\n\n", N->chemin, decoupageMTF, decoupageHuff, nom);
    Compteur* sem = newCompteur(10);
    Fichier* M = newFichier_Huff_inv(sem, N, decoupageHuff);
    sem->value = 0;
    sem->maximum = sem->maximum * 3;
    Fichier* L = newFichier_MTF_inv(sem, M, decoupageMTF);
    removeFichier(M);
    Fichier* S = newFichier_BWT_inv(sem, L);
    removeFichier(L);
    
    char* nouvChemin;
    if (strlen(nom) == 0) {
        unsigned long tailleStringN = strlen(N->chemin);
        nouvChemin = malloc(tailleStringN + 1 - 5);
        strncpy(nouvChemin, N->chemin, tailleStringN - 5);
        nouvChemin[tailleStringN - 5] = '\0';
    } else {
        nouvChemin = nom;
    }


    //printf("Longueur de N : %lu\n", strlen(N->chemin));
    //printf("%s\n", nouvChemin);
    //printf("%d\n", strlen(nouvChemin));

    rename(S->chemin, nouvChemin);
    Fichier* decompresse = newFichier(nouvChemin);
    //printf("%d\n", strlen(nouvChemin));
    return decompresse;
}

