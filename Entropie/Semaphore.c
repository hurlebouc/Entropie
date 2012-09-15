//
//  Semaphore.c
//  Entropie
//
//  Created by hurlebouc on 03/10/11.
//  Copyright 2011 Mines de Nancy. All rights reserved.
//

#include "Semaphore.h"

Compteur* newCompteur(unsigned long max){
    Compteur* res = malloc(sizeof(Compteur));
    res->value = 0;
    res->maximum = max;
    return res;
}

void setValue(Compteur* sem, unsigned long i){
    if(i<sem->maximum){
        sem->value = i;
        return;
    }
    sem->value = sem->maximum;
    return;
}