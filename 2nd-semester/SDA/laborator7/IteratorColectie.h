#pragma once
#include "Colectie.h"
#include <exception>

using namespace std;

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;

private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	//Theta(h), operatia prim() din constructorul iteratorului=>situarea curentului pe minimul din arbore
	IteratorColectie(const Colectie& c);

	//contine o referinta catre containerul pe care il itereaza
	const Colectie& col;

	/*aici reprezentarea*/

	//iteratorul face o parcurgere in inordine (sRd) ,avem nevoie de o stiva
	int* stiva;
	int top;
	int capacitate;
	int curent;

 
public:

	//reseteaza pozitia iteratorului la inceputul containerului
	//Theta(h) - parcurge ramura stanga pana la capat
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	//O(h)
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	//Theta(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	//Theta(1)
	TElem element() const;


};
