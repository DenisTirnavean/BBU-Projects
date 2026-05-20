
#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>


using namespace std;


int MD::d1(const TCheie c) const
{
	return hashCode(c)%capacitate;

}

int MD::d2(const TCheie c) const
{
	return 1 + hashCode(c) % (capacitate - 2);
}

int MD::d(const TCheie c, const int i) const
{
	return (d1(c) + i * d2(c)) % capacitate;
}

MD::MD() {
	this->dimensiune = 0;
	this->capacitate = 175740;
	this->dim_perechi = 0;
	this->tabela = new ElemMD[capacitate];
	for (int i = 0; i < capacitate; i++) {
		tabela[i].cheie = NIL;
		tabela[i].ocupat = unused;
	}
}


void MD::adauga(TCheie c, TValoare v) {

	int i = 0;
	bool gasit = false;
	do {
		int j = d(c, i);
		if (tabela[j].cheie == c && tabela[j].ocupat == used) {
			tabela[j].valori.push_back(v);
			gasit = true;
			break;
		}
		else if (tabela[j].ocupat != used && !gasit) {
			tabela[j].cheie = c;
			tabela[j].valori.push_back(v);
			tabela[j].ocupat = used;
			dimensiune++;
			gasit = true;
			break;
		}
		i++;
	} while (i < capacitate && !gasit);

	dim_perechi++;
	
}


bool MD::sterge(TCheie c, TValoare v) {
	
	auto rez = cauta(c);
	//cazul in care nu avem cheia in dictionar
	if (rez.size() == 0)
	{
		return false;
	}
	int i = 0;
	bool gasit = false;


	int index = d(c, i);
	do {
		int j = d(c, i);
		if (tabela[j].ocupat == unused)
			break;
		if (tabela[j].cheie == c && tabela[j].ocupat == used)
		{
			gasit = true;
			//cautam valoarea in vectorul de valori
			auto it = find_if(tabela[j].valori.begin(), tabela[j].valori.end(), [v](const TValoare val) {
				return val == v;
			});

			if (it >= tabela[j].valori.end()) //nu avem valoarea v in vectorul de valori
			{
				return false;
			}
			else
			{
				//cazul pentru mai multe valori asociate cheii, fara deplasari de date, all good, relax, chill
				if (rez.size() != 1)
				{
					//stergem valoarea v din vectorul de valori al cheii
					tabela[j].valori.erase(it);
				}
				//marcam locatia ca fiind deleted
				else {
					//pasul 2
					tabela[j].ocupat = deleted;
					tabela[j].cheie = NIL;
					tabela[j].valori.erase(tabela[j].valori.begin(), tabela[j].valori.end());
					dimensiune--;
				}
			}
			dim_perechi--;
			break;
		}
		i++;
	} while (i < capacitate && !gasit);
	return true;

}


vector<TValoare> MD::cauta(TCheie c) const {
	
	//parcurg secventa de verificare pana ce gasesc ce ma intereseaza, daca nu am gasit, ghinion
	bool gasit = false;
	vector<TValoare> valori{};
	int i = 0;
	do {
		int j = d(c, i);
		if (tabela[j].ocupat == unused)
			break;
		if (tabela[j].cheie == c && tabela[j].ocupat==used)
		{
			gasit = true;
			valori= tabela[j].valori;
			break;
		}
		i++;
	} while (i < capacitate && !gasit);
	return valori;
}


int MD::dim() const {
	
	return dim_perechi;
}


bool MD::vid() const {
	
	return dimensiune == 0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	
	delete[]tabela;
}

TValoare MD::ceaMaiFrecventaValoare() const {
	if (dim_perechi == 0) {
		return NULL_TVALOARE;
	}

	map<TValoare, int> frecventa;
	TValoare v_max_frecventa = NULL_TVALOARE;
	int max_frecventa = 0;

	for (int i = 0; i < capacitate; i++) {
		if (tabela[i].ocupat == used) {
			for (auto valoare : tabela[i].valori) {
				frecventa[valoare]++;
				if (frecventa[valoare] > max_frecventa) {
					max_frecventa = frecventa[valoare];
					v_max_frecventa = valoare;
				}
			}
		}
	}
	return v_max_frecventa;
}



