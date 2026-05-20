#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "Domain.h"
#include "Lista.h"
#include "Service.h"

//teste domain
void test_crud_materie()
{
	Materie_prima* mat = creaza_materie("ciocolata", "milka", 12);
	assert(strcmp(mat->nume, "ciocolata") == 0);
	assert(strcmp(mat->producator, "milka") == 0);
	assert(mat->cantitate == 12);
	distruge_materie(mat);
}
void test_validator()
{
	char nume[30];
	strcpy_s(nume, 30, "milka");
	char producator[30];
	strcpy_s(producator, 30, "ciocolata");

	int cantitate = 10;
	int ok = valideaza_materie(nume, producator, cantitate);
	assert(ok == 0);
	strcpy_s(nume, 30, "");
	ok = valideaza_materie(nume, producator, cantitate);
	assert(ok == 1);
	strcpy_s(nume, 30, "milka");
	strcpy_s(producator, 30, "");
	ok = valideaza_materie(nume, producator, cantitate);
	assert(ok == 2);
	strcpy_s(producator, 30, "john snow");
	cantitate = -255;
	ok = valideaza_materie(nume, producator, cantitate);
	assert(ok == 3);
}
void test_copy_materie()
{
	Materie_prima* mat1 = creaza_materie("ciocolata", "milka", 12);
	Materie_prima* mat2 = copiaza_materie(mat1);
	assert(sunt_materii_egale(mat1, mat2) == 1);
	distruge_materie(mat1);
	distruge_materie(mat2);
}
void test_egale()
{
	Materie_prima* mat1 = creaza_materie("ciocolata", "milka", 12);
	Materie_prima* mat2 = creaza_materie("ciocolata", "milka", 13);
	Materie_prima* mat3 = creaza_materie("faina", "milka", 14);
	assert(sunt_materii_egale(mat1, mat2) == 1);
	assert(sunt_materii_egale(mat1, mat3) == 0);
	distruge_materie(mat1);
	distruge_materie(mat3);
	distruge_materie(mat2);
}
void test_chestii_pt_filtre()
{

	Materie_prima* mat1 = creaza_materie("ciocolata", "poiana", 20);
	Materie_prima* mat2 = creaza_materie("ciocolata", "milka", 2);
	//compara nume
	assert(comp_nume(mat1, mat2) == 0);
	//compara producator
	assert(comp_prod(mat1, mat2) == 1);
	//compara cantitate
	assert(comp_cant(mat1, mat2) == 1);

	distruge_materie(mat1);
	distruge_materie(mat2);
}
void test_materie_filtru()
{
	char criteriu1[30];
	char criteriu2[30];
	strcpy_s(criteriu1, 5, "nume");
	strcpy_s(criteriu2, 10, "cantitate");
	Materie_prima* mat1 = creaza_materie("ciocolata", "poiana", 20);
	assert(functia_filtru(mat1, criteriu1, "c") == 1);
	assert(functia_filtru(mat1, criteriu1, "d") == 0);
	assert(functia_filtru(mat1, criteriu2, "25") == 1);
	assert(functia_filtru(mat1, criteriu2, "a") == 0);
	assert(functia_filtru(mat1, criteriu1, "an") == 0);
	strcpy_s(criteriu2, 10, "portocale");
	assert(functia_filtru(mat1, criteriu2, "25") == 0);
	distruge_materie(mat1);


}
void test_domain()
{
	test_egale();
	test_crud_materie();
	test_validator();
	test_copy_materie();
	test_chestii_pt_filtre();
	test_materie_filtru();
}
//teste lista/repo
void creaza_distruge_lista()
{
	Lista* lista = creaza_lista();
	Materie_prima* mat = creaza_materie("ciocolata", "milka", 12);
	adauga_element(lista, (TElem*)mat);
	assert(lista->lungime == 1);
	distruge_lista(lista, distruge_materie);
}
void test_copy_lista()
{
	Lista* lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("prajitura", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("cacao", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "oreo", 19));
	adauga_element(lista, (TElem*)creaza_materie("unt", "aro", 19));
	adauga_element(lista, (TElem*)creaza_materie("covalact", "de tara", 19));
	assert(lista->lungime == 8);
	Lista* new_list = deep_copy(lista, copiaza_materie);
	assert(new_list->lungime == 8);
	distruge_lista(lista, distruge_materie);
	distruge_lista(new_list, distruge_materie);
}
void test_redimensionare()
{
	Lista* lista = creaza_lista();
	lista->capacitate = 5;
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("prajitura", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("cacao", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "oreo", 19));
	adauga_element(lista, (TElem*)creaza_materie("unt", "aro", 19));
	adauga_element(lista, (TElem*)creaza_materie("covalact", "de tara", 19));
	assert(lista->lungime == 8);
	assert(lista->capacitate == 10);
	distruge_lista(lista,distruge_materie);
}
void test_modifica_sterge()
{
	Lista* lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	assert(strcmp(((Materie_prima*)lista->elems[0])->nume, "ciocolata") == 0);
	assert(strcmp(((Materie_prima*)lista->elems[0])->producator, "milka") == 0);
	assert(((Materie_prima*)lista->elems[0])->cantitate == 19);
	Materie_prima* mat = creaza_materie("ulei", "bunica", 20);
	modifica_element(lista, 0, (TElem*)mat, distruge_materie);
	assert(strcmp(((Materie_prima*)lista->elems[0])->nume, "ulei") == 0);
	assert(strcmp(((Materie_prima*)lista->elems[0])->producator, "bunica") == 0);
	assert(((Materie_prima*)lista->elems[0])->cantitate == 20);
	sterge_element(lista, 0, distruge_materie);
	assert(lista->lungime == 0);
	distruge_lista(lista,distruge_materie);
	lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("prajitura", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("cacao", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "oreo", 19));
	adauga_element(lista, (TElem*)creaza_materie("unt", "aro", 19));
	adauga_element(lista, (TElem*)creaza_materie("covalact", "de tara", 19));
	sterge_element(lista, 0, distruge_materie);
	assert(lista->lungime == 7);
	distruge_lista(lista, distruge_materie);
}
void test_lista()
{
	creaza_distruge_lista();
	test_copy_lista();
	test_redimensionare();
	test_modifica_sterge();
}
//teste service
void test_creaza_valid_adaug()
{
	Lista* lista = creaza_lista();
	char nume[30];
	char prod[30];
	int cantitate;
	strcpy_s(nume, 30, "ciocolata");
	strcpy_s(prod, 30, "milka");
	cantitate = 10;
	int ok = creaza_valid_adaug(lista, nume, prod, cantitate);
	assert(ok == 0);
	strcpy_s(nume, 30, "");
	ok = creaza_valid_adaug(lista, nume, prod, cantitate);
	assert(ok == 1);
	strcpy_s(nume, 30, "ciocolata");
	strcpy_s(prod, 30, "");
	ok = creaza_valid_adaug(lista, nume, prod, cantitate);
	assert(ok == 2);
	strcpy_s(prod, 30, "milka");
	cantitate = 0;
	ok = creaza_valid_adaug(lista, nume, prod, cantitate);
	assert(ok == 3);
	distruge_lista(lista,distruge_materie);
}
void test_exista_materie()
{
	Lista* lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	assert(strcmp(((Materie_prima*)lista->elems[0])->nume, "ciocolata") == 0);
	assert(strcmp(((Materie_prima*)lista->elems[0])->producator, "milka") == 0);
	int exista = exista_materie(lista, "ciocolata", "milka");
	assert(exista == 1);
	exista = exista_materie(lista, "margarina", "delma");
	assert(exista == 0);
	distruge_lista(lista,distruge_materie);
}
void test_get_pozitie()
{
	Lista* lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 19));
	Materie_prima* mat = creaza_materie("ciocolata", "milka", 19);
	int poz = get_pozitie(lista, mat);
	assert(poz == 0);
	distruge_materie(mat);
	Materie_prima* mat2 = creaza_materie("biscuit", "petitebeure", 19);
	poz = get_pozitie(lista, mat2);
	assert(poz == -1);
	distruge_materie(mat2);
	distruge_lista(lista,distruge_materie);
}
void test_sort()
{

	Lista* lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 2));
	adauga_element(lista, (TElem*)creaza_materie("zebra", "milka", 1));
	adauga_element(lista, (TElem*)creaza_materie("prajitura", "milka", 40));
	adauga_element(lista, (TElem*)creaza_materie("cacao", "ana", 35));
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "poiana", 5));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "oreo", 10));
	adauga_element(lista, (TElem*)creaza_materie("unt", "aro", 25));
	adauga_element(lista, (TElem*)creaza_materie("ananas", "de tara", 20));
	//sortari crescatoare
	Lista* sorted = sort(lista, (sort_fct)comp_nume, 0);

	assert(sorted->lungime == lista->lungime);
	assert(strcmp(((Materie_prima*)sorted->elems[0])->nume, "ananas") == 0);
	distruge_lista(sorted,distruge_materie);
	sorted = sort(lista, (sort_fct)comp_prod, 0);
	assert(strcmp(((Materie_prima*)sorted->elems[0])->nume, "cacao") == 0);
	distruge_lista(sorted,distruge_materie);
	sorted = sort(lista, (sort_fct)comp_cant, 0);
	assert(strcmp(((Materie_prima*)sorted->elems[0])->nume, "zebra") == 0);
	assert(((Materie_prima*)sorted->elems[0])->cantitate == 1);
	distruge_lista(sorted,distruge_materie);
	//sortari descrescatoare

	sorted = sort(lista, (sort_fct)comp_nume, 1);
	assert(strcmp(((Materie_prima*)sorted->elems[0])->nume, "zebra") == 0);
	distruge_lista(sorted,distruge_materie);
	sorted = sort(lista, (sort_fct)comp_prod, 1);
	assert(strcmp(((Materie_prima*)sorted->elems[0])->nume, "ciocolata") == 0);
	distruge_lista(sorted,distruge_materie);
	sorted = sort(lista, (sort_fct)comp_cant, 1);
	assert(strcmp(((Materie_prima*)sorted->elems[0])->nume, "prajitura") == 0);
	distruge_lista(sorted,distruge_materie);
	distruge_lista(lista, distruge_materie);
	
}
void test_filter()
{
	Lista* lista = creaza_lista();
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "milka", 2));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "milka", 1));
	adauga_element(lista, (TElem*)creaza_materie("prajitura", "milka", 40));
	adauga_element(lista, (TElem*)creaza_materie("cacao", "milka", 35));
	adauga_element(lista, (TElem*)creaza_materie("ciocolata", "poiana", 5));
	adauga_element(lista, (TElem*)creaza_materie("biscuit", "oreo", 10));
	adauga_element(lista, (TElem*)creaza_materie("unt", "aro", 25));
	adauga_element(lista, (TElem*)creaza_materie("covalact", "de tara", 20));
	Lista* filt = filter(lista, "cantitate", "10", (fil_fct)functia_filtru);
	assert(filt->lungime == 4);
	distruge_lista(filt,distruge_materie);
	Lista* filt1 = filter(lista, "nume", "c", (fil_fct)functia_filtru);
	assert(filt1->lungime == 4);
	distruge_lista(filt1,distruge_materie);
	Lista* filt2 = filter(lista, "nume", "co", (fil_fct)functia_filtru);
	assert(filt2->lungime == 0);
	distruge_lista(filt2,distruge_materie);
	Lista* filt3 = filter(lista, "cantitate", "0", (fil_fct)functia_filtru);
	assert(filt3->lungime == 0);
	distruge_lista(filt3,distruge_materie);
	filt3 = filter(lista, "ionut", "0", (fil_fct)functia_filtru);
	distruge_lista(filt3,distruge_materie);
	Lista* filt4 = filter(lista, "cantitate", "a", (fil_fct)functia_filtru);
	distruge_lista(filt4,distruge_materie);
	Lista* filt5 = filter(lista, "", "", (fil_fct)functia_filtru);
	distruge_lista(filt5,distruge_materie);
	distruge_lista(lista,distruge_materie);
}

void test_service()
{
	test_creaza_valid_adaug();
	test_exista_materie();
	test_get_pozitie();
	test_sort();
	test_filter();
}
void test_all()
{
	test_domain();
	test_lista();
	test_service();
}