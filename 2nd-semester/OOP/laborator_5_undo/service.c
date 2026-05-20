//
// Created by Denis on 4/1/2025.
//

#include "service.h"

#include <stdlib.h>

#include "produs.h"

void actualizareProdus(int id, MyList* lista, double pret){
    int gasit = 0;
    if (pret < 0){
        return;
    }
    for (int i = 0; i < lista->lg; i++)
        if (((produs*)lista->elems[i])->id == id){
            ((produs*)lista->elems[i])->pret = pret;
            gasit = 1;
            break;
        }
    if (!gasit)
        return;
}

void add_to_undo(MyList* lista, MyList* undo_list)
{
    adauga_element(deepcopy(lista,copyProdus),undo_list);
}
void undo(MyList* lista,MyList* undo_list)
{
    destroyList(lista,destroyProdus);
    lista = deepcopy(undo_list->elems[undo_list->lg],copyProdus);
    destroyList(undo_list->elems[undo_list->lg],destroyProdus);
    undo_list->lg = undo_list->lg - 1;
}
void destroyUndo(MyList* undo)
{
    for (int i = 0; i < undo->lg; i++)
        destroyList(undo->elems[i],destroyProdus);
    free(undo->elems);
    free(undo);
}