#pragma once
#include <string>
#include <vector>
#include <iostream>

class Carte
{
private:
	//private stuff
	std::string autor;
	std::string titlu;
	std::string gen;
	int an_aparitie = 0;
public:
	//constructor de carte cu Titlul= titlu(char*), Autorul= autor(char*), An aparitie= an_aparietie(int)
	Carte(const std::string titlu, const std::string autor, const std::string gen, const int an);

	Carte() noexcept = default;
	///getters

	/*Getter pentru titlu
	* returns: string, titlul cartii
	*/
	std::string get_titlu() const;

	/*Getter pentru autor
	* returns: string, autorul cartii
	*/
	std::string get_autor() const;

	/*Getter pentru gen
	* returns: string, genul cartii
	*/
	std::string get_gen() const;

	/*Getter pentru anul aparitiei
	* returns: int, anul aparitiei cartii
	*/
	int get_an() const noexcept;


	///setters

	/*Setter de titlu pentru carte
	* Schimba titlul cartii in new_title
	*/
	void set_titlu(const std::string new_title);

	/*Setter de autor pentru carte
	* Schimba autor cartii in new_author
	*/
	void set_autor(const std::string new_author);


	/*Setter de gen pentru carte
	* Schimba genul cartii in new_genre
	*/
	void set_gen(const std::string new_genre);


	/*Setter de an pentru carte
	* Schimba anul de aparitie al cartii in new_year
	*/
	void set_an(const int new_year) noexcept;

	//operator de copiere
	Carte(const Carte& carte);

	//operatorul de asignare carti :()
	Carte& operator=(const Carte& ot);

	bool operator==(const Carte& ot);

};