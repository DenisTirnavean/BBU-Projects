#pragma once
#include "produs.h"

typedef void* TElement;
typedef void(*fct_distruge)(TElement);
typedef TElement(*fct_copy)(TElement);
typedef struct
{
    int cap;
    int lg;
    TElement* elems;
}MyList;

MyList* initList();
/*
 *functie care initializeaza lista de /~/produse/~/  ELEMENTE GENERIC
 */

void destroyList(MyList* list,fct_distruge distruge_element);
/*
 *functie care distruge o lista de /~/produse/~/   ELEMENTE GENERIC
 */

void adauga_element( TElement* e,MyList* list);
/*functie care adauga un /~/produs/~/ ELEMENT GENERIC in lista de /~/produse/~/ ELEMENT GENERIC
 *param: /~/produs produs, produs v (lista de produse), int n (lungimea listei)/~/
 */

void stergeProdus(int id, MyList* lista);
/*
 *functie care sterge un produs din lista de produse
 */

int filtrareProducator(MyList* lista, char producator[], produs* rezultate[]) ;
/*functie care afiseaza toate produsele din lista care au producatorul specificat
 *param: produs v (lista de produse), int n (lung listei), string producator
 */

int comp(produs* a, produs* b);
/*
 *functie de comparare pentru sortare
 */


int compDesc(produs* a, produs* b);
/*
 *functie de comparare (descrescator) pentru sortare
 */

void sortProduse(MyList* lista, produs* rezultate[], int (*functie_comp)(produs*, produs*));
/*
 *functie care sorteaza (crecator) produsele din lista dupa pret
 */


/*Functia de copiere lista
 *returns: o noua lista cu aceleasi elemente ca lista data ca parametru
*/
MyList* deepcopy(MyList* lista, fct_copy copy);