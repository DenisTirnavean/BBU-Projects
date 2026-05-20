//
// Created by Denis on 4/1/2025.
//

#include "produs.h"
#include <string.h>

int valideazaProdus(produs* pr){
    if (pr->id < 0 || pr->pret < 0 || pr->cantitate < 0)
        return 0;
    if (strlen(pr->tip) == 0 || strlen(pr->producator) == 0 || strlen(pr->model) == 0)
        return 0;
    return 1;
}
