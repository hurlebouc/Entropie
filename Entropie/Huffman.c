//
//  Huffman.c
//  Entropie
//
//  Created by hurlebouc on 09/10/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

//----------------------- LEAKS FREE -----------------

#include "Huffman.h"


unsigned long insertion(ArrayList* listeArbre, Arbre* arbre){
    short l = (short) listeArbre->nbrAssignees;
    unsigned long p = arbre->poids;
    short i = 0;
    while (i < l && ((Arbre*) getAL(listeArbre, i))->poids > p) {
        i++;
    }
    if (i < l) {
        addAL(listeArbre, arbre, i);
    } else {
        addLastAL(listeArbre, arbre);
    }
    return i;
}

void compter(Compteur* sem, ArrayList* decompte, ArrayList* i2c, TabOfChar* c){
    unsigned long travail_ini = sem->value;
    unsigned long max = sem->maximum;
    unsigned long l = c->longueur;
    short avancement = (travail_ini * 10) / max;
    for (unsigned long i = 0; i<l; i++) {
        if (((i + travail_ini) * 10) / max != avancement) {
            printf("%d pourcent effectués\n",(avancement + 1) * 10);
            avancement++;
            //printf("%d\n",avancement);
        }
        setValue(sem, travail_ini + i + 1);
        //printf("%lu\n", travail_ini+i+1);
        char lettre = TabOfChar_get(c, i);
        long ind = indexOfCharAL(i2c, lettre);
        if (ind != -1) { // si l'élément est déjà présent dans décompte
            Arbre* a = removeAtIndexAL(decompte, ind);
            a->poids++;
            unsigned long indd = insertion(decompte, a);
            char* sup = removeAtIndexAL(i2c, ind);
            free(sup);
            char* pLettre = malloc(sizeof(char));
            *pLettre = lettre;
            addAL(i2c, pLettre, indd);
        } else {
            addLastAL(decompte, newFeuille(lettre, 1));
            char* pLettre = malloc(sizeof(char));
            *pLettre = lettre;
            addLastAL(i2c, pLettre);
        }
    }
}


ArrayList* newListWithComptage(Fichier* fichier,Compteur* sem, unsigned long tailleDecoupage){
    printf("Debut du comptage\n");
    unsigned long tailleFichier = fsize(fichier);
    unsigned long nombreDivisions = tailleFichier / tailleDecoupage;
    TabOfChar* buffer = newTabOfChar(tailleDecoupage);
    TabOfChar* reste = newTabOfChar(tailleFichier % tailleDecoupage);
    ArrayList* decompte = newArrayList(256); //ArrayList<Arbre>
    ArrayList* i2c = newArrayList(256); //ArrayList<Char>
    FILE* lecteur = ouvrirLecture(fichier);

    for (unsigned long i = 0; i<nombreDivisions; i++) {
        readFlux(lecteur, buffer);
        compter(sem, decompte, i2c, buffer);
    }
    readFlux(lecteur, reste);
    compter(sem, decompte, i2c, reste);
    fclose(lecteur);
    terminateTableau((Tableau*) buffer);
    terminateTableau((Tableau*) reste);
    terminateArrayListTotal(i2c);
    printf("Fin du comptage\n");
    return decompte;
}

Arbre* newArbrefromList(ArrayList* tab){
    // cette fonction détruit la liste tab
    int l = (int) tab->nbrAssignees;
    while(l>1){
        Arbre* dernier = removeAtIndexAL(tab, l-1);
        Arbre* avantDernier = removeAtIndexAL(tab, l-2);
        Arbre* a = newArbre(dernier, avantDernier);
        insertion(tab, a);
        l--;
    }
    return getFirstAL(tab);
}

char lireFlux(LinkedList* liste){
    // listeliée
    int res = 0;
    int puiss = 128;
    for(int i = 0; i<8; i++){
        if(liste->longueur > 0){
            res = res + ( *((int*)getFirstLL(liste)) )*puiss;
            removeFirstLL(liste);
            // je fais exprès de ne pas supprimer l'élément effacé de la
            // liste car sinon je modifierais l'arbre de codage.
        }
        puiss = puiss/2;
    }
    return (char) (res - 128);
}

TabOfInt* newTabBinFromInt_Static(char b){
    // renvoie toujours un tableau de même taille
    TabOfInt* res = newTabOfInt(8);
    int a = b + 128;
    for(int i = 7; i>= 0; i--){
        int q = a/2;
        int r = a % 2;
        TabOfInt_put(res, r, i);
        a=q;
    }
    return res;
}




LinkedList* newCode(Compteur* sem, Arbre* huff, TabOfChar* buffer, LinkedList* flux){
    // listeliée flux
    LinkedList* chuff = newLinkedList();
    unsigned long travail_ini = sem->value;
    unsigned long max = sem->maximum;
    int avancement = (int) ((travail_ini * 10)/max);
    unsigned long index = 0;
    int l = (int) (buffer->longueur);
    for(unsigned long i = 0; i<l; i++){
        if (((i + travail_ini) * 10) / max != avancement) {
            printf("%d effectué\n", (avancement + 1) * 10);
            avancement++;
        }
        setValue(sem, travail_ini + i + 1);
        char caractere = TabOfChar_get(buffer, i);
        //printf("taille du flux : %lu\n", flux->longueur);
        LinkedList* listeaajouter = getCode(huff, caractere);
        //afficheListe(listeaajouter, sizeof(char));
        
        addAllLL(flux, listeaajouter);
        while(flux->longueur >=8){
            char car = lireFlux(flux);
            index++;
            char* element = malloc(sizeof(char));
            *element = car;
            addLastLL(chuff, element);
        }
    }
    //afficheListe(chuff, sizeof(char));
    return chuff;
}

TabOfChar* newCodeInv_Aux(Arbre* huff, Arbre* a, TabOfChar* chuff, unsigned long index_ini){
    unsigned long l = chuff->longueur;
    unsigned long index = 0;
    unsigned long longueur = huff->poids;
    LinkedList* res = newLinkedList();
    //ArrayList* res = newArrayList(<#unsigned long l#>);
    int avancement = 0;
    for (unsigned long i = 0; i < l; i++) {
        if ((i * 10) / l != avancement) {
            printf("%d effectué\n",(avancement + 1) * 10);
            avancement++;
        }
        char caractere = TabOfChar_get(chuff, i);
        TabOfInt* codeBin = newTabBinFromInt_Static(caractere);
        for(int j = 0; j<8; j++){
            if(TabOfInt_get(codeBin, j) == 1 && index + index_ini < longueur){
                *a = *(a->droit); // copie a->droit dans a
                if(a->droit == NULL){
                    char* element = malloc(sizeof(char));
                    *element = a->lettre;
                    addLastLL(res, element);
                    index++;
                    *a = *huff;
                }
            } else if (index + index_ini < longueur){
                *a = *(a->gauche);
                if(a->droit == NULL){
                    char* element = malloc(sizeof(char));
                    *element = a->lettre;
                    addLastLL(res, element);
                    index++;
                    *a = *huff;
                }
            }
        }
        terminateTableau((Tableau*) codeBin);
        codeBin = NULL;
    }
    unsigned long tRes = res->longueur;
    TabOfChar* tabRes = newTabOfChar(tRes);
    LinkedList* position = res;
    for(unsigned long i = 0; i<tRes; i++){
        //TabOfChar_put(tabRes,*((char*) getLL(res, i)), i); // à améliorer
        TabOfChar_put(tabRes,*((char*) position->valeur) , i);
        position = position->suiv;
    }
    terminateLinkedListTotal(res);
    return tabRes;
}

Fichier* newFichier_code_inv(Arbre* huff,Fichier* compresse,  FILE* lecteur, unsigned long tailleDecoupage){
    char* nouvChemin = malloc(strlen(compresse->chemin) + 1 + 6);
    int resChaine = sprintf(nouvChemin, "%s.iHuff", compresse->chemin);
    //printf("%s\n",nouvChemin);
    printf("création de chaine : %d\n", resChaine);
    Fichier* original = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(original);
    Arbre* a = malloc(sizeof(Arbre));
    *a = *huff;
    unsigned long index_ini = 0;
    unsigned long tailleFichier = fsize(compresse);
    unsigned long nombreDivisions = tailleFichier / tailleDecoupage;
    TabOfChar* buffer = newTabOfChar(tailleDecoupage);
    TabOfChar* reste = newTabOfChar(tailleFichier % tailleDecoupage);
    for(unsigned long i = 0; i<nombreDivisions; i++){
        readFlux(lecteur, buffer);
        TabOfChar* code = newCodeInv_Aux(huff, a, buffer, index_ini);
        writeFlux(graveur, code);
        index_ini = index_ini + code->longueur;
        terminateTableau((Tableau*) code);
        code = NULL;
    }
    readFlux(lecteur, reste);
    TabOfChar* code = newCodeInv_Aux(huff, a, reste, index_ini);
    writeFlux(graveur, code);
    terminateTableau((Tableau*) code);
    code = NULL;
    fclose(graveur);
    terminateTableau((Tableau*) buffer);
    terminateTableau((Tableau*) reste);
    return original;
}

TabOfChar* newTabFreq(ArrayList* decompte){
    unsigned long l = decompte->nbrAssignees;
    LinkedList* tab = newLinkedList();
    char* element = malloc(sizeof(char));
    *element = (char) (l-128);
    addLastLL(tab, element);
    for (unsigned long i = 0; i<l; i++) {
        Arbre* arbre = (Arbre*) getAL(decompte, i);
        element = malloc(sizeof(char));
        *element = arbre->lettre;
        addLastLL(tab, element);
        TabOfChar* poids = newTabWithClef(arbre->poids);
        unsigned long lp = poids->longueur;
        for (unsigned long j = 0; j<lp; j++) {
            element = malloc(sizeof(char));
            *element = TabOfChar_get(poids, j);
            addLastLL(tab, element);
        }
        terminateTableau((Tableau*) poids);
        poids=NULL;
    }
    unsigned long ltab = tab->longueur;
    TabOfChar* res = newTabOfChar(ltab);
    LinkedList* position = tab;
    for (unsigned long i = 0; i<ltab; i++) {
        //TabOfChar_put(res, *((char*) getLL(tab, i)), i);
        TabOfChar_put(res, *((char*) position->valeur) , i);
        position = position->suiv;
    }
    terminateLinkedListTotal(tab);
    printf("taille du préfixe : %lu\n", res->longueur);
    return res;
}

unsigned long readClefFromFile(FILE* lecteur){ // has been
    unsigned long tot = 0;
    LinkedList* buffer = newLinkedList();
    char val = (char) fgetc(lecteur);
    while (val - (val / 2) * 2 != 0) {
        addLastCharLL(buffer, val);
        val = (char) fgetc(lecteur);
    }
    addLastCharLL(buffer, val);
    
    unsigned long l = buffer->longueur;
    int puiss = (int) puissance(128, l-1);
    for (unsigned long j = 0; j<l; j++) {
        char lettre = getCharLL(buffer, j);
        tot = tot + ((lettre + 128) / 2) * puiss;
        puiss = puiss / 128;
    }
    terminateLinkedListTotal(buffer);
    return tot;
}


Fichier* newFichier_Huff_transfo_aux(Compteur* sem, Fichier* original, unsigned long tailleDecoupage){
    printf("Début du codage de Huffman\n");
    
    // initialisation des variables
    
    unsigned long tailleFichier = fsize(original);
    unsigned long nombreDivisions = tailleFichier/tailleDecoupage;
    TabOfChar* buffer = newTabOfChar(tailleDecoupage);                  // libéré
    TabOfChar* reste = newTabOfChar(tailleFichier % tailleDecoupage);   // libéré
    LinkedList* flux = newLinkedList(); // ou LinkedList                // libéré
    
    /* 
     * la liste de boolean (des char en fait) flux pointe vers les éléments de
     * de codage_caractère de l'arbre huff.
     * La destruction de ce dernier entraine donc également celle de la liste flux
     * Il faut donc libérer huff après flux
     */ 
    
    char* nouvChemin = malloc(strlen(original->chemin) + 1 + 5);
    sprintf(nouvChemin, "%s.temp", original->chemin);
    Fichier* compresse = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(compresse);
    FILE* lecteur = ouvrirLecture(original);
    
    // décompte et construit l'arbre
    
    ArrayList* decompte = newListWithComptage(original, sem, tailleDecoupage); //libéré
    // Attention : decompte ne devra pas être détruite totalement
    TabOfChar* tabFreq = newTabFreq(decompte);                          //libéré
    Arbre* huff = newArbrefromList(decompte); // decompte est détruit   // libéré
    
    //terminateLinkedList(decompte); decompte=NULL;
    terminateArrayList(decompte); decompte=NULL;            
    // écriture du préfixe
    
    writeFlux(graveur, tabFreq);
    
    terminateTableau((Tableau*) tabFreq); tabFreq = NULL;
    
    
    
    for (unsigned long i = 0; i<nombreDivisions; i++) {
        readFlux(lecteur, buffer);
        LinkedList* chuff = newCode(sem, huff, buffer, flux);           //libéré
        
        unsigned long lc = chuff->longueur;
        TabOfChar* code = newTabOfChar(lc);                             //libéré
        LinkedList* position = chuff;
        for (unsigned long j = 0; j<lc; j++) {
            //TabOfChar_put(code, getCharLL(chuff, j), j);
            TabOfChar_put(code, *((char*) position->valeur), j);
            position = position->suiv;
        }
        writeFlux(graveur, code);
        terminateTableau((Tableau*) code); code = NULL;
        terminateLinkedListTotal(chuff); chuff = NULL;
    }
    
    terminateTableau((Tableau*) buffer); buffer = NULL;
    
    readFlux(lecteur, reste);
    fclose(lecteur);
    LinkedList* chuff = newCode(sem, huff, reste, flux);                //libéré
             
    terminateTableau((Tableau*) reste); reste = NULL;
    
    // vidage du flux
    
    while (flux->longueur>0) {
        char car = lireFlux(flux);
        addLastCharLL(chuff, car);
    }
    terminateLinkedListTotal(flux); flux=NULL;
    terminateArbre(huff); huff=NULL;
    
    // conversion arraylist->tableau
    
    unsigned long lc = chuff->longueur;
    TabOfChar* code = newTabOfChar(lc);                                 //libéré
    LinkedList* position = chuff;
    for (unsigned long i = 0; i<lc; i++) {
        //TabOfChar_put(code, getCharLL(chuff, i), i);
        TabOfChar_put(code, *((char*) position->valeur), i);
        position = position->suiv;
    }
    
    terminateLinkedListTotal(chuff); chuff = NULL;
    
    // Ecriture
    
    writeFlux(graveur, code);
    
    terminateTableau((Tableau*) code); code =NULL;
    
    fclose(graveur);
    printf("Fin du codage de Huffman\n\n");
    return compresse;
}

/**
 * lance la compression de Huffman.
 * Cette fonction supporte la compression multiple par l'algoruthme de Huffman.
 * @param sem barre de progression
 * @param original fichier √† compress√©
 * @param tailleDecoupage taille du buffer
 * @param nbrComp nombre de compression par l'algoruthme de Huffman
 * @return renvoie le fichier compress√©.
 */

Fichier* newFichier_Huff_transfo(Compteur* sem, Fichier* original, unsigned long tailleDecoupage, int nbrComp){
    Fichier* temp1 = NULL;
    Fichier* temp2 = original;
    char* nouvChemin = malloc(strlen(original->chemin) + 1 + 6);
    sprintf(nouvChemin, "%s.cHUFF", original->chemin);
    Fichier* compresse = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(compresse);
    
    fputc((char) nbrComp, graveur);
    
    temp1 = newFichier_Huff_transfo_aux(sem, temp2, tailleDecoupage);
    temp2=temp1;
    for (int i = 1 ; i<nbrComp; i++) {
        temp1 = newFichier_Huff_transfo_aux(sem, temp2, tailleDecoupage);
        removeFichier(temp2);
        temp2 = temp1;
    }
    setValue(sem, sem->maximum - fsize(temp1));
    appendFile(graveur, temp1);
    fclose(graveur);
    removeFichier(temp1);
    free(temp1);
    return compresse;
}

Fichier* newFichier_Huff_inv_aux(Compteur* sem, Fichier* compresse, unsigned long tailleDecoupage, int aPrefixe){
    printf("Début du décodage de Huffman\n");
    FILE* lecteur = ouvrirLecture(compresse);
    if (aPrefixe == 1) {
        fgetc(lecteur);
    }
    int tailleFreq = ((char) fgetc(lecteur)) + 128;
    // tailleFreq est le nombre de caractères présents dans l'arbre
    if(tailleFreq == 0){
        tailleFreq = 256;
    }
    
    printf("nombre de caractères : %d\n", tailleFreq);
    
    ArrayList* decompte = newArrayList(256);
    for (unsigned long i = 0; i<tailleFreq; i++) {
        char lettre = (char) fgetc(lecteur);
        unsigned long poids = readClefFromFile(lecteur);
        
        //printf("%lu\n",poids);
        
        addLastAL(decompte, newFeuille(lettre, poids));
    }
    Arbre* huff = newArbrefromList(decompte);
    terminateArrayList(decompte); decompte = NULL;
    Fichier* original = newFichier_code_inv(huff, compresse, lecteur, tailleDecoupage);
    fclose(lecteur);
    sem->maximum = huff->poids;
    terminateArbre(huff); huff = NULL;
    printf("Fin du décodage de Huffman\n\n");
    return original;
}


/**
 * lance la transformation inverse de l'agorithme de Huffman. 
 * Cette focntion prend en compte les compressions de Huffman multiples.
 * @param sem bar de progression
 * @param compresse fichier à décompresser
 * @param tailleDecoupage taille du buffer
 * @return fichier décompressé
 */

Fichier* newFichier_Huff_inv(Compteur* sem, Fichier* compresse, unsigned long tailleDecoupage){
    Fichier* original = NULL;
    FILE* lecteur = ouvrirLecture(compresse);
    int n = fgetc(lecteur);
    fclose(lecteur);
    original = newFichier_Huff_inv_aux(sem, compresse, tailleDecoupage, 1);
    compresse = original;
    for (int i = 1; i<n; i++) {
        original = newFichier_Huff_inv_aux(sem, compresse, tailleDecoupage, 0);
        removeFichier(compresse);
        free(compresse);
        compresse = original;
    }
    return original;
}