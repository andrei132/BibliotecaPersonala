/*GIRNET Andrei - 311CB*/

#ifndef _ARBORE_
#define _ARBORE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Define-uri utile

#define INFO(arb) ((TArbore)arb)->info
#define INFOADD(arb) ((TArbore)arb)->infoAdd
#define NRNODURI(arb) ((TArbore)arb)->nrNoduri

//Structura unui arbore
typedef struct nodArbore{
    
    struct nodArbore *vctUrm;
    void *info;
    int nrNoduri;
    void *infoAdd;

}Arbore, *TArbore;


//Typedef-uri utile ale functiilor

typedef int cmpFunc(void *,void *);
typedef int printFunc(TArbore , char *,FILE *);
typedef void freeFunc(void *);


//Functii arbori

TArbore initArbore();
int addNode(TArbore arb,void *info, cmpFunc cmp);
void *extractNodN(TArbore arb, int n);
int findNodeFromInfo(TArbore arb,void *info, cmpFunc cmp);
int goToNodeN(TArbore *arb,int n);
void setInfoAdd(TArbore arb,void *infoAdd);
int resetNod(TArbore arb);
int uniqPath(TArbore arb);
int deletePath(TArbore rootArb,TArbore arb,TArbore flag ,freeFunc freeInfo,freeFunc freeInfoAdd,int n);
void deleteTArbore(TArbore rootArb,freeFunc freeInfo,freeFunc freeInfoAdd);

#endif