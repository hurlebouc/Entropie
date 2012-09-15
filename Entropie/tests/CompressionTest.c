/*
 * File:   CompressionTest.c
 * Author: hurlebouc
 *
 * Created on 22 oct. 2011, 10:33:10
 */

#include <stdio.h>
#include <stdlib.h>
#include "Compression.h"

/*
 * Simple C Test Suite
 */

void testCompression() {
    Fichier* S = newFichier("ressources/merde.txt");
    int n = 3;
    unsigned long decoupageBWT = 1000;
    unsigned long decoupageMTF = 1000;
    unsigned long decoupageHuff = 1000;
    Fichier* result = compression(S, n, decoupageBWT, decoupageMTF, decoupageHuff, "temp/caca.bmhx");
    Fichier* temoin = newFichier("ressources/merde.txt.bmhx");
    long ecart = fequals(result, temoin);
    if (ecart != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testCompression (CompressionTest) message=La compression ne fonctionne pas (%lu)\n", ecart);
    }
}

void testDecompression() {
    Fichier* N = newFichier("ressources/merde.txt.bmhx");
    unsigned long decoupageMTF = 1000;
    unsigned long decoupageHuff = 1000;
    Fichier* result = decompression(N, decoupageMTF, decoupageHuff, "temp/caca.txt");
    Fichier* temoin = newFichier("ressources/merde.txt");
    long ecart = fequals(result, temoin);
    if (ecart != -1) {
        printf("%%TEST_FAILED%% time=0 testname=testDecompression (CompressionTest) message=La décompression ne fonctionne pas (%lu)\n", ecart);
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% CompressionTest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testCompression (CompressionTest)\n");
    testCompression();
    printf("%%TEST_FINISHED%% time=0 testCompression (CompressionTest)\n");

    printf("%%TEST_STARTED%%  testDecompression (CompressionTest)\n");
    testDecompression();
    printf("%%TEST_FINISHED%% time=0 testDecompression (CompressionTest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
