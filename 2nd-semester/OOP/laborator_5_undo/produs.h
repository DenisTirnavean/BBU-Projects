#pragma once

typedef struct {
    int id;
    char* tip;
    char* producator;
    char* model;
    double pret;
    int cantitate;
}produs;

produs* creeazaProdus(int id, char* tip, char* producator, char* model, double pret, int cantitate);
/*functie care creeaza un produs electronic
 *param: int id, string tip, string producator, string model, double pret, int cantitate
 */

void destroyProdus(produs* produs);
/*
 *functie care distruge un produs
 */


/*Functia de copiere produs
 *returns: un nou produs cu aceleasi specificatii ca produsul dat parametru
*/
produs* copyProdus(produs* produs);