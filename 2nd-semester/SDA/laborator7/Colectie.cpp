
#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	
	return e1<=e2;
}


Colectie::Colectie() {
	capacitate = 67890;
	noduri = new Nod[capacitate];
	urmatorLiber = new int[capacitate];
	for (int i = 0; i < capacitate - 1; ++i)
		urmatorLiber[i] = i + 1;
	urmatorLiber[capacitate - 1] = NIL;
	primLiber = 0;
	dimensiune = 0;

	radacina = NIL;
}


void Colectie::adauga(TElem e) {
	adaugaRec(radacina, e);
}


bool Colectie::sterge(TElem e) {
	
	bool rezultat = stergeIterativ(e);
	if (rezultat)
		--dimensiune;
	return rezultat;
}


bool Colectie::cauta(TElem elem) const {
	return cautaRec(radacina, elem);
}


int Colectie::nrAparitii(TElem elem) const {
	
	return nrAparitiiRec(radacina, elem);
}



int Colectie::dim() const {
	return dimensiune;
}


bool Colectie::vida() const {
	
	return dimensiune == 0;
}


IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] noduri;
	delete[] urmatorLiber;
}

void Colectie::adaugaRec(int& nodCurent, TElem e)
{
	if (nodCurent == NIL) {
		int i = aloca();
		noduri[i] = { e, NIL, NIL };
		nodCurent = i;
		dimensiune++;
	}
	else if (e == noduri[nodCurent].e) {
		adaugaRec(noduri[nodCurent].dreapta, e);
	}
	else if (rel(e, noduri[nodCurent].e)) {
		adaugaRec(noduri[nodCurent].stanga, e);
	}
	else {
		adaugaRec(noduri[nodCurent].dreapta, e);
	}

}

bool Colectie::cautaRec(int nodCurent, TElem e) const {
	if (nodCurent == NIL)
		return false;
	if (noduri[nodCurent].e == e)
		return true;
	else if (rel(e, noduri[nodCurent].e) && e != noduri[nodCurent].e)
		return cautaRec(noduri[nodCurent].stanga, e);
	else
		return cautaRec(noduri[nodCurent].dreapta, e);
}


int Colectie::nrAparitiiRec(int nodCurent, TElem e) const
{
	if (nodCurent == NIL)
		return 0;
	if (noduri[nodCurent].e == e)
		return 1 + nrAparitiiRec(noduri[nodCurent].stanga, e) + nrAparitiiRec(noduri[nodCurent].dreapta, e);
	if (rel(e, noduri[nodCurent].e))
		return nrAparitiiRec(noduri[nodCurent].stanga, e);
	else
		return nrAparitiiRec(noduri[nodCurent].dreapta, e);
}

bool Colectie::stergeRec(int& nodCurent, TElem e)
{
	if (nodCurent == NIL)
		return false;
	if (noduri[nodCurent].e == e) {
		if (noduri[nodCurent].stanga == NIL && noduri[nodCurent].dreapta == NIL) {
			dealoca(nodCurent);
			nodCurent = NIL;
		}
		else if (noduri[nodCurent].stanga == NIL) {
			int aux = nodCurent;
			nodCurent = noduri[nodCurent].dreapta;
			dealoca(aux);
		}
		else if (noduri[nodCurent].dreapta == NIL) {
			int aux = nodCurent;
			nodCurent = noduri[nodCurent].stanga;
			dealoca(aux);
		}
		else {
			int succ = noduri[nodCurent].dreapta;
			while (noduri[succ].stanga != NIL)
				succ = noduri[succ].stanga;
			noduri[nodCurent].e = noduri[succ].e;
			stergeRec(noduri[nodCurent].dreapta, noduri[succ].e);
		}
		return true;
	}
	else if (rel(e, noduri[nodCurent].e)) {
		return stergeRec(noduri[nodCurent].stanga, e);
	}
	else {
		return stergeRec(noduri[nodCurent].dreapta, e);
	}
}


void Colectie::redimensionare() {
	//redimensionare pentru tabela de elemente efective, lista de locuri libere si actualizare primLiber
	auto capacitateNoua = capacitate * 2;
	auto noduriNoi = new Nod[capacitateNoua];
	auto urmatorLiberNou = new int[capacitateNoua];

	//copiem elementele in ordine
	for (int i = 0; i < capacitate; i++)
		noduriNoi[i] = noduri[i];

	//copiem legaturile pt liber
	for (int i = 0; i < capacitate; i++)
		urmatorLiberNou[i] = urmatorLiber[i];
	//continuam inlantuirea
	for (int i = capacitate; i < capacitateNoua; i++)
		urmatorLiberNou[i] = i + 1;
	urmatorLiberNou[capacitateNoua - 1] = NIL;
	if(primLiber==NIL)
		primLiber = capacitate;

	else {
		int p = primLiber;
		while (urmatorLiberNou[p] != NIL) {
			p = urmatorLiberNou[p];
		}
		urmatorLiberNou[p] = capacitate;
	}
	delete[] urmatorLiber;
	delete[] noduri;
	capacitate = capacitateNoua;
	this->urmatorLiber = urmatorLiberNou;
	this->noduri = noduriNoi;
}


int Colectie::aloca()
{
	if (primLiber == NIL) {
		redimensionare();
	}
	int index = primLiber;
	primLiber = urmatorLiber[primLiber];
	return index;
}

void Colectie::dealoca(int index)
{
	urmatorLiber[index] = primLiber;
	primLiber = index;
}
bool Colectie::stergeIterativ(TElem e) {
	int* pnod = &radacina; 
	int nodCurent = radacina;
	int parinte = NIL;     

	//cautare nod
	while (nodCurent != NIL && noduri[nodCurent].e != e) {
		parinte = nodCurent;
		//pe ramura stanga
		if (rel(e, noduri[nodCurent].e)) {
			pnod = &noduri[nodCurent].stanga;
			nodCurent = noduri[nodCurent].stanga;
		}
		else {
			//pe ramura dreapta
			pnod = &noduri[nodCurent].dreapta;
			nodCurent = noduri[nodCurent].dreapta;
		}
	}
	// nu exista nodul
	if (nodCurent == NIL) 
		return false;



	//daca nu are fiu stang nici drept, frunza, stergem lejer
	if (noduri[nodCurent].stanga == NIL && noduri[nodCurent].dreapta == NIL) {
		dealoca(nodCurent);
		*pnod = NIL;
	}
	//daca are un fiu drept,nu are stanga, legam stangul la tatal nodului
	else if (noduri[nodCurent].dreapta == NIL) {
		int copil = noduri[nodCurent].stanga;
		dealoca(nodCurent);
		*pnod = copil;
	}
	//daca are fiu stang,nu are drepta, legam dreptul la tata
	else if (noduri[nodCurent].stanga == NIL) {
		int copil = noduri[nodCurent].dreapta;
		dealoca(nodCurent);
		*pnod = copil;
	}

	else {
		//cazul nasol, stergem ceva cu fiu stang+drept
		int succParent = nodCurent;
		int succ = noduri[nodCurent].dreapta;

		//caut cel mai mic nod din subarborele stang
		while (noduri[succ].stanga != NIL) {
			succParent = succ;
			succ = noduri[succ].stanga;
		}


		noduri[nodCurent].e = noduri[succ].e;

		if (noduri[succ].dreapta != NIL) {
			if (succParent == nodCurent)
				noduri[succParent].dreapta = noduri[succ].dreapta;
			else
				noduri[succParent].stanga = noduri[succ].dreapta;
		}
		else {
			if (succParent == nodCurent)
				noduri[succParent].dreapta = NIL;
			else
				noduri[succParent].stanga = NIL;
		}
		dealoca(succ);
	}

	return true;
}

int Colectie::diferenta() const
{
	int diferenta=-1;
	auto curent = this->radacina;
	if (curent == -1)
		return diferenta;
	//calculam maximul, cea mai din dreapta valoare
	while (this->noduri[curent].dreapta!=-1)
	{
		curent = this->noduri[curent].dreapta;
	}
	int maxim = this->noduri[curent].e;
	//calculam minimul, cea mai din drepta valoare
	curent = this->radacina;
	while (this->noduri[curent].stanga != -1) {
		curent = this->noduri[curent].stanga;
	}
	int minim = this->noduri[curent].e;
	diferenta = maxim - minim;
	return diferenta;
}
