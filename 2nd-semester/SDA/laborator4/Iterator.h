#pragma once

#include "LO.h"

class Iterator {
	friend class LO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	const LO& lo;

	/* aici e reprezentarea  specifica a iteratorului */
	int curent;
public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElement element() const;

	//elimina si returneaza elementul curent referit de iterator
	//dupa eliminare iteratorul este mutat pe urmatorul element din lista, sau iterator invalid daca nu mai exista elemente
	//arunca exceptie daca iteratorul este invalid
	TElement elimina();
	
};


