# Administrarea unui biblioteci personale
## Girnet Andrei

## Descriere
---
Fiecare carte va avea: un titlu unic, un autor, un rating (număr întreg, oferit de prietenul
lui Andrei odată cu recomandarea) și numărul de pagini. Este implementat introducerea unei carti noi si cautarea unei carti deja introduse intr-un mod eficient. Deasemenea programul are optiunea de auto-complite.

## Implementare
---
Pentru gestionarea cărților, folosesc următoarele structuri de date:
1. T1: un arbore de prefixe (trie), în care cheia este titlul cărții, iar informația reținută la
finalul căii este un pointer către o structură cu informațiile cărții;

2. T2: un alt arbore de prefixe (trie), în care cheia este un autor, iar informația reținută este
un alt arbore de prefixe (trie), în care sunt reținute cărțile scrise de acel autor, reținute
asemenea structurii 1.

## Structuri de date folosite
---
+ Arbore
        
    - Structura unui Arbore

+ TArbore

    - Pointer la o structura Arbore

+ Carte

    - Structura unei informatii

## Functii de prelucrare a unui Arbore
---
+ initArbore
        
    - Aloca un Arbore, returneaza adresa lui sau NULL;

+ resetNod

    - Reseaza pointerul vectoruilui urmator, a informatiei adaugatoare
    si seteaza numarul de noduri 0, nu dezaloca nimic;

+ extractNodeN

    - Extrage nodul n din arb->vctUrm si ii returneaza adresa

+ findNodeFromInfo

    - Gaseste la ce nod se afla o informatiei anumita, intoarce numarul
    nodului

+ goToNodeN

    - Muta pointerul arborelui la urmatorul n arbore

+ setInfoAdd

    - Seteaza cimpul aditional al structurii Arbore cu info

+ uniqPath

    - Verifica daca in arbore exista doar o singura frunza cu informatie
    (un singu drum radacina -> frunza)

    - Parcurg recursiv tot arborele si verific daca nu cumva exista
    despartituri sau alte informatii decit cea din capatul Arborelui
    returnez flase

+ addNode

    - adauga un nod dupa o recula data de cmp, returneaza pozitia la care a
    fost inserat, pozitiva daca e inserare noua, negativa daca deja exista,
    0 daca exista o eroare

    - Verific nod viitor nou, initializez stochez info

    - Caut unde sa fie inserat, realoc, mut memoria cu 1 * sizeof(Arbore)
    resetez informatia,memmove pastreaza info la sursa, adaug noua
    informatie

+ deletePath

    - Sterge drumul de la un nod la frunza, returneaza -1 daca exista erori
    0 daca e tot ok

    - Daca nu sa dat ca frunza un nod fara vctUrm, se va sterge doar infoAdd

    - Dezaloc Arborele de la de la nodul dorit, mut informatia, daca e
    necesar realoc, sau dau free

+ deleteTArbore

    - Dezaloca un TArbore recursiv

    - Daca exista sterg info, infoAdd, dupa ce ajunge la sfirsit daca exista
    sterg vcturm

## Functii de prelucrare a fisierului de input si a comenzilor recunoscute
---
+ addWord

    - Adauga un cuvint in arbore, firecare caracter nod aparte

    - Daca am obtinut o pozitie pozitiva stim ca e nod nou, pentru
    siguranta resetam nodul, fara ai schimba informatia

+ addBook

    - Adauga un titlu de carte in T1, autor in T2, un Arbore la capetele lui
    T2 cu titlul cartii noi, returneaza 0 daca tot ok, -1 sau -2 daca sunt
    errrori

    - Verific daca nu cumva deja exista aceasta carte, deci nu trebuie
    rescrisa

    - Verific daca deja exista acest autor sau e unul nou, adaug comform
    conditiei 

+  showFirst

    - Afiseaza cu un antet recursiv 3 - count path-uri, daca *count = -1, va
    afisa toate path-urile

    - Dupa ce sau afisat toate posibilitatile cu o informatie, acea
    informatie e scoasa din buff, buff-ul e setat cu '\0' pina la capat

+ search

    - Cauta un in arbore un path , daca nu exista afiseaza alert, daca 
    exista va returna ultimul nod

    - Prin efect colateral se va returna pointer la ultima dispartitura sau 
    pointer la ultimul nod ce are infoAdd diferit de cea cautat si pozitia 
    nodului din ramificare

+ searchBook

    - Cauta o carte in T1, daca numele ei se termina in ~ se va face
    autocomplete

+ listAutor

    - Cauta autor in T2, daca e gasit sunt afisate toate cartile sale, daca
    se termina in ~ se va face autocomplete

+ searchByAutor

    - Se auta autorul, apoi daca exista se afiseaza cartile lui, in
    dependenta de ~ functioneaza dupa conditii

+ deleteBook

    - Sterge informatia, titlul din T1, autorul din T2 dupa necesitate, si
    cartea din arborele infoAdd din T2

    - Caut titlul, si sterg info, fara a sterge infoAdd(Pointer la Carte),
    el va fi sters la sfirsit din Arborele infoAdd din T2

    - Daca e necesar sterg atorul, si apoi sterg si infoAdd din T2 si
    structura Carte

+ prelucreFisier

    - Se recunoaste comanda si se executa

    - In caz ca a esuat addNode, inseamna ca nu mai exista memorie
    deci programul se va opri

## Functii Generale folosite pentru structua Carte
---
+ myCharCmp

    - Calculeaza pozitia in CHARORD, face aceasta diferenta si o returneaza

+ cmpChr

    - Sunt 2 *(char*) egale

+ alocCarte

    - Aloca o structura Carte

+ showInfo

    - Functie de afisare a informatiei, sau daca sa dat un pointer nevalid
    (trebuie sa fie TArbore cu link infoAdd) afiseaza alert

+ freeInfo

    - Elibereaza memoria unui Carti

+ doNothing

    - E folosita in delete, pentru a nu da free de mai multe ori de cit
    trebuie

+ freeInfoComplex

    - Elibereaza un TArbore care are un alt TArbore in infoAdd, cu conditia
    ca infoAdd va fi eliberat prin alta metoda

Drepturile de autor pentru checker si conditie apartin echipei Structuri de Date UPB 2020

Drepturile fata de rezolvarea cerintelor apartin Girnet Andrei