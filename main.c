/*GIRNET Andrei - 311CB*/

#include "general.h"

//Functia de comparare a 2 char dupa regula ceruta in cerinta
int myCharCmp(void *a,void *b){

    //Gaseste pozitia in stringul ordinii si face diferenta dintre pozitii
    return (int)(strchr(CHARORD,*(char *)a)-strchr(CHARORD,*(char *)b));
    
}

//Compara daca 2 char sunt identice
int cmpChr(void *a, void *b){

    return *(char*)a == *(char*)b;

}

//Aloca o structura carte si o initializeaza
void* alocCarte(void *info){

    if(!info) return NULL;
    char *buff = (char*)info;
    int nrPagini, raiting;
    char *titlu = strtok(buff,":");
    char *autor = strtok(NULL,":");
    char *forNr = strtok(NULL,":");

    sscanf(forNr,"%d",&raiting);
    forNr = strtok(NULL,":");
    sscanf(forNr,"%d",&nrPagini);

    Carte* carte;
    carte = calloc(1,sizeof(Carte));
    
    if(!carte) return NULL;

    carte->titlu = calloc(MAX_TITLU,sizeof(char));
    if(!carte->titlu){
        
        free(carte);
        return NULL;

    }

    carte->autor = calloc(MAX_AUTOR,sizeof(char));
    if(!carte->autor){
        
        free(carte->titlu);
        free(carte);
        return NULL;

    }

    strcpy(carte->titlu,titlu);
    strcpy(carte->autor,autor);
    carte->rating = raiting;
    carte->nrPagini = nrPagini;

    return carte;

}

//Functie de afisare
int showInfo(TArbore aux,char *alert, FILE *fout){
    
    //Daca nu are linuk-ul catre structura
    if(!INFOADD(aux)) {
        
        fprintf(fout, "%s\n", alert);
        return -1;
    
    }
    
    Carte *carte = (Carte*)INFOADD(aux);

    fprintf(fout, "Informatii recomandare: %s, %s, %d, %d\n",
                carte->titlu, carte->autor, carte->rating, carte->nrPagini);

    return 0;

}

void freeInfo(void * info){

    if(!info) return ;

    Carte **carte = (Carte**)info;

    free((*carte)->titlu);
    free((*carte)->autor);
    free(*carte);
    *carte = NULL;
}

//Functie pentru freeInfoComplex, deoarece ea a fost deazolcata cu T1
void nothing(void *info){
    return;
}

void freeInfoComplex(void * info){

    TArbore* arb = (TArbore*)info;

    deleteTArbore(*arb,free,nothing);
    free(*arb);
    *arb = NULL;
}

int main(int argc, char* argv[]){

    FILE *fin, *fout;

    fin=fopen(argv[1], "r");
    fout=fopen(argv[2], "w");

    if(!fin || !fout){

        return 1;

    }

    prelucreFisier(fin,fout,myCharCmp,cmpChr,alocCarte,showInfo,freeInfo, freeInfoComplex);
    
    fclose(fin);
    fclose(fout);

    return 0;
}