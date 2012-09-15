//
//  ArrayList.h
//  Entropie
//
//  Created by hurlebouc on 26/09/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//
/**
 * \file ArrayList.h
 * \author hurlebouc 
 * 
 * Cette classe implémente les listes.
 */


/* -------------------------------------------------------------------- *
 *                          LINKEDLIST                                  *
 * -------------------------------------------------------------------- */

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef TABLEAU
#define TABLEAU
#include "Tableau.h"
#endif

/**
 * \struct LinkedList
 * Une LinkedList est une liste chaînée dont les éléments sont des pointeurs.
 */
typedef struct LinkedList
{
    void* valeur; /*!< \brief pointeur vers un élément de la liste*/
    unsigned long longueur; /*!< \brief taille de la liste*/
    struct LinkedList* prec; /*!< \brief élément précédent*/
    struct LinkedList* suiv; /*!< \brief élément suivant*/
    struct LinkedList* dernier; /*!< \brief dernier élément de la liste. Ce champs
                                 * n'est valable que pour le premier élément de la liste.
                                 */
}LinkedList;

/**
 * Initialise une LinkedList. Tout objet créé par cette fonction doit être 
 * détruit par les fonctions terminateLinkedList() ou terminateLinkedListTotal().
 */
LinkedList* newLinkedList();

/**
 * Donne la taille de liste.
 * @param liste
 */
unsigned long sizeLL(LinkedList* liste);
//unsigned long sizeExtLL(LinkedList* liste);

/**
 * Ajoute un élément à la fin de la liste
 * @param liste
 * @param element
 */
void addLastLL(LinkedList* liste, void* element);

/**
 * Ajoute un élément au début de la liste
 * @param liste
 * @param element
 */
void addFirstLL(LinkedList* liste, void* element);

/**
 * Ajoute un élément à la position index dans la liste.
 * @param liste
 * @param element
 * @param index
 */
void addLL(LinkedList* liste, void* element, unsigned long index);

/**
 * Concatène deux listes. La liste source reste inchangée. Par contre, les éléments
 * de la source ne sont pas copiés.
 * @param recepteur
 * @param source
 */
void addAllLL(LinkedList* recepteur, LinkedList* source);

/**
 * Concatène deux listes (Expérimentale).
 * @param recepteur
 * @param source
 */
void addAllLL2(LinkedList* recepteur, LinkedList* source);

/**
 * Ajoute un caractère à la fin d'une liste. Cette fonction se charge de l'allocation
 * dynamique du caratère en mémoire.
 * @param liste
 * @param c
 */
void addLastCharLL(LinkedList* liste, char c);

/**
 * Renvoie le dernier élément de la liste.
 * @param liste
 */
void* getLastLL(LinkedList* liste);

/**
 * Renvoie le premier élément de la liste
 * @param liste
 */
void* getFirstLL(LinkedList* liste);

/**
 * Renvoie le l'élément de la liste à la place index.
 * @param liste
 * @param index
 */
void* getLL(LinkedList* liste, unsigned long index);

/**
 * Renvoie la valeur du char de l'élément de la liste à la place index. Cette 
 * fonction n'est bien sur à utiliser que sur des listes de char.
 * @param liste
 * @param index
 */
char getCharLL(LinkedList* liste, unsigned long index);

/**
 * Supprime le dernier élément de la liste mais ne le détruit pas.
 * @param liste
 * @return élément supprimé
 */
void* removeLastLL(LinkedList* liste);

/**
 * Supprime le premier élément de la liste mais ne le détruit pas.
 * @param liste
 * @return élément supprimé
 */
void* removeFirstLL(LinkedList* liste);

/**
 * Supprime le index-e éléménent de la liste mais ne le détruit pas.
 * @param liste
 * @param index
 * @return élément supprimé
 */
void* removeAtIndexLL(LinkedList* liste, unsigned long index);

/**
 * Supprime la première instance de l'élément dans la liste.
 * @param liste
 * @param element
 */
void removeElementLL(LinkedList* liste, void* element);

/**
 * Donne l'index de la première instance de l'élement dans la liste.
 * @param liste
 * @param element
 */
unsigned long indexOfLL(LinkedList* liste, void* element);

/**
 * Donne l'index de la première instance du caractère dans la liste.
 * @param liste
 * @param element
 */
long indexOfCharLL(LinkedList* liste, char element);

/**
 * Détruit la liste sans détruire ses éléments.
 * @param liste
 */
void terminateLinkedList(LinkedList* liste);

/**
 * Détruit la liste ainsi que ses éléments.
 * @param liste
 */
void terminateLinkedListTotal(LinkedList* liste);

/**
 * Affiche sur le log le contenu de la liste. Ne fonctionne que si la liste
 * contient des types simples (char, short, int, long)
 * @param liste
 * @param tailleElement taille ne octets des éléments présents dans la liste.
 */
void afficheLinkedList(LinkedList* liste, short tailleElement);

/**
 * Crée une nouvelle liste par copie d'une autre. Les éléments de la liste copiée
 * ne sont pas copiés dans la nouvelle liste.
 * @param liste
 */
LinkedList* newLinkedListFromCopieLinkedList(LinkedList* liste);

/**
 * Converti une LinkedList de charactère en tableau de caractères.
 * @param liste
 */
TabOfChar* LLversTOC(LinkedList* liste);

/* -------------------------------------------------------------------- *
 *                          ARRAYLIST                                   *
 * -------------------------------------------------------------------- */

/**
 * \struct ArrayList
 * Une ArrayList est une liste basée sur un tableau. Une ArrayList est de taille
 * maximale fixe.
 */
typedef struct ArrayList
{
    unsigned long tailleMax;/*!< \brief taille maximale de la liste*/
    void* tableau;/*!< \brief emplacement du premier élément de la liste*/
    unsigned long nbrAssignees;/*!< \brief taille courante de la liste*/
}ArrayList;


/**
 * Crée une ArrayList. Cette fonction gère l'allocation dynamique dans la mémoire
 * de la nouvelle liste.
 * Tout objet issu de cette fonction doit être détruit par les fonctions 
 * terminateArrayList() ou terminateArrayListTotal().
 * @param l
 * @return 
 */
ArrayList* newArrayList(unsigned long l);

/**
 * Donne la taille de la liste
 * @param liste
 */
unsigned long sizeAL(ArrayList* liste);

/**
 * Ajoute un élément à la fin de la liste
 * @param liste
 * @param element
 */
void addLastAL(ArrayList* liste, void* element);

/**
 * Ajoute un élément ne tête de liste
 * @param liste
 * @param element
 */
void addFirstAL(ArrayList* liste, void* element);

/**
 * Ajoute un élément à la place index.
 * @param liste
 * @param element
 * @param index
 */
void addAL(ArrayList* liste, void* element, unsigned long index);

/**
 * Ajoute les élément se la source au récépteur. Cette fonction ne copie pas les
 * éléments de la source et ne la modifie pas.
 * @param recepteur
 * @param source
 */
void addAllAL(ArrayList* recepteur, ArrayList* source);

/**
 * Ajoute un carctère en fin de liste
 * @param liste
 * @param c
 */
void addLastCharAL(ArrayList* liste, char c);

/**
 * Donne le dernier élément de la liste.
 * @param liste
 */
void* getLastAL(ArrayList* liste);

/**
 * Donne le premier élément de la liste.
 * @param liste
 */
void* getFirstAL(ArrayList* liste);

/**
 * Donne le index-eme élément de la liste.
 * @param liste
 * @param index
 */
void* getAL(ArrayList* liste, unsigned long index);

/**
 * Renvoie la valeur du char de l'élément de la liste à la place index. Cette 
 * fonction n'est bien sur à utiliser que sur des listes de char.
 * @param liste
 * @param index
 */
char getCharAL(ArrayList* liste, unsigned long index);

/**
 * Supprime le dernier élément de la liste sans le détruire.
 * @param liste
 * @return élément supprimé
 */
void* removeLastAL(ArrayList* liste);

/**
 * Supprime le premier élément de la liste sans le détruire.
 * @param liste
 * @return élément supprimé
 */
void* removeFirstAL(ArrayList* liste);

/**
 * Supprime le index-eme élément de la liste sans le détruire.
 * @param liste
 * @param index
 * @return élément supprimé
 */
void* removeAtIndexAL(ArrayList* liste, unsigned long index);

/**
 * Supprime la première occurance de l'élément sans le détruire.
 * @param liste
 * @param element
 */
void removeElementAL(ArrayList* liste, void* element);

/**
 * Donne l'index de la première instance de l'élément dns la liste.
 * @param liste
 * @param element
 */
long indexOfAL(ArrayList* liste, void* element);

/**
 * Donne l'index de la première instance du caractère dans la liste.
 * @param liste
 * @param element
 */
long indexOfCharAL(ArrayList* liste, char element);

/**
 * Détruit la liste mais pas ses éléments.
 * @param liste
 */
void terminateArrayList(ArrayList* liste);

/**
 * Détruit la liste avec ses éléments.
 * @param liste
 */
void terminateArrayListTotal(ArrayList* liste);

/**
 * Affiche sur le log les éléments de la liste. Ne marche que pour une liste de 
 * caractères.
 * @param liste
 */
void afficheArrayList(ArrayList* liste);

/**
 * Crée une nouvelle ArrayList à partir d'une LinkedList.
 * Tout objet issu de cette fonction doit être détruit.
 * @param ll
 */
ArrayList* newArrayListFromLinkedList(LinkedList* ll);

/**Crée une nouvelle LinkedList à partir d'une ArrayList.
 * Tout objet issu de cette fonction doit être détruit.
 * @param al
 */
LinkedList* newLinkedListFromArrayList(ArrayList* al);