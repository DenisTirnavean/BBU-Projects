#include <string>
#include "Domain.h"

Carte::Carte(const std::string titlu,const std::string autor, const std::string gen,const int an)
{
	this->titlu = titlu;
	this->autor = autor;
	this->gen = gen;
	this->an_aparitie = an;
}

std::string Carte::get_titlu() const
{
	return this->titlu;
}
std::string Carte::get_autor() const
{
	return this->autor;
}
std::string Carte::get_gen() const
{
	return this->gen;
}

int Carte::get_an() const noexcept
{
	return this->an_aparitie;
}

void Carte::set_titlu(const std::string new_title)
{
	this->titlu = new_title;
}
void Carte::set_autor(const std::string new_author)
{
	this->autor = new_author;
}
void Carte::set_gen(const std::string new_genre)
{
	this->gen = new_genre;
}
void Carte::set_an(const int new_year) noexcept
{
	this->an_aparitie = new_year;
}
Carte::Carte(const Carte& carte)
{
	this->titlu = carte.get_titlu();
	this->autor = carte.get_autor();
	this->gen = carte.get_gen();
	this->an_aparitie = carte.get_an();
	std::cout << "!!!!!!!!!!!!!!!!!!!!Copy constructor called!!!!!!!!!!!!!!!!!!!!!!!\n";
}
Carte& Carte::operator=(const Carte& ot)
{
	if (this == &ot)
	{
		//std::cout << "Operator de asignare called\n";
		return *this;
	}
	this->titlu = ot.titlu;
	this->autor = ot.autor;
	this->gen = ot.gen;
	this->an_aparitie = ot.an_aparitie;
	//std::cout << "Operator de asignare called\n";
	return *this;

}
bool Carte::operator==(const Carte& ot)
{
	return this->get_titlu() == ot.get_titlu() && this->get_autor()==ot.get_autor();
}

