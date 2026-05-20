#pragma once

#include "Lista.h"

typedef int(*fil_fct)(TElem, char*, char*);
typedef int(*sort_fct)(TElem a, TElem b);

/*Functia de creaza, valideaza si adauga in lista materie prima cu specificatiile date
* @nume - sir de caractere, numele materiei
* @prod - sir de caractere, numele producatorului
* @cantitate - int, cantitatea de materie prima
* returns: 0 - daca all good, 1 - nume invalid(sir vid) , 2 -producator invalid(sir vid), 3 - cantitatea invalida (cantitate<=0)
*/
int creaza_valid_adaug(Lista* lista, char* nume, char* prod, int cantitate);

/*Functia care verifica daca exista in lista o materie cu numele si producatorul specificat
* @ nume - sir de caractere, nume materie
* @ prod - sir de caracater, nume producator
* returns: 1 - daca exista, 0 - altfel
*/
int exista_materie(Lista* lista, char* nume, char* prod);

/*Functia care gaseste indexul materiei indicate
* @ lista - Lista
* @ mat - o materie prima
* returns: (int)pozitia materiei in lista daca exista, -1 altfel
*/
int get_pozitie(Lista* lista, Materie_prima* mat);


/*Functia de filtrare lista dupa un anumit criteriu
* @lista - lista
* @fil_crt - modul in care care filtram(nume/cantitate)
* @fil_val - valoarea criteriului dupa care filtram
* fil - o functie care verifica daca un element respecta filtrul
* returns: o noua lista cu elemente ce respecta filtrul
*/
Lista* filter(Lista* lista, char* fil_crt, char* fil_val, fil_fct fil);

/*Functia de sortare lista dupa un anumit criteriu
* @lista - lista
* @ sort_fct cmp -  functia de comparare doua elemente
* @desc - 1/0 daca vrem sau nu ordonare in ordine descrescatoare
* returns: o noua lista cu elemete sortate dupa criteriul dat
*/
Lista* sort(Lista* lista, sort_fct cmp, int desc);