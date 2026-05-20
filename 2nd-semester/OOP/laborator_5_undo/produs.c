#include <stdio.h>
#include "produs.h"
#include <string.h>
#include <stdlib.h>

produs* creeazaProdus(int id, char* tip, char* producator, char* model, double pret, int cantitate) {
    produs* pr = malloc(sizeof(produs));
    pr->id = id;
    // int lenTip = strlen(tip) + 1;
    // int lenProducator = strlen(producator) + 1;
    // int lenModel = strlen(model) + 1;
    pr->tip = (char*)malloc(strlen(tip) + 1);
    pr->producator = (char*)malloc(strlen(producator) + 1);
    pr->model = (char*)malloc(strlen(model) + 1);
    strcpy(pr->tip, tip);
    strcpy(pr->producator, producator);
    strcpy(pr->model, model);
    pr->pret = pret;
    pr->cantitate = cantitate;
    return pr;
}

void destroyProdus(produs* pr) {
    if (pr != NULL) {
        free(pr->tip);
        free(pr->producator);
        free(pr->model);
        free(pr);
    }

}

produs* copyProdus(produs* produs)
{
    return creeazaProdus(produs->id, produs->tip, produs->producator, produs->model , produs->pret, produs->cantitate);
}