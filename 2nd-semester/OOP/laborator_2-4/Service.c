#include "Lista.h"
#include "Service.h"
#include "string.h"
int creaza_valid_adaug(Lista* lista, char* nume, char* prod, int cantitate) {
	int ok = 0;
	ok = valideaza_materie(nume, prod, cantitate);
	if (ok == 0)
		adauga_element(lista, (TElem*)creaza_materie(nume, prod, cantitate));
	return ok;
}

int exista_materie(Lista* lista, char* nume, char* prod)
{
	int ok = 0;
	Materie_prima* mat;
	for (int i = 0; i < lista->lungime; i++)
	{
		mat = creaza_materie(((Materie_prima*)(lista->elems[i]))->nume, ((Materie_prima*)(lista->elems[i]))->producator, ((Materie_prima*)(lista->elems[i]))->cantitate);
		if (strcmp(mat->nume, nume) == 0 && strcmp(mat->producator, prod) == 0)
			ok = 1;
		distruge_materie(mat);
	}
	
	return ok;
}

int get_pozitie(Lista* lista, Materie_prima* mat)
{
	for (int i = 0; i < lista->lungime; i++)
		if (sunt_materii_egale(mat, (Materie_prima*)lista->elems[i]))
			return i;
	return -1;
}

Lista* filter(Lista* lista, char* fil_crt, char* fil_val, fil_fct fil) {
	Lista* filt_list = creaza_lista();
	if (strlen(fil_crt) <= 0 || strlen(fil_val) <= 0)
		return filt_list;

	for (int i = 0; i < lista->lungime; i++) {
		if (fil(lista->elems[i], fil_crt, fil_val)) {
			creaza_valid_adaug(filt_list, ((Materie_prima*)(lista->elems[i]))->nume, ((Materie_prima*)(lista->elems[i]))->producator, ((Materie_prima*)(lista->elems[i]))->cantitate);
		}
	}
	return filt_list;
}

Lista* sort(Lista* lista, sort_fct cmp, int desc) {
	Lista* sorted = deep_copy(lista,copiaza_materie);
	for (int i = 0; i < sorted->lungime; i++) {
		for (int j = i + 1; j < sorted->lungime; ++j) {
			if (desc - cmp(sorted->elems[i], sorted->elems[j])) {
				TElem* aux = sorted->elems[i];
				sorted->elems[i] = sorted->elems[j];
				sorted->elems[j] = aux;
			}
		}
	}
	return sorted;
}