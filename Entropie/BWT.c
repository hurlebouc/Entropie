#include "BWT.h"

//---------------------------LEAKS FREE----------------------


/* à refaire sans ArrayList */

unsigned long readClefFromArray(TabOfChar* L){
    unsigned long i = 0;
    unsigned long tot = 0;
    LinkedList* buffer = newLinkedList();
    while(TabOfChar_get(L, i) % 2 != 0){
        char* b = Tableau_get((Tableau*)L, i);
        addLastLL(buffer, b);
        i++;
    }
    char* b = Tableau_get((Tableau*)L, i);
    addLastLL(buffer, b);
    unsigned long l = buffer->longueur;
    unsigned long puiss = puissance(128, l-1);
    for(unsigned long j = 0; j<l; j++){
        char* c = getLL(buffer, j);
        tot = tot + ((*c + 128) / 2) * puiss;
        puiss = puiss / 128;
    }
    terminateLinkedList(buffer); // pour ne pas effacer les éléments des tableaux.
    return tot;
}

unsigned long readClefFromArray2(TabOfChar* L){
    unsigned long i = 0;
    unsigned long tot = 0;
    while(TabOfChar_get(L, i) % 2 != 0){
        char* c = Tableau_get((Tableau*)L, i);
        tot = tot*128 + (*c + 128) / 2;
        i++;
    }
    char* c = Tableau_get((Tableau*)L, i);
    tot = tot*128 + (*c + 128) / 2;
    return tot;
}

/**
 * Cette fonction donne la taille d'un segments qui a été codé par BWT lors
 * du découpage du fichier original.
 */

/* refaire sans list */

long readTailleSegment(FILE* lecteur){ // hasbeen
    long tot = 0;
    LinkedList* buffer = newLinkedList();
    int val = fgetc(lecteur);
    //long pos = ftell(lecteur);
    if (val!=-1){
        char car = (char) val;
        while(car % 2 != 0){
            char* p = malloc(sizeof(char));
            *p = car;
            addLastLL(buffer, p);
            val = fgetc(lecteur);
            car = (char) val;
        }
        char* p = malloc(sizeof(char));
        *p = car;
        addLastLL(buffer, p);
        unsigned long l = buffer->longueur;
        unsigned long puiss = puissance(128, l-1);
        for(unsigned long j = 0; j<l; j++){
            char* c = getLL(buffer, j);
            tot = tot + ((*c + 128) / 2) * puiss;
            puiss = puiss / 128;
        }
        terminateLinkedListTotal(buffer);
        //printf("%d \n",tot);
        return tot;
    }
    terminateLinkedListTotal(buffer);
    return -1;
}

long readTailleSegment2(FILE* lecteur){
    long tot = 0;
    int val = fgetc(lecteur);
    //long pos = ftell(lecteur);
    if (val!=-1){
        char car = (char) val;
        while(car % 2 != 0){
            tot = tot*128 + (car+128)/2;
            val = fgetc(lecteur);
            car = (char) val;
        }
        tot = tot*128 + (car+128)/2;
        return tot;
    }
    return -1;
}


void incrementer_Avancement(Compteur*sem){
    unsigned long max = sem->maximum;
    unsigned long val = sem->value;
    if ((val * 10) % max == 0) {
        printf("%lu effectuée\n", ((val * 10) / max) * 10);
    }
    setValue(sem, val+1);
}

TabOfChar* newTab_BWT_transfo_aux(Compteur* sem, TabOfChar* c){
    unsigned long l = c->longueur;
    TabCirc* ref = newTabCirc(c); // libéré
    unsigned long positionRef = 0;
    //LinkedList* i2d = newLinkedList(); // libéré
    ArrayList* i2d = newArrayList(c->longueur);
    unsigned long zero = 0;
    unsigned long* p = malloc(sizeof(long));
    *p = zero;
    //addLastLL(i2d, p);
    addLastAL(i2d, p);
    for(unsigned long i = 1; i<l; i++){
        incrementer_Avancement(sem);
        positionRef =  insertionTabCirc(ref, i, i2d, positionRef);
    }
    TabOfChar* tab = newTabOfCharWithDerniereColonne(ref, i2d); //libéré
    TabOfChar* clef = newTabWithClef(positionRef); // libéré
    //afficheTableau((Tableau*) clef);
    unsigned long lClef = clef->longueur;
    unsigned long lTab = tab->longueur;
    TabOfChar* res = newTabOfChar(lClef + lTab);
    memcpy(res->tableau, clef->tableau, (clef->longueur)*(clef->tailleElement));
    
    for(unsigned long i = lClef; i<lClef + lTab; i++){
        TabOfChar_put(res, TabOfChar_get(tab, i - lClef), i);
    }
    //afficheTableau((Tableau*) res);
    terminateTableau((Tableau*) clef);
    terminateTableau((Tableau*) tab);
    //terminateLinkedListTotal(i2d);
    terminateArrayListTotal(i2d);
    terminateTabCirc(ref);
    return res;
}

TabOfChar* newTab_BWT_transfo_aux_qsort(Compteur* sem, TabOfChar* c){
    unsigned long l = c->longueur;
    TabCirc* tabC = newTabCirc(c); // libéré
    unsigned long* i2d = malloc(sizeof(long)*l); // libéré
    for (unsigned long i = 0; i<l; i++) {
        i2d[i]=i;
    }
    unsigned long positionRef = triRapide_r(tabC, i2d, l);
    TabOfChar* clef = newTabWithClef(positionRef); // libéré
    //afficheTableau((Tableau*) clef);
    unsigned long lClef = clef->longueur;
    TabOfChar* res = newTabOfChar(lClef + l);
    memcpy(res->tableau, clef->tableau, (clef->longueur)*(clef->tailleElement));
    
    for(unsigned long i = lClef; i<lClef + l; i++){
        TabOfChar_put(res, TabCirc_get(tabC,i2d[i-lClef] , l-1), i);
    }
    //afficheTableau((Tableau*) res);
    terminateTableau((Tableau*) clef);
    free(i2d);
    terminateTabCirc(tabC);
    return res;
}

TabOfChar* newTab_BWT_transfo_aux_triRapide(Compteur* sem, TabOfChar* c){
    unsigned long l = c->longueur;
    TabCirc* tabC = newTabCirc(c); // libéré
    unsigned long* i2d = malloc(sizeof(long)*l); // libéré
    for (unsigned long i = 0; i<l; i++) {
        i2d[i]=i;
    }
    unsigned long positionRef = 0;
    triRapide(tabC, i2d, 0, l, &positionRef);
    TabOfChar* clef = newTabWithClef(positionRef); // libéré
                                                   //afficheTableau((Tableau*) clef);
    unsigned long lClef = clef->longueur;
    TabOfChar* res = newTabOfChar(lClef + l);
    memcpy(res->tableau, clef->tableau, (clef->longueur)*(clef->tailleElement));
    
    for(unsigned long i = lClef; i<lClef + l; i++){
        TabOfChar_put(res, TabCirc_get(tabC,i2d[i-lClef] , l-1), i);
    }
    //afficheTableau((Tableau*) res);
    terminateTableau((Tableau*) clef);
    free(i2d);
    terminateTabCirc(tabC);
    return res;
}

Fichier* newFichier_BWT_transfo(Compteur* sem, Fichier* original, unsigned long tailleDecoupage){
    printf("Début du codage BWT\n");
    FILE* lecteur = ouvrirLecture(original);
    char* nouvChemin = malloc(strlen(original->chemin) + 1 + 5);
    sprintf(nouvChemin, "%s.cBWT", original->chemin);
    Fichier* compresse = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(compresse);
    unsigned long tailleFichier = fsize(original);
    unsigned long nombreDivisions = tailleFichier / tailleDecoupage;
    TabOfChar* buffer = newTabOfChar(tailleDecoupage); //libéré
    TabOfChar* reste = newTabOfChar(tailleFichier % tailleDecoupage); //libéré
    unsigned long taillePostBWT = 0;
    for(unsigned long i = 0; i<nombreDivisions; i++){
        readFlux(lecteur, buffer);
        printf("     Secteur %lu sur %lu\n", i+1, nombreDivisions+1);
        TabOfChar* code = newTab_BWT_transfo_aux_qsort(sem, buffer); // libéré
        taillePostBWT = code->longueur;
        TabOfChar* prefixe = newTabWithClef(taillePostBWT); // libéré
        writeFlux(graveur, prefixe);
        writeFlux(graveur, code);
        terminateTableau((Tableau*) prefixe);
        terminateTableau((Tableau*) code);
    }
    readFlux(lecteur, reste);
    printf("     Secteur %lu sur %lu\n", nombreDivisions+1, nombreDivisions+1);
    TabOfChar* code = newTab_BWT_transfo_aux_qsort(sem, reste);
    taillePostBWT = code->longueur;
    TabOfChar* prefixe = newTabWithClef(taillePostBWT);
    writeFlux(graveur, prefixe);
    writeFlux(graveur, code);
    fclose(graveur);
    fclose(lecteur);
    terminateTableau((Tableau*) prefixe);
    terminateTableau((Tableau*) code);
    terminateTableau((Tableau*) buffer);
    terminateTableau((Tableau*) reste);
    printf("Fin du codage BWT\n\n");
    return compresse;
}

// -------------------------- THREADS ----------------------------

CondNbrTheads* newCondNbrThreads(unsigned long nbrMaxThreads){
    pthread_mutex_t* triggering = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(triggering, NULL);
    pthread_mutex_lock(triggering);
    pthread_cond_t* condition = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(condition, NULL);
    CondNbrTheads* res = malloc(sizeof(CondNbrTheads));
    res->triggering = triggering;
    res->condition = condition;
    res->maxNbrThreads = nbrMaxThreads;
    res->currentNbrThreads = 0;
    return res;
}

void terminateCondNbrThreads(CondNbrTheads* cond){
    pthread_mutex_destroy(cond->triggering);
    pthread_cond_destroy(cond->condition);
    free(cond);
}

ParamLanceur* newParamLanceur(Compteur* sem, CondNbrTheads* runningThreads, Fichier* fichier, LinkedList* listeTache, unsigned long tailleDecoupage, pthread_mutex_t* accesList){
    ParamLanceur* res = malloc(sizeof(ParamLanceur));
    res->runningThreads = runningThreads;
    res->fichier = fichier;
    res->listeTache = listeTache;
    res->tailleDecoupage = tailleDecoupage;
    res->sem = sem;
    res->accesListe = accesList;
    return res;
}

void terminateParamLanceur(ParamLanceur* param){
    free(param);
}

CommandeBWT* newCommandeBWT(Compteur* sem, TabOfChar* buffer, CondNbrTheads* runningThreads){
    CommandeBWT* res = malloc(sizeof(CommandeBWT));
    res->sem = sem;
    res->buffer = buffer;
    res->res = NULL;
    
    //pthread_t nouvTache;
    pthread_t* p_nouvTache = malloc(sizeof(pthread_t));
    //*p_nouvTache = nouvTache;
    res->pid = p_nouvTache;
    
    pthread_attr_t* p_attr = malloc(sizeof(pthread_attr_t));
    pthread_attr_init(p_attr);
    pthread_attr_setdetachstate(p_attr, PTHREAD_CREATE_JOINABLE);
    res->attribut = p_attr;
    res->runningThreads = runningThreads;
    
    return res;
}

void terminateCommande(CommandeBWT* ordre){
    
}

void* tacheBWT_transfo(void* vordre){
    CommandeBWT* ordre = (CommandeBWT*) vordre;
    printf("Début de la tâche %lu\n", ordre->refCommande);
    TabOfChar* buffer = ordre->buffer;
    Compteur* sem = ordre->sem;
    CondNbrTheads* conditionLancement = ordre->runningThreads;
    ordre->res = newTab_BWT_transfo_aux_qsort(sem, buffer);
    //terminateTableau((Tableau*) buffer); // à faire dans collecteur
    conditionLancement->currentNbrThreads--;
    pthread_cond_signal(conditionLancement->condition);
    printf("Fin de la tâche %lu\n", ordre->refCommande);
    return NULL;
}


/**
 * il faut que triggering soit verrouillé
 * paramLancement->listeTache devra déjà être initialisée par newLinkedList()
 */

void* lanceur(void* param_void){
    
    ParamLanceur* param = param_void;
    
    LinkedList* listeTache = param->listeTache;
    Fichier* fichier = param->fichier;
    unsigned long tailleFichier = fsize(fichier);
    unsigned long tailleDecoupage = param->tailleDecoupage;
    FILE* lecteur = ouvrirLecture(fichier);
    CondNbrTheads* condNbrThreads = param->runningThreads;
    
    unsigned long nbrDivisions = tailleFichier/tailleDecoupage;
        
    for (unsigned long i = 0; i<nbrDivisions; i++) {
        
        TabOfChar* buffer = newTabOfChar(tailleDecoupage); // faudra le détruire lors de l'exécution de terminateCommande
        readFlux(lecteur, buffer);
        CommandeBWT* ordre = newCommandeBWT(param->sem, buffer, condNbrThreads);
        ordre->refCommande = i;
        pthread_mutex_lock(param->accesListe);
        addLastLL(listeTache, ordre);
        pthread_mutex_unlock(param->accesListe);
        
        pthread_create(ordre->pid, ordre->attribut, tacheBWT_transfo, ordre);
        //printf("current runnig threads: %lu\n", condNbrThreads->currentNbrThreads + 1);
        
        condNbrThreads->currentNbrThreads++;
        if (condNbrThreads->currentNbrThreads >= condNbrThreads->maxNbrThreads) {
            pthread_cond_wait(condNbrThreads->condition, condNbrThreads->triggering);
        }
    }
    unsigned long tailleReste = tailleFichier % tailleDecoupage;
    if (tailleReste != 0) {
        TabOfChar* buffer = newTabOfChar(tailleReste); // faudra le détruire lors de l'exécution de terminateCommande
        readFlux(lecteur, buffer);
        CommandeBWT* ordre = newCommandeBWT(param->sem, buffer, condNbrThreads);
        ordre->refCommande = nbrDivisions;
        pthread_mutex_lock(param->accesListe);
        addLastLL(listeTache, ordre);
        pthread_mutex_unlock(param->accesListe);
        
        pthread_create(ordre->pid, ordre->attribut, tacheBWT_transfo, ordre);
    }
    fclose(lecteur);
    return NULL;
}

/**
 * On a synchronisé l'acces à la liste ce qui permet d'exécuter cette 
 * fonction en même temps que le lanceur.
 */

Fichier* newFichier_collecteur(ParamLanceur* param){
    Fichier* original = param->fichier;
    char* nouvChemin = malloc(strlen(original->chemin) + 1 + 5);
    sprintf(nouvChemin, "%s.cBWT", original->chemin);
    Fichier* compresse = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(compresse);
    LinkedList* liste = param->listeTache;
    pthread_mutex_t* accesListe = param->accesListe;
    unsigned long tailleFichier = fsize(param->fichier);
    unsigned long nbrTache = tailleFichier / param->tailleDecoupage;
    if (tailleFichier % param->tailleDecoupage != 0) {
        nbrTache++;
    }
    LinkedList* position = newLinkedList();
    LinkedList* tete = position;
    position->suiv = liste; // Très artificielle comme méthode...
    unsigned long l;
    
    unsigned long taillePostBWT = 0;
    for (unsigned long i = 0; i<nbrTache; i++) {
        pthread_mutex_lock(accesListe);
        l = liste->longueur;
        pthread_mutex_unlock(accesListe);
        while (l <= i) {
            sleep(1);
            pthread_mutex_lock(accesListe);
            l = liste->longueur;
            pthread_mutex_unlock(accesListe);
        }
        position = position->suiv;
        
        CommandeBWT* ordre = position->valeur;
        pthread_t pid = *(ordre->pid);
        
        pthread_join(pid, NULL); // ATTENTION au NULL !!!!
        printf("récolte de la tâche %lu\n",i);
        
        TabOfChar* code = ordre->res; // libéré
        taillePostBWT = code->longueur;
        TabOfChar* prefixe = newTabWithClef(taillePostBWT); // libéré
        writeFlux(graveur, prefixe);
        writeFlux(graveur, code);
        terminateTableau((Tableau*) prefixe);
        terminateTableau((Tableau*) code);
        terminateTableau((Tableau*) ordre->buffer);
        pthread_attr_destroy(ordre->attribut);
        free(ordre->pid);
        free(ordre);
    }
    fclose(graveur);
    free(tete);
    return compresse;
}

Fichier* newFichier_BWT_transfo_thread(Compteur* sem, Fichier* original, unsigned long tailleDecoupage, unsigned long nbrMaxThreads){
    pthread_mutex_t* accesListe = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(accesListe, NULL);
    LinkedList* listeTache = newLinkedList();
    CondNbrTheads* runningThreads = newCondNbrThreads(nbrMaxThreads);
    ParamLanceur* param = newParamLanceur(sem, runningThreads, original, listeTache, tailleDecoupage, accesListe);
    pthread_t lanceur_Tache;
    pthread_create(&lanceur_Tache, NULL, lanceur, param);
    Fichier* compresse = newFichier_collecteur(param);
    
    pthread_mutex_unlock(runningThreads->triggering);
    terminateLinkedList(listeTache);
    terminateParamLanceur(param);
    terminateCondNbrThreads(runningThreads);
    pthread_mutex_destroy(accesListe);
    return compresse;
}

/*-------------------------------------------------------------------------*
 *                                  INVERSE                                *
 *-------------------------------------------------------------------------*/

TabOfChar* newTab_BWT_inv_aux(Compteur* sem, TabOfChar* L){
    unsigned long I = readClefFromArray2(L);
    unsigned long longClef = 1;
    if(I!=0) {
        //longClef = (unsigned long) (-floor((floor(log2(I)) + 1) / (-7.)));
        longClef = quotienEntierSup(lnX(I, 2) + 1, 7);
        
        //----------------- à supprimer après débugage-----------
        unsigned long temoin = (unsigned long) (-floor((floor(log2(I)) + 1) / (-7.)));
        if (temoin != longClef) {
            //printf("%d\n", 10/(7));
            printf("la nouvelle fonction ln ne marche pas\n ancien : %lu\n nouveau : %lu\n",temoin, longClef);
            exit(EXIT_FAILURE);
        }
        //--------------------------------------------------------
        
    }
    unsigned long N = L->longueur - longClef;
    unsigned long* C = calloc(256, sizeof(long));
    unsigned long* P = calloc(N, sizeof(long));
    TabOfChar* S = newTabOfChar(N);
    for(unsigned long i=0; i<N; i++){
        P[i] = C[TabOfChar_get(L, i+longClef) + 128]; //P[i] est le nombre de caractères L[I] d'indice strictement inférieur dans L.
        C[TabOfChar_get(L, i+longClef) + 128]++; // C est le nombre d'occurences de chaque caractère.
        incrementer_Avancement(sem);
    }
    unsigned long sum = 0; // nombre total de caractères
    for(int ch = 0; ch<256; ch++){
        sum = sum + C[ch]; // C indique le nombre de caractères présents dans L placés avant ch dans l'ordre alphabetique
        C[ch] = sum - C[ch];
    }
    unsigned long i = I;
    for(unsigned long j = N-1; j> 0; j--){
        TabOfChar_put(S, TabOfChar_get(L, i+longClef), j);
        i = P[i] + C[TabOfChar_get(L, i+longClef) + 128];
        incrementer_Avancement(sem);
    }
    TabOfChar_put(S, TabOfChar_get(L, i+longClef), 0);
    i = P[i] + C[TabOfChar_get(L, i+longClef) + 128];
    incrementer_Avancement(sem);
    free(C);
    free(P);
    return S;
}

Fichier* newFichier_BWT_inv(Compteur* sem, Fichier* compresse){
    printf("Début du décodage BWT\n");
    FILE* lecteur =  ouvrirLecture(compresse);
    char* nouvChemin = malloc(strlen(compresse->chemin) + 1 + 5);
    sprintf(nouvChemin, "%s.iBWT", compresse->chemin);
    Fichier* original = newFichier(nouvChemin);
    FILE* graveur = ouvrirEcriture(original);
    long taillePostBWT = readTailleSegment2(lecteur);
    while(taillePostBWT != -1){
        TabOfChar* buffer = newTabOfChar(taillePostBWT);
        readFlux(lecteur, buffer);
        TabOfChar* decode = newTab_BWT_inv_aux(sem, buffer);
        writeFlux(graveur, decode);
        taillePostBWT = readTailleSegment2(lecteur);
        terminateTableau((Tableau*) buffer);
        terminateTableau((Tableau*) decode);
    }
    fclose(graveur);
    fclose(lecteur);
    printf("Fin du décodage BWT\n\n");
    return original;
}
