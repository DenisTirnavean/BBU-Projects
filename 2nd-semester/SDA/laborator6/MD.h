#pragma once
#include<vector>
#include <map>;
#include<utility>

#define NIL -1
#define deleted 2
#define unused 0
#define used 1

#define NULL_TVALOARE INT_MAX
using namespace std;

typedef int TCheie;
typedef int TValoare;



typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;


class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */

	typedef struct ElemMD {
		TCheie cheie;
		vector<TValoare> valori;
		int ocupat;
	};
	int capacitate; //cate elemente incap
	int dimensiune; //cate elemente(chei distincte) am - pt a stii cand redimensionez
	int dim_perechi; //cate perechi cheie-valoare am total   - pt a eficientiza operatia dim()
	ElemMD* tabela; //TD

	//functii de dispersie
	int hashCode(TCheie c) const {
		return abs(c);
	}

	int d1(const TCheie c) const;

	int d2(const TCheie c) const;

	int d(const TCheie c,const int i) const;


public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	//*Complexitati:
	//caz favorabil: Theta(1), adaugare pe prima pozitie verificata in secventa
	//caz defavorabil: O(capacitate), redispersare, redimensionare, toate cataclismele, caz rar
	//caz mediu: Theta(1) amortizat
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	//*Complexitati:
	//caz favorabil: Theta(1), gasim pe prima pozitie verificata in secventa
	//caz defavorabil: O(capacitate), parcurg toata tabela
	//caz mediu: Theta(1) amortizat
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	//*Complexitati:
	//caz favorabil: Theta(1), gasesti elementul de sters pe prima pozitie verificata
	//caz defavorabil: O(capacitate), acelasi ca la cautare
	//caz mediu: Theta(1) amortizat
	//caz general: O(k), k - numarul de valori din vectorul cheii c
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD
	// theta(1)
	int dim() const;

	//verifica daca MultiDictionarul e vid
	// theta(1)
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// destructorul MultiDictionarului	
	~MD();

	//functie care returneaza cea mai frecventa valoare
	//daca dictionarul este vid returneaza NULL_TVALOARE
	// daca exista mai multe valori cu frecventa maxima, returneaza una dintre ele
	//complexitate Theta(capacitate), iteram prin toate cheile multidictionarului
	TValoare ceaMaiFrecventaValoare() const;

};

