#pragma once
//Structura de materie prima pentru cofetarie
typedef struct {
    char* nume;
    char* producator;
    int cantitate;
}Materie_prima;

/*Functia de creare o noua materie prima cu numele, producatorul si cantitatea specificate
* @nume - sir de caractere, numele materiei prime
* @producator - sir de caractere, producatorul materiei prime
* @cantitate - numar intreg, cantitatea de materie prima
* returns: materie prima
*/
Materie_prima* creaza_materie(char* nume, char* producator, int cantitate);

/*Functia de validare materie prima
* @nume - sir de caractere, numele materiei prime
* @producator - sir de caractere, producatorul materiei prime
* @cantitate - numar intreg, cantitatea de materie prima
* returns: 0 - daca materia prima este valida, 1 - daca numele este vid, 2 - daca producatorul este sir vid, 3 - cantitatea este <=0
*/
int valideaza_materie(char* nume, char* producator, int cantitate);

 /* Functia care distruge o materie prima
 * returns: -
 */
void distruge_materie(Materie_prima* materie);

/*Functia care verifica daca doua materii prime sunt egale
* returns: 1 - daca materiile sunt egale, 2 - altfel
*/
int sunt_materii_egale(Materie_prima* mat1, Materie_prima* mat2);


/*Functia care verifica daca numele producatorilor a doua materii prime sunt in ordine invers lexicografic
* @a - materie_prima
* @b - materie_prima
* returns: 1/0 daca numele producatorilor materiilor a si b sunt(sau nu) in ordine invers lexicografic
*/
int comp_prod(Materie_prima* a, Materie_prima* b);

/*Functia de copiere materie prima
* @materie - materie prima
* returns: o noua materie prima cu aceleasi specificatii
*/
Materie_prima* copiaza_materie(Materie_prima* materie);

/*Functia care verifica daca materia prima materie respecta filtrul
* @materie - o materie prima
* @criteriu - sir de caractere, criteriul dupa care filtram
* @val - valoarea criteriului dupa care filtram(o litera sau un numar)
*/
int functia_filtru(Materie_prima* materie, char* criteriu, char* val);

/*Functia care verifica daca numele a doua materii prime sunt in ordine invers lexicografic
* @a - materie_prima
* @b - materie_prima
* returns: 1/0 daca numele materiilor a si b sunt(sau nu) in ordine invers lexicografic
*/
int comp_nume(Materie_prima* a, Materie_prima* b);

/*Functia care compara cantitatile a doua materii
* @a - materie_prima
* @b - materie_prima
* returns: 1 daca materia a este in cantitate mai mare ca b, 0 altfel
*/
int comp_cant(Materie_prima* a, Materie_prima* b);