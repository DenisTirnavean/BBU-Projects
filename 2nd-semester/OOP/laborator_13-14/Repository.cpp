#include "Repository.h"
#include <iostream>
#include <sstream>
#include <algorithm>


void Repository::insert(const Carte& carte, const int poz)
{
	this->lista.insert(lista.begin() + poz, carte);
}

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
		throw RepositoryException("Carte deja existenta\n");
}
int Repository::get_size() const noexcept
{
	return (int)this->lista.size();
}

int Repository::cauta_carte(const string titlu, const string autor)
{
	/*
	int ok = -1;

	const int length = this->get_size();
	for (int i = 0; i < length; i++)
		if (get_carte(i).get_titlu() == titlu && get_carte(i).get_autor() == autor)
			ok = i;
	return ok;
	*/
	auto it = find_if(lista.begin(), lista.end(), [=](const Carte& cartulica) {
		return cartulica.get_titlu() == titlu && cartulica.get_autor() == autor;
		});
	if (it < lista.end())
	{
		return (int)(it - lista.begin());
	}

	return -1;


}

void Repository::sterge_carte(Carte& carte)
{
	int const ok = cauta_carte(carte.get_titlu(), carte.get_autor());
	if (ok == -1)
		throw RepositoryException("Carte inexistenta\n");
	else
	{
		this->lista.erase(lista.begin() + ok);
	}
}

void Repository::modifica_carte(const int poz, const Carte& new_carte)
{
	const int ok = cauta_carte(new_carte.get_titlu(), new_carte.get_autor());
	Carte& carte = get_carte(poz);
	if (ok != -1)
	{
		if (carte.get_gen() == new_carte.get_gen() && carte.get_an() == new_carte.get_an())
			throw RepositoryException("Carte deja existenta\n");
	}
	carte.set_titlu(new_carte.get_titlu());
	carte.set_autor(new_carte.get_autor());
	carte.set_gen(new_carte.get_gen());
	carte.set_an(new_carte.get_an());

}

bool Repository::cauta(const string& titlu, const string& autor) const {
	auto it = find_if(lista.begin(), lista.end(), [=](const Carte& cartulica) {
		return cartulica.get_titlu() == titlu && cartulica.get_autor() == autor;
		});
	return it < lista.end();
}

vector<Carte>& Repository::get_elems() noexcept
{
	return this->lista;
}

void Repository_file::save_to_file()
{
	ofstream fout(this->file_name);
	for (auto& el : Repository::get_elems())
	{
		fout << el.get_titlu() << ";" << el.get_autor() << ";" << el.get_gen() << ";" << el.get_an() << "\n";
	}
	fout.close();
}
void Repository_file::load_from_file() {
	ifstream fin(this->file_name);
	string str;
	while (getline(fin, str)) {
		stringstream ss(str);

		string word;
		vector<string> arg;
		while (getline(ss, word, ';')) {
			arg.push_back(word);
		}
		int nr = stoi(arg[3]);
		Repository::adauga(Carte(arg[0], arg[1], arg[2], nr));
	}
	fin.close();

}

void Repository_map::toss_the_dice()
{
	float random = ((float)rand()) / (float)RAND_MAX; //genereaza un float random intre 0 si 1
	if (random < reliability)
	{
		throw RepositoryException("\n:) guess what\n");
	}

}

void Repository_map::adauga(const Carte& carte)
{
	toss_the_dice();
	auto poz = cauta_carte(carte.get_titlu(), carte.get_autor());
	if (poz != -1)
	{
		throw RepositoryException("Carte deja existenta\n");
	}
	//daca nu a crapat
	this->dict.insert(make_pair((int)dict.size(), carte));
	this->continut.push_back(carte);
}

void Repository_map::modifica_carte(const int poz, const Carte& new_carte)
{
	toss_the_dice();
	auto position = cauta_carte(new_carte.get_titlu(), new_carte.get_autor());
	if (position != -1)
	{
		throw RepositoryException("Carte deja existenta\n");
	}
	for (auto& it : dict) {
		if (it.first == poz) {
			dict.erase(poz);
			dict.insert(make_pair(poz, new_carte));
			break;
		}
	}

	Carte& carte = continut.at(poz);
	carte.set_titlu(new_carte.get_titlu());
	carte.set_autor(new_carte.get_autor());
	carte.set_gen(new_carte.get_gen());
	carte.set_an(new_carte.get_an());
}

void Repository_map::sterge_carte(Carte& carte)
{
	toss_the_dice();
	int poz = cauta_carte(carte.get_titlu(), carte.get_autor());
	if (poz == -1)
	{
		throw RepositoryException("Carte inexistenta\n");
	}
	else {
		dict.erase(poz);
		continut.erase(continut.begin() + poz);
	}
}

vector<Carte>& Repository_map::get_elems()
{
	return continut;
}

int Repository_map::get_size() const noexcept
{
	return (int)dict.size();
}

bool Repository_map::cauta(const string& titlu, const string& autor) const
{

	const auto it = std::find_if(dict.begin(), dict.end(), [titlu, autor](const auto& elem) {
		return elem.second.get_titlu() == titlu && elem.second.get_autor() == autor;
		});
	if (it != dict.end())
		return true;
	return false;
	/*
	for (auto& el : dict) {
		if (el.second.get_titlu() == titlu && el.second.get_autor() == autor)
		{
			return true;
		}
	}
	return false;
	*/
}

void Repository_map::insert(const Carte& carte, const int poz)
{
	this->dict.insert(make_pair(poz, carte));
	this->continut.insert(continut.begin() + poz, carte);
}

int Repository_map::cauta_carte(const string titlu, const string autor)
{
	auto ok = cauta(titlu, autor);
	if (ok)
		for (auto& el : dict) {
			if (el.second.get_titlu() == titlu && el.second.get_autor() == autor)
			{
				return el.first;
			}
		}
	return -1;

}

Carte& Repository_map::get_carte(int pozitie)
{
	return dict.at(pozitie);
}
