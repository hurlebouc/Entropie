//
//  Compression.h
//  Entropie
//
//  Created by hurlebouc  on 16/10/11.
//  Copyright (c) 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file Compression.h
 * \author hurlebouc Godfoy
 * 
 * Implémente l'enchainement des algorithmes de compression.
 */

#include <stdio.h>

#ifndef FICHIER
#define FICHIER
#include "Fichier.h"
#endif

#ifndef BWT
#define BWT
#include "BWT.h"
#endif

#ifndef MTF
#define MTF
#include "MTF.h"
#endif

#ifndef HUFFMAN
#define HUFFMAN
#include "Huffman.h"
#endif

/**
 * Lance la compression BWT + MTF + Huffman
 * @param S fichier source
 * @param n intensité de la compression de Huffman. C'est le nombre de fois que 
 * l'algorythme de Huffman est répété.
 * @param decoupageBWT taille de la segmentation du fichier lors du codage BWT
 * @param decoupageMTF taille de la ségmentation du fichier lors du codage MTF
 * @param decoupageHuff taille de la ssegmentation du fichier lors de la 
 * compression de Huffman
 * @param nom chemin du fichier compressé. Si une chaine vide est donnée, le fichier 
 * sera dans le même répertoire que le fichier original
 * @param nbrMaxThreads nombre maximal de threads autorisé
 * @return fichier compressé
 */
Fichier* compression(
        Fichier* S,
        int n,
        unsigned long decoupageBWT,
        unsigned long decoupageMTF,
        unsigned long decoupageHuff,
        char* nom, int nbrMaxThreads);

/**
 * Lance la décompression Huffman + MTF + BWT
 * @param C fichier compressé
 * @param decoupageMTF taille de la segmentation lors du décodage MTF
 * @param decoupageHuff taille de la segmentation lors de la décompression de Huffman
 * @param nom chemin du fichier décompressé. Si une chaine vide est donnée, le fichier
 * décompressé sera dans le même repertoire que le fichier compressé.
 * @return 
 */
Fichier* decompression(
        Fichier* C,
        unsigned long decoupageMTF,
        unsigned long decoupageHuff,
        char* nom);