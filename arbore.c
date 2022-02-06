/*GIRNET Andrei - 311CB*/

#include "arbore.h"

//Functia de initializare a unui arbore
TArbore initArbore(){

    TArbore arb = calloc(1, sizeof(Arbore));

    return arb;

}

//Reseteaza legaturile nodului fara ai modifica informatia
int resetNod(TArbore arb){
    
    if(!arb) return 1;

    NRNODURI(arb) = 0;
    INFOADD(arb) = NULL;
    arb->vctUrm = NULL;

    return 0;

}

//Extrage Nodul n din arbore fara al modifica, intoarce adresa sa
void *extractNodN(TArbore arb, int n){

    if(!arb) return NULL;
    if(n >= arb->nrNoduri) return NULL;
    
    return INFO(arb->vctUrm + n);

}

//Gaseste dupa informatie cu ajutorul functiei cmp, intoarcea nr de ordine
int findNodeFromInfo(TArbore arb,void *info, cmpFunc cmp){

    if(!arb) return -1;

    for(int i = 0; i < NRNODURI(arb); i++){

        if(cmp(INFO(arb->vctUrm+i), info)){
            
            return i;

        }
    
    }

    return -1;

}

//Mergi in nodul n
int goToNodeN(TArbore *arb,int n){
    
    if(!(*arb)) return -1;
    if(n >= NRNODURI(*arb)) return -1;

    *arb = ((*arb)->vctUrm + n);

    return 0;

}

//Seteaza cimpul infoAdd cu informatie
void setInfoAdd(TArbore arb,void *infoAdd){
    
    INFOADD(arb) = infoAdd;

}

//Verifica daca in arbore nu exista alta informatie
int uniqPath(TArbore arb){

    if(!arb) return 1;
    if(!NRNODURI(arb)) return 1;
    
    for(int i = 0; i < NRNODURI(arb); i++) {
        
        if(NRNODURI(arb) > 1 || INFOADD(arb)) {
            
            return 0;
        
        } else {
            
            return uniqPath(arb->vctUrm + i);
            
        }

    }

    return 1;

}

/* 
 * Functie de adaugare a unui nod dupa o regula de inserare, 
 * intoarce pozitia la care a fost inserata, pozitiva daca e inserat proaspat
 * negativ daca deja exista aceasta chee in arbore, 0 eroare
 */
int addNode(TArbore arb, void *info, cmpFunc cmp){

    TArbore aux;
    int i,flag;

    //Inserare atunci cind nu exista inca noduri
    if(!arb->vctUrm){
        
        arb->vctUrm = initArbore();
        if(!arb->vctUrm) return 0;

        INFO(arb->vctUrm) = info;
        NRNODURI(arb) = 1;

        return 1;

    }
    
    for (i = 0; i < NRNODURI(arb); i++){

        //Comparatie dintre info si cheea din arbore 
        flag = cmp(info,INFO(arb->vctUrm+i));

        //Daca deja exista acesta chee
        if( flag == 0) return -1 * (i+1);

        //A fost gasita pozitia la care trebuie sa fie inserata celula
        if(flag < 0){
        
            //realocarea array-ului
            aux = realloc(arb->vctUrm, (NRNODURI(arb) + 1)*sizeof(Arbore));
            if (!aux) return 0;
            arb->vctUrm = aux;

            //muta celulele de la pozitia i cu o pozitie la dreapta
            memmove((arb->vctUrm + i+1), (arb->vctUrm + i), (NRNODURI(arb) - i)*sizeof(Arbore));

            INFO(arb->vctUrm+i) = info;       
            NRNODURI(arb)++;

            return i+1;

        }

    }

    /*
     * Daca trebuie sa fie inserat la sfirsit
     * realocarea array-ului
     */
    aux = realloc(arb->vctUrm, (NRNODURI(arb) + 1)*sizeof(Arbore));
    if (!aux) return 0;
    arb->vctUrm = aux;

    (arb->vctUrm + i)->info = info;
    NRNODURI(arb)++;

    return NRNODURI(arb);

}

/*
 * Sterge intreg path-ul dat de flag pina la capat, arb - celula cu infoAdd
 * rootArb - Arborele din care fac parte flag si arb, n - numarul nodului din 
 * flag pentru arb 
*/
int deletePath(TArbore rootArb,TArbore arb,TArbore flag, freeFunc freeInfo,freeFunc freeInfoAdd ,int n){
    
    if(NRNODURI(arb) > 0){
        
        if(INFOADD(arb)) freeInfoAdd(&INFOADD(arb));
        INFOADD(arb)=NULL;
        return 0;

    }

    if(flag){
        
        deleteTArbore(flag->vctUrm+n,freeInfo,freeInfoAdd);

        if(NRNODURI(flag)> n) {
        
            memmove(flag->vctUrm+n,flag->vctUrm+n+1,
                    (NRNODURI(flag) - n -1)*sizeof(Arbore));
        
        }
        
        if(NRNODURI(flag) != 1){
            
            arb = realloc(flag->vctUrm,(NRNODURI(flag)-1)*sizeof(Arbore));           
            if(!arb) return -1; 
            flag->vctUrm = arb;
        
        } else{

            free(flag->vctUrm);
            flag->vctUrm = NULL;

        }
        
        NRNODURI(flag)--;
        
    } else{
        
        
        deleteTArbore(rootArb,freeInfo,freeInfoAdd);
        free(rootArb);

    }
    


    return 0;

}

//Elibereaza toata memoria alocata de un TArbore
void deleteTArbore(TArbore rootArb,freeFunc freeInfo,freeFunc freeInfoAdd){

    if(!rootArb) return;
    if (INFO(rootArb)) freeInfo(INFO(rootArb));
    if(INFOADD(rootArb)) freeInfoAdd(&INFOADD(rootArb));
    if(!rootArb->nrNoduri) return;

    for(int i = 0; i < rootArb->nrNoduri; i++){

        deleteTArbore(rootArb->vctUrm+i,freeInfo,freeInfoAdd);
        
    }

    if(rootArb->vctUrm) {
    
        free(rootArb->vctUrm);
        rootArb->vctUrm = NULL;
        rootArb->nrNoduri = 0;
    
    }
    
}