
#include "service.h"


#include <stdlib.h>
#include <string.h>
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

/* Functionalitate de undo facuta de catre denis adrian */


void add_to_undo(MyList* lista, MyList* undo_list)
{
    adauga_element((TElement*)deepcopy(lista,(fct_copy)copyProdus),undo_list);
}

MyList* undo(MyList* lista,MyList* undo_list)
{
    destroyList(lista,(fct_distruge)destroyProdus);
    lista = deepcopy((MyList*)(undo_list->elems[(undo_list->lg)-1]),(fct_copy)copyProdus);
    destroyList((MyList*)undo_list->elems[(undo_list->lg)-1],(fct_distruge)destroyProdus);
    undo_list->lg = undo_list->lg - 1;
    return lista;
}
void destroyUndo(MyList* lista)
{
    for (int i = 0; i < lista->lg; i++)
        destroyList(lista->elems[i],(fct_distruge)destroyProdus);
    free(lista->elems);
    free(lista);
}

MyList* filter(MyList* lista, char* fil_crt, char* fil_val, fil_fct fil)
{
    MyList* filt_list = initList();
    if (strlen(fil_crt) <= 0 || strlen(fil_val)<=0)
        return filt_list;

    for (int i = 0; i < lista->lg; i++) {
        if (fil(lista->elems[i], fil_crt, fil_val)) {
            adauga_element((TElement)creeazaProdus(((produs*)lista->elems[i])->id,((produs*)lista->elems[i])->tip,((produs*)lista->elems[i])->producator,((produs*)lista->elems[i])->model,((produs*)lista->elems[i])->pret,((produs*)lista->elems[i])->cantitate), filt_list);
        }
    }
    return filt_list;
}

int functia_filtru(produs* pr, char* criteriu, char* val) {
    if (strcmp(criteriu, "tip") == 0)
        {
        if (strlen(val) > 1) return 0;
        return pr->tip[0] == val[0];
        }
    else if (strcmp(criteriu, "cantitate") == 0) {
        int nr = 0;
        for (int i = 0; i < (int)strlen(val); ++i) {
            if ('0' <= val[i] && val[i] <= '9') {
                nr = nr * 10 + (val[i] - '0');
            }
            else {
                return 0;
            }
        }
        return pr->cantitate <= nr;
    }
    return 0;
}