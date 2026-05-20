#include "Service.h"


int compare_name(const Carte& a, const Carte& b)
{
	return a.get_titlu() > b.get_titlu();
}
int compare_author(const Carte& a, const Carte& b)
{
	return a.get_autor() > b.get_autor();
}
int compare_genre(const Carte& a, const Carte& b)
{
	return a.get_gen() > b.get_gen();
}
int compare_year(const Carte& a, const Carte& b)
{
	return a.get_an() > b.get_an();
}

bool right_name(const Carte& a, const string nume)
{
	return a.get_titlu()==nume;
}

bool right_year(const Carte& a, const string an)
{
	return to_string(a.get_an())==an;
}


void Service::creaza_valideaza_adauga(std::string titlu, std::string autor, std::string gen, int an)
{
	this->valid.valideaza_carte(titlu, autor, gen, an);
	Carte carte = Carte(titlu, autor, gen, an);
	const Carte& ncarte = carte;
	this->reposit.adauga(ncarte);
}
int Service::get_repo_size() noexcept{
	return this->reposit.get_size();
}
Carte& Service::get_elem(const int poz)
{
	return reposit.get_carte(poz);
}

int Service::cauta_carte_repo(const string titlu, const string autor)
{
	return this->reposit.cauta_carte(titlu, autor);
}

void Service::sterge_carte_repo(const string titlu, const string autor)
{
	const int poz = reposit.cauta_carte(titlu, autor);
	if (poz != -1)
	{
		Carte& carte = reposit.get_carte(poz);
		this->reposit.sterge_carte(carte);
	}
	else
	{
		throw exception("Carte inexistenta\n");
	}
}

void Service::modifica_carte_repo(const string titlu, const string autor, const Carte& new_carte)
{
	const int poz= reposit.cauta_carte(titlu, autor);
	if (poz != -1) //daca exista cartea modificam
	{
		this->valid.valideaza_carte(new_carte.get_titlu(), new_carte.get_autor(), new_carte.get_gen(), new_carte.get_an());
		this->reposit.modifica_carte(poz,new_carte);
	}
	else // altfel exceptie
	{
		throw exception("Carte inexistenta\n");
	}
}
MyVector<Carte> Service::get_all()
{
	return this->reposit.get_elems();	
}
MyVector<Carte> Service::sort(sort_fct cmp, const int descrescator)
{
	MyVector<Carte> rez = get_all();
	int dim = rez.size();
	for (int i = 0; i < dim-1; i++)
	{
		for(int j =i+1;j<dim;j++)
			if ( (!descrescator && cmp(rez.at(i), rez.at(j)) ) || (descrescator && !cmp(rez.at(i), rez.at(j)) ) )
			{
				auto aux = Carte(rez.at(i).get_titlu(), rez.at(i).get_autor(), rez.at(i).get_gen(), rez.at(i).get_an());
				rez.set(i, rez.at(j));
				rez.set(j, aux);
			}
	}
	return rez;
}

MyVector<Carte> Service::filter(fltr_fct filtru, const string what)
{
	MyVector<Carte> rez;
	for (int i = 0; i < this->get_repo_size(); i++)
		if (filtru(get_elem(i),what))
			rez.push_back(get_elem(i));
	return rez;
		
}
