#include "Validator.h"
#include <exception>


void Validator::valideaza_carte(std::string titlu, std::string autor, std::string gen, int an)
{
	std::string errori = "";
	if (titlu == "")
		errori += "Titlu invalid\n";
	if (autor == "")
		errori += "Autor invalid\n";
	if (gen == "")
		errori += "Gen invalid\n";
	if (an < 0 || an>2025)
		errori += "An invalid\n";
	if (errori.size() != 0)
		throw std::exception(errori.c_str());
		
	
}
