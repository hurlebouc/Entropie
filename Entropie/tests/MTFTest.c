/*
 * File:   MTFTest.c
 * Author: hurlebouc
 *
 * Created on 23 oct. 2011, 17:51:11
 */

#include <stdio.h>
#include <stdlib.h>
#include "MTF.h"

/*
 * Simple C Test Suite
 */

void testNewFichier_MTF_inv() {
    Fichier* compresse = newFichier("ressources/merde.cMTF");
    Compteur* sem = newSemaphore(fsize(compresse));
    unsigned long tailleDecoupage = 1000;
    Fichier* result = newFichier_MTF_inv(sem, compresse, tailleDecoupage);
    Fichier* temoin = newFichier("ressources/merde.txt");
    long difference = fequals(result, temoin);
    if (difference != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testNewFichier_MTF_inv (MTFTest) message=%lu au lieu de -1\n", difference);
    }
    removeFichier(result);
}

void testNewFichier_MTF_transfo() {
    Fichier* original = newFichier("ressources/merde.txt");
    Compteur* sem = newSemaphore(fsize(original));
    unsigned long tailleDecoupage = 1000;
    Fichier* result = newFichier_MTF_transfo(sem, original, tailleDecoupage);
    Fichier* temoin = newFichier("ressources/merde.cMTF");
    long difference = fequals(result, temoin);
    if (difference != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testNewFichier_MTF_transfo (MTFTest) message=%lu au lieu de -1\n", difference);
    }
    removeFichier(result);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% MTFTest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testNewFichier_MTF_inv (MTFTest)\n");
    testNewFichier_MTF_inv();
    printf("%%TEST_FINISHED%% time=0 testNewFichier_MTF_inv (MTFTest)\n");

    printf("%%TEST_STARTED%%  testNewFichier_MTF_transfo (MTFTest)\n");
    testNewFichier_MTF_transfo();
    printf("%%TEST_FINISHED%% time=0 testNewFichier_MTF_transfo (MTFTest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
