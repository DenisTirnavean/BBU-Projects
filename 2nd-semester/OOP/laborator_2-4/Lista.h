#pragma once
#include "Domain.h"

//tipuri de date generice
typedef void* TElem;
typedef void(*fct_distruge)(TElem);
typedef TElem(*fct_copy)(TElem);

//Structura de lista generica
typedef struct {
	TElem* elems;
	int capacitate;
	int lungime;
}Lista;

/*Functia de creare lista goala
* returns: o lista goala
*/
Lista* creaza_lista();

/*Functia de redimensionare lista
* @lista - Lista
*/
void redimensionare(Lista* lista);

/*Functia de adaugare element nou in lista
* @lista - o lista generica
* elem - un element oarecare
*/
void adauga_element(Lista* lista, TElem* elem);

/*Functia de modificare a unui element de pe pozitia poz din lista
* @lista - o lista generica
* @poz - un indice(numar de ordine) din lista
* @elem - noul element(gata modificat)
* @distruge_elem - functia de distrugere element specific
*/
void modifica_element(Lista* lista, int poz, TElem elem, fct_distruge distruge_elem);


/*Functia de stergere a unui element de pe pozitia poz din lista
* @lista - o lista generica
* @poz - un indice(numar de ordine) din lista
* @distruge_elem - functia de distrugere element specific
*/
void sterge_element(Lista* lista, int poz, fct_distruge distruge_elem);

/*Functia de distrugere lista
* @lista - o lista generica
* @distruge_elem - functia de distrugere elemente din lista
*/
void distruge_lista(Lista* lista, fct_distruge distruge_elem);

/*Functia de deep-copy(clonare) lista
* @lista - lista generica
* @cpy - functia de copiere elemente din lista
*/
Lista* deep_copy(Lista* lista, fct_copy cpy);