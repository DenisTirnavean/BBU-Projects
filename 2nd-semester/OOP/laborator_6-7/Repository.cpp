#include "Repository.h"

Carte& Repository::get_carte(const int pozitie)
{
	return this->lista.at(pozitie);
}
void Repository::adauga(const Carte& carte)
{
	const int ok = cauta_carte(carte.get_titlu(), carte.get_autor());
	if (ok == -1)
		this->lista.push_back(carte);
	else
		throw exception("Carte deja existenta\n");
}
int Repository::get_size() const noexcept
{
	return (int)this->lista.size();
}

int Repository::cauta_carte(const string titlu, const string autor)
{
	int ok = -1;
	const int length = this->get_size();
	for (int i = 0; i < length; i++)
		if (get_carte(i).get_titlu() == titlu && get_carte(i).get_autor() == autor)
			ok = i;
	return ok;
}

void Repository::sterge_carte(Carte& carte)
{
	int const ok = cauta_carte(carte.get_titlu(), carte.get_autor());
	if (ok == -1)
		throw exception("Carte inexistenta\n");
	else
	{
		this->lista.erase(ok);
	}
}

void Repository::modifica_carte(const int poz,const Carte& new_carte)
{
	const int ok = cauta_carte(new_carte.get_titlu(), new_carte.get_autor());
	if (ok != -1)
	{
		throw exception("Carte deja existenta\n");}
	else
	{
		Carte& carte = get_carte(poz);
		carte.set_titlu(new_carte.get_titlu());
		carte.set_autor(new_carte.get_autor());
		carte.set_gen(new_carte.get_gen());
		carte.set_an(new_carte.get_an());
	}
}

MyVector<Carte> Repository::get_elems()
{
	return this->lista;
}