#include "Exceptii.h"
#include "Cos.h"
using std::ofstream;

void Cos::goleste_cos() noexcept
{
	continut.clear();
	contor = 0;
}

void Cos::add_to_cos(const Carte& carte)
{
	continut.push_back(carte);
	contor++;
}

void Cos::genereaza(int cate, const std::vector<Carte>& lista)
{ 
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, int(lista.size()) - 1);
		while (cate>0)
		{
				add_to_cos(lista[dist(mt)]);
				cate--;	
		}
			
}

void Cos::export_in_fisier(const std::string& file_name)
{
		ofstream fish(file_name);
		for (auto carte : continut)
		{
			fish << carte.get_titlu() << ";" << carte.get_autor() << ";" << carte.get_gen() << ";" << carte.get_an() << "\n";
		}
		fish.close();
	
}

int Cos::cate_carti() const
{
	return contor;
}

vector<Carte>& Cos::get_all_cos() noexcept
{
	return this->continut;
}
