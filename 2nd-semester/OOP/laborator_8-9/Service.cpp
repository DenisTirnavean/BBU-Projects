#include "Service.h"


bool compar_nume(const Carte& a, const Carte& b)
{
	return (a.get_titlu() > b.get_titlu());
}
bool compar_autor(const Carte& a, const Carte& b)
{
	return (a.get_autor() > b.get_autor());
}
bool compar_gen(const Carte& a, const Carte& b)
{
	return (a.get_gen() > b.get_gen());
}
bool compar_an(const Carte& a, const Carte& b)
{
	return (a.get_an() > b.get_an());
}

bool right_name(const Carte& a, const string nume)
{
	return a.get_titlu() == nume;
}

bool right_year(const Carte& a, const string an)
{
	return to_string(a.get_an()) == an;
}


void Service::creaza_valideaza_adauga(std::string titlu, std::string autor, std::string gen, int an)
{
	this->valid.valideaza_carte(titlu, autor, gen, an);
	Carte carte = Carte(titlu, autor, gen, an);
	const Carte& ncarte = carte;
	this->reposit->adauga(ncarte);
	UndoAdd* undo = new UndoAdd(this->reposit, ncarte);
	undo_act.push_back((unique_ptr<UndoAdd>)undo);
}
int Service::get_repo_size() noexcept {
	return this->reposit->get_size();
}
Carte& Service::get_elem(const int poz)
{
	return reposit->get_carte(poz);
}

int Service::cauta_carte_repo(const string titlu, const string autor)
{
	return this->reposit->cauta_carte(titlu, autor);
}

void Service::sterge_carte_repo(const string titlu, const string autor)
{
	const int poz = reposit->cauta_carte(titlu, autor);
	if (poz != -1)
	{
		Carte carte = Carte(reposit->get_carte(poz).get_titlu(), reposit->get_carte(poz).get_autor(), reposit->get_carte(poz).get_gen(), reposit->get_carte(poz).get_an());
		this->reposit->sterge_carte(carte);
		undo_act.push_back(make_unique<UndoDelete>(reposit, carte,poz));
	}
	else
	{
		throw ServiceException("Carte inexistenta\n");
	}
}

void Service::modifica_carte_repo(const string titlu, const string autor, const Carte& new_carte)
{
	const int poz = reposit->cauta_carte(titlu, autor);
	if (poz != -1) //daca exista cartea modificam
	{
		this->valid.valideaza_carte(new_carte.get_titlu(), new_carte.get_autor(), new_carte.get_gen(), new_carte.get_an());
		auto carte_cop = reposit->get_carte(poz);
		this->reposit->modifica_carte(poz, new_carte);
		UndoModify* undo = new UndoModify(this->reposit,carte_cop,poz);
		undo_act.push_back((unique_ptr<UndoModify>)undo);
	}
	else // altfel exceptie
	{
		throw ServiceException("Carte inexistenta\n");
	}
}
vector<Carte>& Service::get_all() noexcept
{
	return this->reposit->get_elems();
}
vector<Carte>& Service::sort(sort_fct cmp, const bool descrescator)
{
	vector<Carte>& rez = get_all();
	if(descrescator == true)
		std::sort(rez.begin(), rez.end(), cmp);
	else {
		std::sort(rez.begin(), rez.end(), [cmp](const Carte& a, const Carte& b) noexcept{return ( cmp(b, a)); });
	}
	return rez;
}

vector<Carte> Service::filter(fltr_fct filtru, const string what)
{
	vector<Carte> rez;
	copy_if(this->get_all().begin(), get_all().end(), back_inserter(rez), [=](const Carte& carticica) {
		return filtru(carticica, what);
		});
	return rez;
	/*
	for (int i = 0; i < this->get_repo_size(); i++)
		if (filtru(get_elem(i), what))
			rez.push_back(get_elem(i));
	return rez;
	*/
}


int Service::how_many_basket() const
{
	return this->cosulet.cate_carti();
}

void Service::generate(const int cate)
{
	this->cosulet.genereaza(cate,this->get_all());
}

void Service::adauga_in_cos(const string& titlu,const string& autor)
{
	const bool ok =this->reposit->cauta(titlu, autor);
	if (ok)
	{
		cosulet.add_to_cos(this->get_elem(cauta_carte_repo(titlu,autor)));
	}
	else {
		throw BasketException("Carte inexistenta!\n");
	}

}

void Service::empty_cos() noexcept
{
	cosulet.goleste_cos();
}

void Service::save_cos(const string& file_name)
{
	cosulet.export_in_fisier(file_name);
}

vector<Carte>& Service::get_cos() noexcept
{
	return this->cosulet.get_all_cos();
}

void Service::serv_undo()
{
	if (undo_act.size() == 0)
	{
		throw ServiceException("Undo invalid\n");}
	else {
		unique_ptr<ActUndo> act = move(undo_act.back());
		act->doUndo();
		undo_act.pop_back();
	}
}
