
//
//  main.c
//  Entropie
//
//  Created by hurlebouc on 26/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//


#include <math.h>


#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef COMPRESSION
#define COMPRESSION
#include "Compression.h"
#endif

#define TAILLE_BWT 50000
#define TAILLE_BUFFER 1000000
#define NCOMP 3
#define NBRTHREADS 4

#define truc(){afficheLinkedList(liste,1);}

//#include <stdlib.h>

long taille(char* c){
    return strlen(c);
}


int main (int argc, const char * argv[]) {
    int cmp = 1;
    unsigned long tBWT = TAILLE_BWT;
    unsigned long tMTF = TAILLE_BUFFER;
    unsigned long tHUF = TAILLE_BUFFER;
    char* cheminFinal = "";
    int nComp = NCOMP;
    int nThreads = NBRTHREADS;
    char* cheminInitial = "";
    
        
    if (argc==1) {
        
        
        
        
        Fichier* original = newFichier("/Users/hurlebouc/Desktop/language.tar");
        Fichier* compresse = compression(original, NCOMP, TAILLE_BWT, TAILLE_BUFFER, TAILLE_BUFFER, "", NBRTHREADS);
        //Fichier* compresse = newFichier("/Users/hurlebouc/Desktop/language.tar.bmhx");
        Fichier* decompresse = decompression(compresse, TAILLE_BUFFER, TAILLE_BUFFER, "/Users/hurlebouc/Desktop/language_extr.tar");
        printf("localisation de la première erreur : %ld\n", fequals(decompresse, original));
        
        printf("fini\n");
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        return 0;
    } else if (argc >= 3) {
        for (int i = 1; i<argc; i++) {
            char premChar = *((char*)argv[i]);
            if (premChar=='-') {
                const char* argument = argv[i] + 1;
                if (strcmp(argument, "c")==0) {
                    cmp=1;
                }
                if (strcmp(argument, "d")==0) {
                    cmp=0;
                }
                if (strcmp(argument, "tBWT")==0) {
                    tBWT = atol(argv[i+1]); i++;
                }
                if (strcmp(argument, "tMTF")==0) {
                    tMTF = atol(argv[i+1]); i++;
                }
                if (strcmp(argument, "tHUF")==0) {
                    tHUF = atol(argv[i+1]); i++;
                }
                if (strcmp(argument, "o")==0) {
                    cheminFinal = (char*) argv[i+1]; i++;
                }
                if (strcmp(argument, "nComp")==0) {
                    nComp = atoi(argv[i+1]); i++;
                }
                if (strcmp(argument, "nThreads")==0) {
                    nThreads = atoi(argv[i+1]); i++;
                } 
            } else {
                cheminInitial = (char*) argv[i];
            }
        }
        
        if (cmp) {
            Fichier* original = newFichier(cheminInitial);
            compression(original, nComp, tBWT, tMTF, tHUF, cheminFinal, nThreads);
            return 0;
        } else {
            Fichier* compresse = newFichier(cheminInitial);
            decompression(compresse, tMTF, tHUF, cheminFinal);
            return 0;
        }
        
    }
    
    printf("entropie : Vous n avez pas assez d arguments\n");
    exit(EXIT_FAILURE);
}

