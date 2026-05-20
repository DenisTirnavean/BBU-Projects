#pragma once
#include <string>
#include "Exceptii.h"

class Validator
{
	/*Functia de validare carte
	* returns: -
	* raises: Erori cu mesaje specifice:
	"Titlu invalid\n" - daca titlu este string vid;
	"Autor invalid\n" - daca autor este sir vid;
	"Gen invalid\n" daca gen este sir vid;
	"An invalid\n" daca anul este intreg negativ sau nu exista inca(>=2026)
	*/
public:
	void valideaza_carte(std::string titlu, std::string autor, std::string gen, int an);

};
