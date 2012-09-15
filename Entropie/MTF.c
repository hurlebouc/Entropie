#include "MTF.h"

//-------------------------LEAKS FREE----------------------------


/*
 * On sait que char2int est un tableau de 256 cases donc on peut 
 * se passer de la structure que j'ai mise en place.
 */

TabOfChar* newTab_MTF_transfo_aux(Compteur* sem, TabOfChar* L, unsigned long* char2int, ArrayList* int2char){
    printf("Début du codage MTF\n");
    unsigned long travail_ini = sem->value;
    unsigned long l = L->longueur;
    TabOfChar* res = newTabOfChar(l);
    int avancement = 0;
    for(unsigned long i = 0; i<l; i++){
        if ((i * 10) / l != avancement) {
            printf("%d pourcents effectues\n", (avancement + 1) * 10);
            avancement++;
        }
        char lettre = TabOfChar_get(L, i);
        unsigned long place = char2int[lettre + 128];
        TabOfChar_put(res, (char) (place - 128), i);
        char2int[lettre + 128] = 0;
        char* aSupprimer = removeAtIndexAL(int2char, place);
        free(aSupprimer);
        char* element = malloc(sizeof(char));
        * element = lettre;
        addFirstAL(int2char, element);
        for(unsigned long j = 1; j<= place; j++){
            char2int[ *((char*) getAL(int2char, j)) + 128]++;
        }
        sem->value = travail_ini + i + 1;
    }
    printf("Fin du codage MTF\n\n");
    return res;
}

Fichier* newFichier_MTF_transfo(Compteur* sem, Fichier* original, unsigned long tailleDecoupage){
    char* nouvChemin = malloc(strlen(original->chemin) + 1 + 5);
    sprintf(nouvChemin, "%s.cMTF", original->chemin);
    Fichier* compresse = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(compresse);
    FILE* lecteur = ouvrirLecture(original);
    unsigned long tailleFichier = fsize(original);
    unsigned long nombreDivisions = tailleFichier/tailleDecoupage;
    TabOfChar* buffer = newTabOfChar(tailleDecoupage);
    TabOfChar* reste = newTabOfChar(tailleFichier % tailleDecoupage);
    ArrayList* int2char = newArrayList(256);
    unsigned long char2int[256];
    for(int i = 0; i<256; i++){
        char2int[i] = i;
        char* element = malloc(sizeof(char));
        *element = i-128;
        addLastAL(int2char, element);
    }
    for(unsigned long i = 0; i<nombreDivisions; i++){
        readFlux(lecteur, buffer);
        TabOfChar* code = newTab_MTF_transfo_aux(sem, buffer, char2int, int2char);
        writeFlux(graveur, code);
        terminateTableau((Tableau*) code);
    }
    readFlux(lecteur, reste);
    TabOfChar* code = newTab_MTF_transfo_aux(sem, reste, char2int, int2char);
    writeFlux(graveur, code);
    fclose(lecteur);
    fclose(graveur);
    terminateTableau((Tableau*) code);
    terminateArrayListTotal(int2char);
    terminateTableau((Tableau*) buffer);
    terminateTableau((Tableau*) reste);
    return compresse;
}

TabOfChar* newTab_MTF_inv_aux(Compteur* sem, TabOfChar* LL, unsigned long* char2int, ArrayList* int2char){
    printf("Début du décodage MTF\n");
    unsigned long travail_ini = sem->value;
    unsigned long l = LL->longueur;
    TabOfChar* L = newTabOfChar(l);
    int avancement = 0;
    for(unsigned long i = 0; i<l; i++){
        if ((i * 10) / l != avancement) {
            printf("%d effectué\n",(avancement + 1) * 10);
            avancement++;
        }
        setValue(sem, travail_ini + i + 1);
        char code_place = TabOfChar_get(LL, i);
        int place = code_place + 128;
        char lettre = *((char*) getAL(int2char, place));
        TabOfChar_put(L, lettre, i);
        char2int[lettre + 128] = 0;
        char* aSupprimer = removeAtIndexAL(int2char, place);
        free(aSupprimer);
        char* element = malloc(sizeof(char));
        *element = lettre;
        addFirstAL(int2char, element);
        for(unsigned long j = 1; j<=place; j++){
            char2int[*((char*) getAL(int2char, j)) + 128]++;
        }
    }
    printf("Fin du décodage MTF\n\n");
    return L;
}

Fichier* newFichier_MTF_inv(Compteur* sem, Fichier* compresse, unsigned long tailleDecoupage){
    char* nouvChemin = malloc(strlen(compresse->chemin) + 1 + 5);
    sprintf(nouvChemin, "%s.iMTF", compresse->chemin);
    Fichier* decompresse = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(decompresse);
    FILE* lecteur = ouvrirLecture(compresse);
    unsigned long tailleFichier = fsize(compresse);
    unsigned long nombreDivisions = tailleFichier/tailleDecoupage;
    TabOfChar* buffer = newTabOfChar(tailleDecoupage);
    TabOfChar* reste = newTabOfChar(tailleFichier % tailleDecoupage);
    ArrayList* int2char = newArrayList(256);
    unsigned long char2int[256];
    for(int i = 0; i<256; i++){
        char2int[i] = i;
        char* element = malloc(sizeof(char));
        *element = i-128;
        addLastAL(int2char, element);
    }
    for(unsigned long i = 0; i<nombreDivisions; i++){
        readFlux(lecteur, buffer);
        TabOfChar* code = newTab_MTF_inv_aux(sem, buffer, char2int, int2char);
        writeFlux(graveur, code);
    }
    readFlux(lecteur, reste);
    TabOfChar* code = newTab_MTF_inv_aux(sem, reste, char2int, int2char);
    writeFlux(graveur, code);
    fclose(lecteur);
    fclose(graveur);
    terminateTableau((Tableau*) code);
    terminateArrayListTotal(int2char);
    terminateTableau((Tableau*) buffer);
    terminateTableau((Tableau*) reste);
    return decompresse;
}