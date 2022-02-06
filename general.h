/*GIRNET Andrei - 311CB*/

#include "arbore.h"

#ifndef _GENERAL_
#define _GENERAL_

#define CHARORD "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "
#define MAX_AUTOR 40
#define MAX_TITLU 50

//Typedef-uri utile

typedef void* alocInfo(void*);


//Structura informatiei
typedef struct {

    char *titlu, *autor;
    int rating, nrPagini;
    
} Carte;


//Functii de prelucrare a unui fisier

void prelucreFisier(FILE *fin,FILE *fout,cmpFunc cmp,cmpFunc cmpIdentic,alocInfo aloc,printFunc,freeFunc,freeFunc);

#endif