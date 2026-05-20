#include "Lista.h"
#include "Domain.h"
#include <stdlib.h>

Lista* creaza_lista() {
    Lista* lista = malloc(sizeof(Lista));
    if (lista != NULL)
    {
        lista->capacitate = 50;
        lista->lungime = 0;
        lista->elems = malloc(lista->capacitate * sizeof(TElem));
    }
    return lista;
}

void redimensionare(Lista* lista) {
    if (lista->lungime == lista->capacitate) {
        lista->capacitate *= 2;
        TElem* temp = malloc(lista->capacitate * sizeof(TElem));
        for (int i = 0; i < lista->lungime; ++i) {
            temp[i] = lista->elems[i];
        }
        free(lista->elems);
        lista->elems = temp;
    }
}

void adauga_element(Lista* lista, TElem* elem) {
    redimensionare(lista);
    lista->elems[lista->lungime++] = elem;
}

void modifica_element(Lista* lista, int poz, TElem elem, fct_distruge distruge_elem) {
    distruge_elem(lista->elems[poz]);
    lista->elems[poz] = elem;
}

void sterge_element(Lista* lista, int poz, fct_distruge distruge_elem)
{
    distruge_elem(lista->elems[poz]);
    for (int i = poz + 1; i < lista->lungime; i++) {
        lista->elems[i - 1] = lista->elems[i];
    }
    lista->lungime-=1;
}

void distruge_lista(Lista* lista, fct_distruge distruge_element)
{
    for (int i = 0; i < lista->lungime; i++)
        distruge_element(lista->elems[i]);
    free(lista->elems);
    free(lista);
}

Lista* deep_copy(Lista* lista, fct_copy copiaza_element)
{
    Lista* cop = creaza_lista();
    for (int i = 0; i < lista->lungime; ++i) {
        adauga_element(cop, copiaza_element(lista->elems[i]));
    }
    return cop;
}