#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "service.h"
#include "list.h"
#include "validari.h"
#include "tests.h"



void test_creeazaProdus() {
    produs* pr = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    assert(pr->id == 1);
    assert(strcmp(pr->tip, "Telefon") == 0);
    assert(strcmp(pr->producator, "Apple") == 0);
    assert(strcmp(pr->model, "iPhone 13") == 0);
    assert(pr->pret == 3000.5);
    assert(pr->cantitate == 10);
    printf("Testul pentru creeazaProdus a trecut!\n");

    destroyProdus(pr);
}

void test_valideazaProdus() {
    produs* pr1 = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    produs* pr2 = creeazaProdus(-1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    produs* pr3 = creeazaProdus(2, "", "Apple", "iPhone 13", 3000.5, 10);
    assert(valideazaProdus(pr1) == 1);
    assert(valideazaProdus(pr2) == 0);
    assert(valideazaProdus(pr3) == 0);
    printf("Testul pentru valideazaProdus a trecut!\n");

    destroyProdus(pr1);
    destroyProdus(pr2);
    destroyProdus(pr3);
}
void test_adaugaProdus() {
    MyList* lista=initList();

    produs* pr1 = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    produs* pr2 = creeazaProdus(1, "Telefon", "Samsung", "Galaxy S21", 2000.5, 5);
    produs* pr3 = creeazaProdus(2, "Telefon", "Samsung", "Galaxy S31", 24000.5, 5);
    produs* pr4 = creeazaProdus(3, "Telefon", "Samsung", "Galaxy S41", 6000.5, 5);
    produs* pr5 = creeazaProdus(4, "Telefon", "Samsung", "Galaxy S51", 4000.5, 5);
    produs* pr6 = creeazaProdus(5, "Telefon", "Samsung", "Galaxy S61", 23000.5, 5);
    produs* pr7 = creeazaProdus(6, "Telefon", "Samsung", "Galaxy S71", 4000.5, 5);

    adauga_element((TElement*)pr1, lista);
    adauga_element((TElement*)pr2, lista);
    adauga_element((TElement*)pr3, lista);
    adauga_element((TElement*)pr4, lista);
    adauga_element((TElement*)pr5, lista);
    adauga_element((TElement*)pr6, lista);
    adauga_element((TElement*)pr7, lista);
    assert(lista->lg == 7);
    printf("Testul pentru adaugaProdus a trecut!\n");

    destroyList(lista,(fct_distruge)destroyProdus);
}

void test_actualizareProdus() {
    MyList* lista=initList();

    produs* pr1 = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    adauga_element((TElement*)pr1, lista);

    actualizareProdus(1, lista, 3500.0);
    assert(((produs*)lista->elems[0])->pret == 3500.0);

    actualizareProdus(1, lista, -100.0);
    actualizareProdus(999, lista, 1000.0);
    printf("Testul pentru actualizareProdus a trecut!\n");

    destroyList(lista,(fct_distruge)destroyProdus);
}

void test_stergeProdus() {
    MyList* lista=initList();


    produs* p1 = creeazaProdus(1, "Laptop", "Dell", "XPS", 5000.0, 10);
    produs* p2 = creeazaProdus(2, "Telefon", "Samsung", "S21", 3000.0, 5);
    produs* p3 = creeazaProdus(3, "Tableta","Apple", "iPad", 4000.0, 7);

    adauga_element((TElement*)p1, lista);
    adauga_element((TElement*)p2, lista);
    adauga_element((TElement*)p3, lista);

    assert(lista->lg == 3);

    stergeProdus(2, lista);
    assert(lista->lg == 2);
    assert(((produs*)lista->elems[0])->id == 1);
    assert(((produs*)lista->elems[1])->id == 3);

    stergeProdus(5, lista);
    assert(lista->lg == 2);
    destroyList(lista,(fct_distruge)destroyProdus);
    printf("Testele au trecut cu succes!\n");
}
void test_filtrareProducator() {

    MyList* lista=initList();

    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);

    // produse rezultate;
    // initList(&rezultate);
    produs* rezultate[15];
    int n = filtrareProducator(lista, "Apple", rezultate);

    assert(n == 3);
    assert(rezultate[0]->id == 1);
    assert(strcmp(rezultate[0]->model, "iPhone 13") == 0);
    assert(rezultate[1]->id == 4);
    assert(strcmp(rezultate[1]->model, "iPhone 12") == 0);
    assert(rezultate[2]->id == 5);
    assert(strcmp(rezultate[2]->model, "MacBook Air") == 0);
    assert(strcmp(rezultate[0]->producator, "Apple") == 0);
    assert(strcmp(rezultate[1]->producator, "Apple") == 0);
    assert(strcmp(rezultate[2]->producator, "Apple") == 0);
    assert(strcmp(((produs*)lista->elems[1])->producator, "Dell") == 0);
    assert(strcmp(((produs*)lista->elems[2])->producator, "Samsung") == 0);

    printf("Testul pentru filtrareProducator a trecut!\n");

    destroyList(lista,(fct_distruge)destroyProdus);
    //destroyList(rezultate);
}

void test_sortProdus() {

    MyList* lista=initList();
    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);

    produs* rezultate[15];
    sortProduse(lista, rezultate,comp);

    assert(strcmp(rezultate[0]->model, "Galaxy S21") == 0);
    assert(strcmp(rezultate[1]->model, "iPhone 12") == 0);
    assert(strcmp(rezultate[2]->model, "iPhone 13") == 0);
    assert(strcmp(rezultate[3]->model, "MacBook Air") == 0);
    assert(strcmp(rezultate[4]->model, "XPS 13") == 0);


    printf("Testul pentru sortProdus a trecut!\n");

    destroyList(lista,(fct_distruge)destroyProdus);
}

void test_sortProdusDesc() {

    MyList* lista=initList();
    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);

    produs* rezultate[15];
    sortProduse(lista, rezultate, compDesc);

    assert(strcmp(rezultate[4]->model, "Galaxy S21") == 0);
    assert(strcmp(rezultate[3]->model, "iPhone 12") == 0);
    assert(strcmp(rezultate[2]->model, "iPhone 13") == 0);
    assert(strcmp(rezultate[0]->model, "XPS 13") == 0);
    assert(strcmp(rezultate[1]->model, "MacBook Air") == 0);

    printf("Testul pentru sortProdusDesc a trecut!\n");

    destroyList(lista,(fct_distruge)destroyProdus);
}
void test_copy_produs()
{
    produs* pr1 = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    produs* pr2 = copyProdus(pr1);
    assert(strcmp(pr1->model, pr2->model) == 0);
    assert(strcmp(pr1->producator, pr2->producator) == 0);
    assert(pr1->id== pr2->id);
    assert(strcmp(pr1->tip, pr2->tip) == 0);
    assert(pr1->cantitate== pr2->cantitate);
    assert(pr1->pret==pr2->pret);
    destroyProdus(pr1);
    destroyProdus(pr2);
}
void comparari()
{
    produs* pr1 = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    produs* pr2 = copyProdus(pr1);
    int x = comp(pr1,pr2);
    assert(x==0);
    int y = compDesc(pr1,pr2);
    assert(y==0);
    destroyProdus(pr1);
    destroyProdus(pr2);
}
void test_deep()
{
    MyList* lista=initList();
    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);
    MyList* copie_adinca = deepcopy(lista,(fct_copy)copyProdus);
    assert(copie_adinca->lg==lista->lg);
    assert(copie_adinca->cap==lista->cap);
    assert(((produs*)copie_adinca->elems[0])->id ==((produs*)lista->elems[0])->id);
    assert(((produs*)copie_adinca->elems[0])->cantitate ==((produs*)lista->elems[0])->cantitate);
    assert(((produs*)copie_adinca->elems[0])->pret ==((produs*)lista->elems[0])->pret);
    assert(strcmp(((produs*)copie_adinca->elems[0])->tip,((produs*)lista->elems[0])->tip)==0);
    assert(strcmp(((produs*)copie_adinca->elems[0])->producator,((produs*)lista->elems[0])->producator)==0);
    assert(strcmp(((produs*)copie_adinca->elems[0])->model,((produs*)lista->elems[0])->model)==0);
    destroyList(lista,(fct_distruge)destroyProdus);
    destroyList(copie_adinca,(fct_distruge)destroyProdus);
}
void test_add_undo()
{

    MyList* lista=initList();
    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);
    MyList* undo_lst=initList();
    assert(undo_lst->lg==0);
    add_to_undo(lista,undo_lst);
    assert(undo_lst->lg==1);
    add_to_undo(lista,undo_lst);
    add_to_undo(lista,undo_lst);
    add_to_undo(lista,undo_lst);
    assert(undo_lst->lg==4);
}

void test_undo_doamne_ajuta()
{
    MyList* lista=initList();
    MyList* undo_lst=initList();
    assert(undo_lst->lg==0);
    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    add_to_undo(lista,undo_lst);
    assert(undo_lst->lg==1);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    add_to_undo(lista,undo_lst);
    assert(undo_lst->lg==2);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    add_to_undo(lista,undo_lst);
    assert(undo_lst->lg==3);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    add_to_undo(lista,undo_lst);
    assert(undo_lst->lg==4);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);
    assert(lista->lg==5);
    lista=undo(lista,undo_lst);
    assert(lista->lg==4);
    lista=undo(lista,undo_lst);
    assert(lista->lg==3);
    lista=undo(lista,undo_lst);
    assert(lista->lg==2);
    destroyList(lista,(fct_distruge)destroyProdus);
    destroyUndo(undo_lst);
}
void test_filtrele_denis()
{
    char criteriu1[30];
    char criteriu2[30];
    strcpy_s(criteriu1, 5, "tip");
    strcpy_s(criteriu2, 10, "cantitate");
    produs* pr = creeazaProdus(1,"laptop","asus","vivobook",12.5,30);
    assert(functia_filtru(pr, criteriu1, "l") == 1);
    assert(functia_filtru(pr, criteriu1, "d") == 0);
    assert(functia_filtru(pr, criteriu2, "31") == 1);
    assert(functia_filtru(pr, criteriu2, "a") == 0);
    assert(functia_filtru(pr, criteriu1, "an") == 0);
    assert(functia_filtru(pr, "banane", "an") == 0);
    destroyProdus(pr);
    MyList* lista=initList();
    adauga_element((TElement*)creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10),lista);
    adauga_element((TElement*)creeazaProdus(2, "Laptop", "Dell", "XPS 13", 5000.5, 5),lista);
    adauga_element((TElement*)creeazaProdus(3, "Telefon", "Samsung", "Galaxy S21", 2000.5, 15),lista);
    adauga_element((TElement*)creeazaProdus(4, "Telefon", "Apple", "iPhone 12", 2500.5, 20),lista);
    adauga_element((TElement*)creeazaProdus(5, "Laptop", "Apple", "MacBook Air", 4000.0, 8),lista);
    MyList* filt=filter(lista,"tip","T",(fil_fct)functia_filtru);
    assert(filt->lg==3);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"tip","ab",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"tip","A",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt = filter(lista,"cantitate","an",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"cantitate","30",(fil_fct)functia_filtru);
    assert(filt->lg==5);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"banane","30",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"","30",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"banane","",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
    filt=filter(lista,"","",(fil_fct)functia_filtru);
    assert(filt->lg==0);
    destroyList(filt,(fct_distruge)destroyProdus);
}
void run_tests(){
    test_creeazaProdus();
    test_valideazaProdus();
    test_actualizareProdus();
    test_adaugaProdus();
    test_filtrareProducator();
    test_sortProdus();
    test_sortProdusDesc();
    test_stergeProdus();


    test_copy_produs();
    test_deep();
    test_add_undo();
    test_undo_doamne_ajuta();
    comparari();
    test_filtrele_denis();
}
