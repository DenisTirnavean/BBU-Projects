
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;


Coada::Coada() {
	/* de adaugat */
	cp = 50;
	this->fata = 0;
	this->spate = 0;
	elems = new TElem[cp];
}

void Coada::redimensionare() {
	TElem* aux = new TElem[cp * 2];
	int new_cap = cp * 2;
	if (fata > spate) //cazul ala special fmm
	{
		for (int i = fata; i < cp; i++)
			aux[i+cp] = elems[i];
		fata += cp;
	}
	if (fata < spate) //cazul normal
	{
		for (int i = 0; i < cp; i++)
			aux[i] = elems[i];
	}
	cp = new_cap;
	delete elems;
	elems = aux;
}

void Coada::adauga(TElem elem) {
	/* de adaugat */
	if (fata == spate + 1)	redimensionare();
	if (fata == 0 && spate == cp - 1) redimensionare();

	elems[spate] = elem;
	spate++;
}

//arunca exceptie daca coada e vida
TElem Coada::element() const {
	if (vida())
	{
		throw exception("vida!!\n");
		return -1;
	}
	else return elems[fata];
}

TElem Coada::sterge() {
	if (vida())
	{
		throw exception("vida!!\n");
		return -1;
	}
	else
	{
		TElem primu = elems[fata];
		if (fata == cp - 1) fata = 0;
		else fata++;
		return primu;
	}
}

bool Coada::vida() const {
	if (fata == spate)
		return true;
	else return false;
}


Coada::~Coada() {
	/* de adaugat */
	delete this->elems;
	this->cp = 0;
	this->fata = 0;
	this->spate=0;
}

