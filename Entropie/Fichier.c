//
//  Fichier.c
//  Entropie
//
//  Created by hurlebouc on 30/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//  

// --------------------------LEAKS FREE-----------------------------------

#include "Fichier.h"

#define TAILLE_BUFFER 1000000

Fichier* newFichier(char* chemin){
    Fichier* res = malloc(sizeof(Fichier));
    res->chemin = chemin;
    return res;
}

void closeFichier(Fichier* f){
    free(f);
}

FILE* ouvrirLecture(Fichier* f){
    FILE* res = fopen(f->chemin, "rb");
    if (res == NULL) {
        printf("le fichier %s n'est pas lisible\n", f->chemin);
        exit(EXIT_FAILURE);
    }
    return res;
}

FILE* ouvrirEcriture(Fichier* f){
    return fopen(f->chemin, "wb");
}

long fequals(Fichier* f1, Fichier* f2){
    long res = -1;
    long index = 0;
    FILE* lecteur1 = ouvrirLecture(f1);
    FILE* lecteur2 = ouvrirLecture(f2);
    int val1 = fgetc(lecteur1);
    int val2 = fgetc(lecteur2);
    while (val1 == val2 && val1 != -1 && val2 != -1) {
        val1 = fgetc(lecteur1);
        val2 = fgetc(lecteur2);
        index++;
    }
    fclose(lecteur1);
    fclose(lecteur2);
    if (val1 != val2) {
        res = index;
    }
    return res;
}

void readFlux(FILE* lecteur, TabOfChar* buffer){
    char* b = buffer->tableau;
    fread(b, buffer->longueur, sizeof(char), lecteur);
}

void writeFlux(FILE* graveur, TabOfChar* buffer){
    char* b = buffer->tableau;
    fwrite(b, buffer->longueur, sizeof(char), graveur);
}

void appendFile(FILE* graveur, Fichier* queue){
    FILE* lecteur = ouvrirLecture(queue);
    unsigned long tailleFichier = fsize(queue);
    unsigned long nbrDivisions = tailleFichier/TAILLE_BUFFER;
    TabOfChar* buffer = newTabOfChar(TAILLE_BUFFER);
    TabOfChar* reste = newTabOfChar(tailleFichier % TAILLE_BUFFER);
    for (unsigned long i = 0; i<nbrDivisions; i++) {
        readFlux(lecteur, buffer);
        writeFlux(graveur, buffer);
    }
    readFlux(lecteur, reste);
    writeFlux(graveur, reste);
    terminateTableau((Tableau*) buffer);
    terminateTableau((Tableau*) reste);
    fclose(lecteur);
}

unsigned long fsize(Fichier* fichier){
    FILE * f;
    unsigned long taille;
    f = fopen(fichier->chemin, "rb");   
    fseek(f, 0, SEEK_END); /* aller a la fin du fichier */
    taille = ftell(f); /* lire l'offset de la position courante par rapport au debut du fichier */
    fclose(f);
    return taille;
}

int removeFichier(Fichier* fichier){
    return remove(fichier->chemin);
}

//-------------------------------------------------------------------------



