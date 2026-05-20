
#include "Coada.h"
#include <exception>
#include <iostream>

using namespace std;


Coada::Coada(const int capacitate) {
	if (capacitate <= 0)
		throw exception("Capacitate invalida\n");
	cp = capacitate+1;
	this->fata = 0;
	this->spate = 0;
	elems = new TElem[cp];
}
/*
* pseudocod:
* Coada:
*	cp: Intreg
*	fata, spate: Intreg
*	e: TElement[1..cp]
* 
* {se creeaza o coada cu capacitatea fixa capacitate}
* {pre: capacitate: Intreg > 0}
* {post: c:Coada }
* @arunca exceptie daca capacitate<=0
* subalgoritm Coada(c,capacitate) este {TETA(1)}
*		daca(capacitate <= 0) atunci
*			@arunca_exceptie
*		sf_daca
*		c.cp<-capacitate
*		c.fata<-0
*		c.spate<-0
* sf_subalgoritm
*		
*/


void Coada::redimensionare() {
	TElem* aux = new TElem[cp * 2];
	int new_cap = cp * 2;
	if (fata > spate) //cazul ala special fmm
	{
		for (int i = fata; i < cp; i++)
			aux[i + cp] = elems[i];
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

	if (estePlina())	throw exception("Coada este plina\n");
	elems[spate] = elem;
	spate++;
}
/*
* pseudocod:
* {adauga element in coada}
* {pre: c:Coada , elem: TElem}
* {post: c'<-c+{elem}
* @arunca exceptie daca estePlina(c) = TRUE
* subalgoritm adauga(c,elem) este {TETA(1)}
*		daca estePlina(c) = TRUE atunci
*				@arunca_exceptie
*		sf_daca
*		c.elems[spate] <- elem
*		spate<-spate + 1
* sf_subalgoritm
*/


//arunca exceptie daca coada e vida
TElem Coada::element() const {
	if (vida())
	{
		throw exception("lmao coada e vidra!!\n");
		return -1;
	}
	else return elems[fata];
}

TElem Coada::sterge() {
	if (vida())
	{
		throw exception("lmao coada e vidra!!\n");
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
	delete this->elems;
	this->cp = 0;
	this->fata = 0;
	this->spate = 0;
}


bool Coada::estePlina()
{
	if (fata == spate + 1)
	{
		return true;
	}
	else if (fata == 0 && spate == cp - 1)
	{
		return true;
	}
	else return false;
}
/*
* pseudocod:
* {verifica daca coada este plina}
* {pre: c:Coada}
* {post: estePlina = TRUE, daca c este plina
*		 estePlina = FALSE, altfel}
* subalgoritm estePlina(c) este {TETA(1)}
*		daca(c.fata =c.spate + 1) atunci
*			estePlina<-TRUE
*		altfel
*			daca(c.fata= 0 si c.spate = c.cp - 1) atunci
*				estePlina<-TRUE
*			altfel estePlina<-FALSE
*			sf_daca
*		sf_daca
* sf_subalgoritm
*/