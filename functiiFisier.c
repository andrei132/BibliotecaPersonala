#include "general.h"

//Intoarce adresa ultimei celule din ramura sau NULL daca nu sa primit ceva
void* addWord(char *buff,TArbore arb,cmpFunc cmp){

    char *auxChar;
    int pos, i;

    for ( i = 0; buff[i] != '\0'; i++ ){
        
        auxChar = calloc(1, sizeof(char));
        *auxChar = buff[i];

        pos = addNode(arb, auxChar, cmp);
        
        if(pos == 0){
            
            free(auxChar);
            return NULL;
            
        }

        if(pos < 0) {free(auxChar);} 

        goToNodeN(&arb, abs(pos) - 1);
        
        //Daca pos pozitiv inseamna ca e chee noua, toate mai deptare vor fi noi
        if(pos > 0) resetNod(arb);

    }   

    return arb;

}

//Adauga o carte in toate structurile
int addBook(char *buff,TArbore T1, TArbore T2,cmpFunc cmp,alocInfo aloc,freeFunc freeInfo){

    TArbore aux;
    Carte *carte = aloc(buff);

    aux = (TArbore)addWord(carte->titlu, T1, cmp);

    //Deja exista aceasta carte
    if(aux->infoAdd) {
    
        freeInfo(&carte);
        return -1;
    
    }

    setInfoAdd(aux,carte);

    aux = (TArbore)addWord(carte->autor, T2, cmp);

    //Daca are infoAdd, pentru link-ul catre noul Arbore
    if(aux->infoAdd){

        TArbore aux2 = (TArbore)aux->infoAdd;
        
        aux2 = addWord(carte->titlu, aux2, cmp);
        setInfoAdd(aux2, carte);

    } else {
        
        TArbore aux2 = initArbore();
        setInfoAdd(aux, aux2);

        aux2 = addWord(carte->titlu, aux2, cmp);
        setInfoAdd(aux2, carte);

    }

    return 0;

}

/*
 * Afiseaza carti dintr-un Arbore, daca *count e setat -1 se vor afisa toate 
 * path-urile cu un antent, daca e setat cu alt numar se vor afisa 3 - (*count)
 */
int showFirst(FILE *fout, TArbore arb, char *antent,int *count,char *buff){

    if (*count != -1 && (*count > 2)) return -1;
    if(arb == NULL) return -1;
    
    if(INFO(arb)) buff[strlen(buff)] = *(char*)INFO(arb);

    //Am gasit o informatie care trebuie afisata
    if(INFOADD(arb) != NULL ){

        fprintf(fout,"%s%s\n" ,antent, buff);
        if (*count != -1) (*count)++;

    }

    //Caut in celelate noduri
    for(int i = 0; i < NRNODURI(arb); i++){

         showFirst(fout, arb->vctUrm + i, antent, count, buff);

    }    

    //Daca buff nu e gol, scot cheea pentru care deja sa afisat
    if (strlen(buff) != 0) 
        memset(&buff[strlen(buff)-1], '\0', MAX_TITLU-strlen(buff));
        
    return 0;
    
}

/*
 * Cauta in arbore path, daca il gaseste intoarce ultimul nod si prin efect
 * colateral nodul sau pointerul nodului cu ultima informatie diferita de cea 
 * care e cautat si pozitia de unde a inceput ramificarea 
 */
TArbore search(TArbore arb, char *buff,FILE *fout,const char *alert, TArbore *flag,cmpFunc cmp, int *positia){

    int pos;
    TArbore aux = arb;
    *flag= NULL;

    /*Verific daca nu se termina in \n si daca nu se termina
     * in carriage return de la strtok*/
    if(buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '\0';
    if(buff[strlen(buff) - 1] == 13) buff[strlen(buff) - 1] = '\0';

    for (int i = 0; buff[i] != '\0' && buff[i] != '~'; i++){

        pos = findNodeFromInfo(aux,&buff[i],cmp);
        
        if(pos == -1) {
            
            fprintf(fout,"%s\n",alert);
            return NULL;
        
        }
        
        if(NRNODURI(aux) > 1 || INFOADD(aux)) {
            
            *flag = aux;
            *positia = pos;
        
        }

        pos = goToNodeN(&aux,pos);
        
        if (pos){
            
            fprintf(fout,"%s\n",alert);
            return NULL;

        } 

    }

    return aux;

}

//Gaseste cartea
int searchBook(char* buff, TArbore T1, cmpFunc cmp,printFunc printInfo ,FILE *fout){
    
    int pos;
    TArbore aux ,flag;
    char *alert = calloc(50+MAX_TITLU,sizeof(char));

    /*Verific daca nu se termina in \n si daca nu se termina
     * in carriage return de la strtok*/
    if(buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '\0';
    if(buff[strlen(buff) - 1] == 13) buff[strlen(buff) - 1] = '\0';
    
    if(buff[strlen(buff) - 1] == '~'){ 
        
        sprintf(alert,"Nicio carte gasita."); 
    
    } else{

        sprintf(alert,"Cartea %s nu exista in recomandarile tale.",buff);

    }

    aux = search(T1,buff,fout,alert,&flag,cmp,&pos);
    if(!aux) {
        
        free(alert);
        return -1;
        
    }

    int c = strlen(buff) - 1;
    
    if(buff[c] == '~'){
        
        buff[c - 1] = '\0';

        char *path = calloc(MAX_TITLU + 1, sizeof(char));
        c = 0;

        showFirst(fout,aux,buff,&c,path);
        
        free(path);
        free(alert);
        
        return 0;

    }

    printInfo(aux,alert,fout);
    free(alert);
    return 0;
    

}

//Listeaza autor
TArbore listAutor(char *buff,TArbore T2,cmpFunc cmp,FILE *fout){

    int pos;
    TArbore aux ,flag;
    char *alert = calloc(50+MAX_TITLU,sizeof(char));

    /*Verific daca nu se termina in \n si daca nu se termina
     * in carriage return de la strtok*/
    if(buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '\0';
    if(buff[strlen(buff) - 1] == 13) buff[strlen(buff) - 1] = '\0';
    
    if(buff[strlen(buff) - 1] == '~'){ 
        
        sprintf(alert,"Niciun autor gasit."); 
    
    } else{

        sprintf(alert,"Autorul %s nu face parte din recomandarile tale.",buff);
        
    }

    aux = search(T2,buff,fout,alert,&flag,cmp,&pos);
    if(!aux) {
        
        free(alert);
        return NULL;
        
    }

    int c = strlen(buff) - 1;

    if(buff[c] == '~'){

        buff[c - 1] = '\0';
        char *path = calloc(MAX_TITLU +1, sizeof(char));
        c = 0;

        showFirst(fout,aux,buff,&c,path);
        
        free(path);
        free(alert);
        
        return NULL;

    }
    
    //Daca sa terminat titlul insa oricum nu are linuk-ul catre structura
    if(!INFOADD(aux)) {
            
        fprintf(fout,"%s\n",alert);
        free(alert);
        return NULL;
        
    }

    free(alert);
    return INFOADD(aux); 
    
} 

//Gaseste autorul
int searchByAutor(char *buff,TArbore T2,cmpFunc cmp,printFunc printInfo,FILE *fout){
    
    char *autor = strtok(buff,":");
    char *titlu = strtok(NULL,":\0\n ");

    TArbore aux = listAutor(autor,T2,cmp,fout);
    if(!aux) return -1;

    searchBook(titlu,aux,cmp,printInfo,fout);

    return 0;

}
//Functie pentru freeInfoComplex, deoarece ea a fost deazolcata cu T1
void doNothing(void *info){
    return;
}

//Sterge carte
int deleteBook(char *buff,TArbore T1, TArbore T2,cmpFunc cmp,freeFunc freeInfo, freeFunc freeInfoComplex,FILE *fout){

    char *autor;
    TArbore aux,flag,flag2;
    int pos;
    char *alert = calloc(50 + MAX_TITLU,sizeof(char));
    
    sprintf(alert,"Cartea %s nu exista in recomandarile tale.",buff);
    
    aux = search(T1,buff,fout,alert,&flag,cmp,&pos);
    if (!aux) {free(alert); return -1;}
    if(!INFOADD(aux)) {
        
        fprintf(fout,"%s\n",alert);
        free(alert);
        return -1;
    
    } 
    Carte *carte = ((Carte *)INFOADD(aux));
    autor = calloc(strlen(carte->autor) + 1, sizeof(char));
    strcpy(autor , (((Carte *)INFOADD(aux))->autor));
    
    deletePath(T1,aux,flag,free,doNothing,pos);

    aux = search(T2,autor,fout,"\0",&flag,cmp,&pos);
    free(autor);
    if (!aux){free(alert); return -1;}
    if(!INFOADD(aux)) {
        
        fprintf(fout,"%s\n",alert);
        free(alert);
        return -1;
    
    }

    flag2 = (TArbore)INFOADD(aux);
    
    if(uniqPath(flag2)) deletePath(T2,aux,flag,free,doNothing,pos);

    aux = search(flag2,buff,fout,"\0",&flag,cmp,&pos);
    if (!aux) {free(alert); return -1;}
    if(!INFOADD(aux)) {
        
        fprintf(fout,"%s\n",alert);
        free(alert);
        return -1;
    
    }

    deletePath(flag2,aux,flag,free,freeInfo,pos);
    free(alert);
    return 0;

}

//Functia de prelucre a comenzilor
void prelucreFisier(FILE *fin,FILE *fout,cmpFunc cmpOrdonat,cmpFunc cmpIdentic,alocInfo aloc,printFunc printInfo, freeFunc freeInfo, freeFunc freeInfoComplex){
    
    int pos;
    char *comm,*flag;
    char *buff = calloc(256,sizeof(char));

    if(!buff){
        
        return ;
    
    }
    flag = buff;

    comm = calloc(20,sizeof(char));

    if(!comm){
        
        free(buff);
        return ;

    }
    
    TArbore T1 = initArbore();
    TArbore T2 = initArbore();

    while(fgets(buff,255,fin) != NULL){
        
        //newline si carriage return de la strcmp
        if(buff[strlen(buff)-1] == '\n') {
            
            buff[strlen(buff)-1] = '\0';
        
        }
        
        if(buff[strlen(buff)-1] == 13) {
            
            buff[strlen(buff)-1] = '\0';
        
        }

        if(*buff == '\0' ) continue;
        
        sscanf(buff,"%s%n",comm,&pos);
        buff += pos + 1;

        if (!strcmp(comm,"add_book")){
            
            addBook(buff,T1,T2,cmpOrdonat,aloc,freeInfo);

        }

        if (!strcmp(comm,"search_book")){


            searchBook(buff,T1,cmpIdentic,printInfo,fout);

        }

        if (!strcmp(comm,"list_author")){
            
            TArbore aux =  listAutor(buff,T2,cmpIdentic,fout);

            if(aux){

                char *path = calloc(MAX_TITLU + 1, sizeof(char));
                int c = -1;
                showFirst(fout,aux,"",&c,path);
                free(path);

            }
            
        }

        if (!strcmp(comm,"search_by_author")){

            searchByAutor(buff,T2,cmpIdentic,printInfo,fout);
            
        }

        if (!strcmp(comm,"delete_book")){
        
            deleteBook(buff,T1,T2,cmpIdentic,freeInfo,freeInfoComplex,fout);

        }

        buff = flag;
    }

    free(flag);
    free(comm);
    deleteTArbore(T1,free,freeInfo);
    free(T1);
    deleteTArbore(T2,free,freeInfoComplex);
    free(T2);

}