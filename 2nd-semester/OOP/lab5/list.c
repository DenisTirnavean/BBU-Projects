#include <stdio.h>
#include <string.h>
#include "list.h"
#include <stdlib.h>

MyList* initList(){
    MyList* lista= (MyList*) malloc(sizeof(MyList));
    if(lista != NULL)
    {
        lista->cap = 5;
        lista->elems = malloc(sizeof(TElement) * lista->cap);
        lista->lg = 0;
    }
    return lista;
  }

void destroyList(MyList* lista,fct_distruge distruge) {
    for (int i = 0; i < lista->lg; i++) {
        distruge(lista->elems[i]);
    }
    lista->lg = 0;
    free(lista->elems);
    free(lista);
}

void adauga_element(TElement* e, MyList* lista){
    if (lista->lg >= lista->cap) {
        TElement* aux = malloc(sizeof(TElement)*(lista->cap + 5));
        for (int i = 0; i < lista->lg; i++) {
            aux[i] = lista->elems[i];
        }
        free(lista->elems);
        lista->elems = aux;
        lista->cap += 5;
    }

    lista->elems[lista->lg] = e;
    lista->lg++;
}

void stergeProdus(int id, MyList* lista) {
    //int gasit = 0;
    for (int i = 0; i < lista->lg; i++) {
        if (((produs*)lista->elems[i])->id == id) {
            //gasit = 1;
            destroyProdus(lista->elems[i]);
            for (int k = i; k < lista->lg - 1; k++) {
                lista->elems[k] = lista->elems[k + 1];
            }
            lista->lg--;
            break;
        }
    }
/*
    if (!gasit)
        printf("Nu exista produs cu acest ID!\n");
        */
}

int filtrareProducator(MyList* lista, char producator[], produs* rezultate[]) {
    int count = 0;
    for (int i = 0; i < lista->lg; i++) {
        if (strcmp(((produs*)lista->elems[i])->producator, producator) == 0) {
            rezultate[count++] = lista->elems[i];
        }
    }
    return count;
}

int comp(produs* a, produs* b) {
    if (a->pret > b->pret) return 1;
    if (a->pret < b->pret) return 0;
    if (a->cantitate > b->cantitate) return 1;
    if (a->cantitate < b->cantitate) return 0;
    return 0;
}

int compDesc(produs* a, produs* b) {
    if (a->pret > b->pret) return 0;
    if (a->pret < b->pret) return 1;
    if (a->cantitate > b->cantitate) return 0;
    if (a->cantitate < b->cantitate) return 1;
    return 0;
}

void sortProduse(MyList* lista, produs* rezultate[], int (*functie_comp)(produs*, produs*)) {
    for (int i = 0; i < lista->lg; i++)
        rezultate[i] = lista->elems[i];
    for (int i = 0; i < lista->lg-1; i++)
        for (int j = i+1; j < lista->lg; j++)
            if (functie_comp(rezultate[i], rezultate[j])) {
                produs* aux = rezultate[i];
                rezultate[i] = rezultate[j];
                rezultate[j] = aux;
            }
}

MyList* deepcopy(MyList* lista, fct_copy copy)
{
    MyList* new_list = malloc(sizeof(MyList));
    new_list->cap = lista->cap;
    new_list->lg = 0;

    new_list->elems = malloc(sizeof(TElement) * new_list->cap);
    for (int i = 0; i < lista->lg; i++)
    {
        produs* pr = copy(lista->elems[i]);
        adauga_element((TElement*)pr, new_list);
    }
    return new_list;
}