/*
 * File:   newsimpletest.c
 * Author: hurlebouc
 *
 * Created on 23 oct. 2011, 18:18:17
 */

#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"

/*
 * Simple C Test Suite
 */

void testNewFichier_Huff_inv() {
    Fichier* compresse = newFichier("ressources/merde.cHUFF");
    Compteur* sem = newSemaphore(fsize(compresse));
    unsigned long tailleDecoupage = 1000;
    Fichier* result = newFichier_Huff_inv(sem, compresse, tailleDecoupage);
    Fichier* temoin = newFichier("ressources/merde.txt");
    long difference = fequals(result, temoin);
    if (difference != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testNewFichier_Huff_inv (newsimpletest) message=%lu au lieu de -1\n", difference);
    }
    removeFichier(result);
}

void testNewFichier_Huff_transfo() {
    Fichier* original = newFichier("ressources/merde.txt");
    Compteur* sem = newSemaphore(fsize(original));
    unsigned long tailleDecoupage = 1000;
    int nbrComp = 1;
    Fichier* result = newFichier_Huff_transfo(sem, original, tailleDecoupage, nbrComp);
    Fichier* temoin = newFichier("ressources/merde.cHUFF");
    long difference = fequals(result, temoin);
    if (difference != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testNewFichier_Huff_transfo (newsimpletest) message=%lu au lieu de -1\n", difference);
    }
    removeFichier(result);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% newsimpletest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testNewFichier_Huff_inv (newsimpletest)\n");
    testNewFichier_Huff_inv();
    printf("%%TEST_FINISHED%% time=0 testNewFichier_Huff_inv (newsimpletest)\n");

    printf("%%TEST_STARTED%%  testNewFichier_Huff_transfo (newsimpletest)\n");
    testNewFichier_Huff_transfo();
    printf("%%TEST_FINISHED%% time=0 testNewFichier_Huff_transfo (newsimpletest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
