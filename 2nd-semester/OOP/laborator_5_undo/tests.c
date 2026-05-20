#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "service.h"
#include "list.h"
#include "validari.h"
#include "tests.h"

#include <stdlib.h>

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

    adauga_element(pr1, lista);
    adauga_element(pr2, lista);
    adauga_element(pr3, lista);
    adauga_element(pr4, lista);
    adauga_element(pr5, lista);
    adauga_element(pr6, lista);
    adauga_element(pr7, lista);
    assert(lista->lg == 7);
    printf("Testul pentru adaugaProdus a trecut!\n");

    destroyList(lista,destroyProdus);
}

void test_actualizareProdus() {
    MyList* lista=initList();

    produs* pr1 = creeazaProdus(1, "Telefon", "Apple", "iPhone 13", 3000.5, 10);
    adauga_element(pr1, lista);

    actualizareProdus(1, lista, 3500.0);
    assert(((produs*)lista->elems[0])->pret == 3500.0);

    actualizareProdus(1, lista, -100.0);
    actualizareProdus(999, lista, 1000.0);
    printf("Testul pentru actualizareProdus a trecut!\n");

    destroyList(lista,destroyProdus);
}

void test_stergeProdus() {
    MyList* lista=initList();


    produs* p1 = creeazaProdus(1, "Laptop", "Dell", "XPS", 5000.0, 10);
    produs* p2 = creeazaProdus(2, "Telefon", "Samsung", "S21", 3000.0, 5);
    produs* p3 = creeazaProdus(3, "Tableta","Apple", "iPad", 4000.0, 7);

    adauga_element(p1, lista);
    adauga_element(p2, lista);
    adauga_element(p3, lista);

    assert(lista->lg == 3);

    stergeProdus(2, lista);
    assert(lista->lg == 2);
    assert(((produs*)lista->elems[0])->id == 1);
    assert(((produs*)lista->elems[1])->id == 3);

    stergeProdus(5, lista);
    assert(lista->lg == 2);
    destroyList(lista,destroyProdus);
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

    destroyList(lista,destroyProdus);
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
    sortProduse(lista, rezultate, comp);

    assert(strcmp(rezultate[0]->model, "Galaxy S21") == 0);
    assert(strcmp(rezultate[1]->model, "iPhone 12") == 0);
    assert(strcmp(rezultate[2]->model, "iPhone 13") == 0);
    assert(strcmp(rezultate[3]->model, "MacBook Air") == 0);
    assert(strcmp(rezultate[4]->model, "XPS 13") == 0);


    printf("Testul pentru sortProdus a trecut!\n");

    destroyList(lista,destroyProdus);
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

    destroyList(lista,destroyProdus);
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
}
