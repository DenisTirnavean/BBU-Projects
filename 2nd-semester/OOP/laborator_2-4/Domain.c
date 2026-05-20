#include "Domain.h"
#include <string.h>
#include <stdlib.h>

Materie_prima* creaza_materie(char* nume, char* prod, int cantitate)
{
	Materie_prima* mat = malloc(sizeof(Materie_prima));
	int numar_chr_nume, numar_chr_prod;
	numar_chr_nume = (int)strlen(nume) + 1;
	if (mat != NULL)
	{
		mat->nume = malloc(numar_chr_nume * sizeof(char));
		if (mat->nume != '\0')
		{
			strcpy_s(mat->nume, numar_chr_nume, nume);
		}
		numar_chr_prod = (int)strlen(prod) + 1;
		mat->producator = malloc(numar_chr_prod * sizeof(char));
		if (mat->producator != '\0')
		{
			strcpy_s(mat->producator, numar_chr_prod, prod);
		}

		mat->cantitate = cantitate;
	}
	return mat;
}

void distruge_materie(Materie_prima* mat)
{
	free(mat->nume);
	free(mat->producator);
	free(mat);

}
int sunt_materii_egale(Materie_prima* mat1, Materie_prima* mat2)
{
	if (strcmp(mat1->nume, mat2->nume) == 0 && strcmp(mat1->producator, mat2->producator) == 0) {
		return 1;
	}
	return 0;
}
int valideaza_materie(char* nume, char* prod, int cantitate) {
	if (strlen(nume) <= 0)
		return 1;
	if (strlen(prod) <= 0)
		return 2;
	if (cantitate <= 0)
		return 3;
	return 0;
}

int comp_prod(Materie_prima* a, Materie_prima* b) {
	return strcmp(a->producator, b->producator) > 0;
}

int functia_filtru(Materie_prima* materie, char* criteriu, char* val) {
	if (strcmp(criteriu, "nume") == 0) {
		if (strlen(val) > 1) return 0;
		return materie->nume[0] == val[0];}
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
		return materie->cantitate <= nr;
	}
	return 0;
}

Materie_prima* copiaza_materie(Materie_prima* a) {
	return creaza_materie(a->nume, a->producator, a->cantitate);
}

int comp_nume(Materie_prima* a, Materie_prima* b) {
	return strcmp(a->nume, b->nume) > 0;
}


int comp_cant(Materie_prima* a, Materie_prima* b) {
	return a->cantitate > b->cantitate;
}
