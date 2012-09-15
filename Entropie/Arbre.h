//
//  Arbre.h
//  Entropie
//
//  Created by hurlebouc on 30/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

/**
 * \file Arbre.h
 * \author hurlebouc 
 * 
 * Implémente la gestion des arbres.
 */

#define ARBRE

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef ARRAYLIST
#define ARRAYLIST
#include "ArrayList.h"
#endif

#ifndef TABLEAU
#define TABLEAU
#include "Tableau.h"
#endif

#ifndef UTILITAIRES
#define UTILITAIRES
#include "utilitaires.h"
#endif

/**
 * \struct arbre
 * 
 * Cette structure reccursive permet d'effectuer le codage de Huffman.
 */
typedef struct arbre{
    struct arbre* droit;
    struct arbre* gauche;
    unsigned long poids;
    char lettre;

    float codage_moyen; /*!< \brief Donne la moyenne des tailles de codage de chaque
                         * caractères pondérées par les fréquences des caractères */
    TabOfPoint* codage_caracteres; /*!< \brief Tableau dont chaque élément est une liste
                                    contenant le codage binaire de chaque caractères */
    TabOfChar* liste_caracteres; /*!< \brief Tableau contenant l'ensemble des caractères
                                  contenus dans l'arbre et ses fils*/
    short profondeur; /*!<\brief taille maximal des branches de l'arbre*/
}Arbre;


/**
 * Construit une feuille d'un arbre. Cette fonction se charge de faire une 
 * allocation dynamique.
 * Tout objet créé par cette fonction doit être détruit par la fonction
 * terminateArbre().
 * 
 * @param caractere caractère représenté par la feuille.
 * @param poids nombre d'occurance du caractère dans le message.
 * @return une nouvelle feuille.
 */

Arbre* newFeuille(char caractere, unsigned long poids);

/**
 * Construit un arbre à partir de ses deux fils. Cette fonction se charge de 
 * faire l'allocation dynamique.
 * Tout objet créé par cette fonction doit être détruit par la fonction
 * terminateArbre().
 * 
 * @param fDroit fils droit
 * @param fGauche fils gauche
 * @return le nouvel arbre
 */

Arbre* newArbre(Arbre* fDroit, Arbre* fGauche);

/**
 * Contruit un nouvel arbre en copiant les champs de l'arbre donné en paramètre
 * de manière récursive.
 * Tout objet créé par cette fonction doit être détruit par la fonction
 * terminateArbre().
 * La destruction d'un objet créé par ce constructeur ne détruit pas l'arbre copié
 * 
 * @param a arbre à copier
 * @return copie du paramètre
 */

Arbre* newCopieArbre(Arbre* a);

/**
 * Renvoie le codage binaire d'un caractère codé par l'arbre de Huffamn.
 * @param arbre arbre de Huffman
 * @param b caractère codé par l'arbre
 * @return codage binaire
 */

LinkedList* getCode(Arbre* arbre, char b);

/**
 * Copie de manière récursive tous les champs du modèle dans le recepteur
 * @param recepteur
 * @param modele
 */

void merge(Arbre* recepteur, Arbre* modele);

/**
 * Renvoie une chaine de caractère décrivant un arbre.
 * @param arbre
 */

char* afficheArbre(Arbre* arbre);

/**
 * Détruit un arbre et tous les champs qui le compose.
 * @param arbre
 */

void terminateArbre(Arbre* arbre);