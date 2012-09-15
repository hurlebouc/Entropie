/*
 * File:   BWTTest.c
 * Author: hurlebouc
 *
 * Created on 23 oct. 2011, 17:18:30
 */

#include <stdio.h>
#include <stdlib.h>
#include "BWT.h"

/*
 * Simple C Test Suite
 */

void testNewFichier_BWT_inv() {
    Fichier* compresse = newFichier("ressources/merde.cBWT");
    Compteur* sem = newCompteur(fsize(compresse)*3);
    Fichier* result = newFichier_BWT_inv(sem, compresse);
    Fichier* temoin = newFichier("ressources/merde.txt");
    long difference = fequals(result, temoin);
    if (difference != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testNewFichier_BWT_inv (BWTTest) message=%lu au lieu de -1\n", difference);
    }
    removeFichier(result);
}

void testNewFichier_BWT_transfo() {
    Fichier* original = newFichier("ressources/merde.txt");
    Compteur* sem = newCompteur(fsize(original));
    unsigned long tailleDecoupage = 1000;
    Fichier* result = newFichier_BWT_transfo(sem, original, tailleDecoupage);
    Fichier* temoin = newFichier("ressources/merde.cBWT");
    long difference = fequals(result, temoin);
    if (difference != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testNewFichier_BWT_transfo (BWTTest) message= %lu au lieu de -1\n", difference);
    }
    removeFichier(result);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% BWTTest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testNewFichier_BWT_inv (BWTTest)\n");
    testNewFichier_BWT_inv();
    printf("%%TEST_FINISHED%% time=0 testNewFichier_BWT_inv (BWTTest)\n");

    printf("%%TEST_STARTED%%  testNewFichier_BWT_transfo (BWTTest)\n");
    testNewFichier_BWT_transfo();
    printf("%%TEST_FINISHED%% time=0 testNewFichier_BWT_transfo (BWTTest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
