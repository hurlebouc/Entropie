/**
 * \file  utilitaires.h
 * \author hurlebouc 
 * 
 * Cette bibliothèque contient quelques fonctions utilisées plusieurs fois à des
 * à des endroits différents dans le projet
 */

#ifndef TABLEAU
#define TABLEAU
#include "Tableau.h"
#endif

/**
 * Donne le maximum de deux entiers
 * @param a
 * @param b
 */
long max(long a, long b);

/**
 * Élève n à la puissance p.
 * @param n
 * @param p
 */
long puissance(long n, long p);

/**
 * Crée une version binaire de la clef
 * @param clef
 */
TabOfChar* newTabWithClef(unsigned long clef);

/**
 * Calcule la valeur do logarithme de n dans une certaine base.
 * @param n
 * @param base
 */
unsigned long lnX(unsigned long n, unsigned long base);

/**
 * Donne la valeur de la partie entière supérieur du quotient de a par b
 * @param a
 * @param b
 */
unsigned long quotienEntierSup(unsigned long a, unsigned long b);