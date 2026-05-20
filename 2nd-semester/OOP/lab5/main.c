#include <stdio.h>
#include <string.h>
#include "validari.h"
#include "service.h"
#include "list.h"
#include "tests.h"

void functionalitate_filtru(MyList* lista)
{
    printf("Comenzi filtrare: tip(afiseaza produsele cu tip care incep cu o anumita litera), \ncantitate(produse cu o cantitate mai mica decat un anumit numar)\n");
    char cmd[30];
    printf("Comanda: ");
    scanf_s("%s",cmd,30);

    char val[30];
    printf("Valoarea dupa care se filtreaza: ");
    scanf_s("%s", val,30);
    MyList* filt = filter(lista, cmd, val, (fil_fct)functia_filtru);
    if (filt->lg== 0)
        printf("Filtrarea nu a reusit :(\n");

    else {
        for (int i = 0; i < filt->lg; i++)
            printf("%d %s %s %s %lf %d\n", ((produs*)(filt->elems[i]))->id, ((produs*)filt->elems[i])->tip, ((produs*)filt->elems[i])->producator, ((produs*)filt->elems[i])->model, ((produs*)filt->elems[i])->pret, ((produs*)filt->elems[i])->cantitate);
    }
    destroyList(filt,(fct_distruge)destroyProdus);
}

int main(void) {
    MyList* lista=initList();
    MyList* undo_list=initList();
    run_tests();

     while (1) {
         printf("\nMeniu functionalitati\n1. Adaugare produs\n2. Actualizare produs\n3. Afisare produse\n4. Filtreaza dupa producator\n5. Sterge produs\n6. Sorteaza produse\n7.Undo\n8.Noi filtrari\n0. Exit\n");
         printf(">>> ");
         char optiune;
         scanf(" %c", &optiune);

         switch (optiune) {
             case '0':
                 destroyList(lista,(fct_distruge)destroyProdus);
                 destroyUndo(undo_list);
                 printf("\nProgramul a fost oprit de catre utilizator.\n");
             return 0;

             case '1': {

                 int id, cantitate;
                 double pret;
                 char tip[15], producator[25], model[25];

                 printf("\nID Produs: ");
                 scanf_s("%d", &id);

                 printf("\nTip Produs: ");
                 scanf(" %[^\n]", tip);

                 printf("\nProducator Produs: ");
                 scanf(" %[^\n]", producator);

                 printf("\nModel Produs: ");
                 scanf(" %[^\n]", model);

                 printf("\nPret: ");
                 scanf_s("%lf", &pret);

                 printf("\nCantitate: ");
                 scanf_s("%d", &cantitate);

                 produs* pr = creeazaProdus(id, tip, producator, model, pret, cantitate);
                 if (valideazaProdus(pr) == 1)
                 {
                     add_to_undo(lista,undo_list);
                     adauga_element((TElement)pr, lista);
                 }
                 else
                     printf("\nValori invalide!\n");
                 break;

             }

             case '2':
                 int id;
                 double pret;

                 printf("\nID Produs: ");
                 scanf_s("%d", &id);

                 printf("\nPret nou: ");
                 scanf_s("%lf", &pret);
                 add_to_undo(lista,undo_list);
                 actualizareProdus(id, lista, pret);
                 break;

             case '3':
                 if (lista->lg == 0)
                     printf("Nu exista produse in lista!\n");
                 for (int i = 0; i < lista->lg; i++)
                     printf("%d %s %s %s %lf %d\n", ((produs*)(lista->elems[i]))->id, ((produs*)lista->elems[i])->tip, ((produs*)lista->elems[i])->producator, ((produs*)lista->elems[i])->model, ((produs*)lista->elems[i])->pret, ((produs*)lista->elems[i])->cantitate);
                 break;

             case '4':
                 char producator[25];
                 int x;
                 printf("Introduceti producator: ");
                 scanf(" %[^\n]", producator);
                 produs* prod[100];
                 x = filtrareProducator(lista, producator, prod);
                 for (int i=0; i<x; i++)
                     printf("%s ", prod[i]->model);
                 break;

             case '5':
                 int id_produs;
                 printf("Introduceti ID: ");
                 scanf_s("%d", &id_produs);
                 add_to_undo(lista,undo_list);
                 stergeProdus(id_produs, lista);
                 break;

             case '6':
                 printf("Introduceti modalitate(crescator/descrescator): \n");
                 char mode[15];
                 scanf(" %[^\n]", mode);
                 if (strcmp(mode, "crescator") == 0) {
                     int n = lista->lg;
                     produs* v[n];
                     sortProduse(lista, v, comp);
                     for (int i = 0; i < n; i++)
                         printf("%d %s %s %s %lf %d\n", v[i]->id, v[i]->tip, v[i]->producator, v[i]->model, v[i]->pret, v[i]->cantitate );
                 }
                 else if (strcmp(mode, "descrescator") == 0)
                 {
                     int n = lista->lg;
                     produs* v[n];
                     sortProduse(lista, v, compDesc);
                     for (int i = 0; i < n; i++)
                         printf("%d %s %s %s %lf %d\n", v[i]->id, v[i]->tip, v[i]->producator, v[i]->model, v[i]->pret, v[i]->cantitate );
                 }
                 else
                     printf("Modalitate invalida!\n");
             case '7':
                 if (undo_list->lg == 0)
                     printf("Nu ai la ce da undo!\n");
                 else
                    lista = undo(lista,undo_list);
                 break;
             case '8':
                    functionalitate_filtru(lista);
                 break;
             default:
                 printf("\nOptiune invalida!\n");
         }
    }


}