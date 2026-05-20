#include "UI.h"

void Consola::add()
{
	cout << "===========================================\n";
	cout << "||              ADAUGARE		||\n";
	cout << "===========================================\n\n";
	int an;
	string titlu, autor, gen, an_str;

	cout << "Titlul cartii: ";
	getline(cin, titlu);
	cout << "Autorul cartii: ";
	getline(cin, autor);
	cout << "Genul cartii: ";
	getline(cin, gen);
	cout << "Anul aparitiei: ";
	cin >> an_str;
	cin.get();
	try {
		an = stoi(an_str);
	}
	catch (exception)
	{
		cout << "\nAi vrut sa strici aplicatia :(\n\n";
		return;
	}

	this->service.creaza_valideaza_adauga(titlu, autor, gen, an);
	cout << "\nCarte adaugata cu succes!!!\n\n";
}
void Consola::print_elem(const Carte& carte) const
{
	cout << "{TITLU}: " << carte.get_titlu() << "		" << "{AUTOR}: " << carte.get_autor() << "		" << "{GEN}" << carte.get_gen() << "		" << "{AN}: " << carte.get_an() << endl;
}
void Consola::show()
{
	cout << "===========================================\n";
	cout << "||                AFISARE                 ||\n";
	cout << "===========================================\n\n";
	if (service.get_repo_size() == 0)
		cout << "\nLista este goala, nimic de afisat inca\n\n";
	else {
		const vector<Carte>& rez = service.get_all();
		for(auto &carte: rez)
			print_elem(carte);
		cout << endl;
	}
}
void Consola::print_meniu()
{
	cout << "Bine ati venit in Biblioteca!!\n";
	cout << "Optiuni disponibile:\n";
	cout << "0. EXIT\n";
	cout << "1. Adauga carte\n";
	cout << "2. Afiseaza inventarul\n";
	cout << "3. Cauta carte dupa titlu si autor\n";
	cout << "4. Sterge carte\n";
	cout << "5. Modificare carte\n";
	cout << "6. Filtrare dupa titlu sau anul aparitiei\n";
	cout << "7. Sortare dupa orice criteriu\n";
	cout << "8. Undo ultima actiune\n";
	cout << "9. Cos de inchieri\n>>>";
}
void Consola::sterge()
{
	cout << "===========================================\n";
	cout << "||                STERGERE               ||\n";
	cout << "===========================================\n\n";
	string titlu, autor;
	cout << "Titlul cartii pe care vrei sa o stergi: ";
	getline(cin, titlu);
	cout << "Autorul cartii pe care vrei sa o stergi: ";
	getline(cin, autor);
	try {
		service.sterge_carte_repo(titlu, autor);
		cout << "\nCarte stearsa cu succes!!\n\n";
	}
	catch (const ServiceException& e)
	{
		cout << "Eroare de service: " << e.what()<<"\n";
	}
}
void Consola::cauta()
{
	cout << "===========================================\n";
	cout << "||                CAUTARE               ||\n";
	cout << "===========================================\n\n";
	string titlu, autor;
	cout << "Titlul cartii cautate: ";
	getline(cin, titlu);
	cout << "Autorul cartii cautate: ";
	getline(cin, autor);
	const int poz = service.cauta_carte_repo(titlu, autor);
	if (poz == -1)
	{
		cout << "\nNu exista cartea cautata!!!\n\n";
	}
	else
	{
		cout << "\nCartea cautata este: ";
		const Carte& carte = service.get_elem(poz);
		print_elem(carte);
		cout << endl;
	}


}
void Consola::modifica()
{
	cout << "===========================================\n";
	cout << "||                MODIFICA              ||\n";
	cout << "===========================================\n\n";
	string titlu, autor;
	cout << "Titlul cartii pe care vrei sa o modifici: ";
	getline(cin, titlu);
	cout << "Autorul cartii pe care vrei sa o modifici: ";
	getline(cin, autor);
	service.cauta_carte_repo(titlu, autor);
	string n_titlu, n_autor, n_gen;
	int an;
	cout << "Titlul modificat: ";
	getline(cin, n_titlu);
	cout << "Autorul modificat: ";
	getline(cin, n_autor);
	cout << "Genul modificat: ";
	getline(cin, n_gen);
	cout << "Anul modificat: ";
	string an_str;
	cin >> an_str;
	cin.get();
	try {
		an = stoi(an_str);
	}
	catch (exception)
	{
		cout << "\nAi vrut sa strici aplicatia :(\n\n";
		return;
	}
	Carte new_carte = Carte(n_titlu, n_autor, n_gen, an);
	service.modifica_carte_repo(titlu, autor, new_carte);
	cout << "\nModificare facuta cu succes!\n\n";
}
void Consola::filtreaza()
{

	cout << "===========================================\n";
	cout << "||                FILTREAZA            ||\n";
	cout << "===========================================\n\n";
	cout << "Criteriul dupa care filtrezi?\n";
	cout << "<1> Anumit nume\n";
	cout << "<2> Anumit an de aparitie\n";
	int crt;
	string nume, an,crt_s;
	cin >> crt_s;
	cin.get();
	try {
		crt = stoi(crt_s);
	}
	catch (exception)
	{
		cout << "\nAi vrut sa strici aplicatia :(\n\n";
		return;
	}
	if (crt > 2 || crt < 1)
		cout << "Comanda invalida\n\n";
	else {
		switch (crt) {
		case 1:
		{
			cout << "Numele cartii: ";
			cin >> nume;
			const vector<Carte>& rez=service.filter(right_name, nume);
			if (rez.size() == 0)
				cout << "\nFiltrarea nu a reusit!!\n\n";
			else {
				cout << "\nRezultatele filtrarii:\n";
				for(auto &el:rez)
				{
					print_elem(el);
				}
				cout << "\n";
			}
			break;
		}
		case 2:
		{
			cout << "Anul aparitiei: ";
			cin >> an;
			const vector<Carte>& rez =service.filter(right_year, an);
			if (rez.size() == 0)
				cout << "\nFiltrarea nu a reusit!!\n\n";
			else {
				cout << "\nRezultatele filtrarii:\n";
				for (auto &el : rez)
				{
					print_elem(el);
				}
				cout << "\n";
			}
			break;
		}
		default:
			cout << "\nComanda invalida!\n\n";
			break;
		}
	}
}
void sort_meniu()
{
	cout << "SORTARE DUPA CRITERIU:\n";
	cout << "<1> Titlu\n";
	cout << "<2> Autor\n";
	cout << "<3> Gen\n";
	cout << "<4> An aparitie\n>>>";
}
void Consola::sorteaza()
{

	cout << "===========================================\n";
	cout << "||                SORTEAZA              ||\n";
	cout << "===========================================\n\n";
	sort_meniu();
	int crt=1;
	bool descrescator=true,ok=true;
	string criteriu;
	cin >> criteriu;
	cin.get();
	crt = stoi(criteriu);
	if (crt > 4 || crt < 1) {
		cout << "Comanda invalida!\n\n";
	}
	else {
		cout << "<0> Crescator      <1>Descrescator\n>>>";
		cin >> descrescator;
	;
		switch (crt)
		{
		case 1:
		{
			const vector<Carte>& rez = this->service.sort(compar_nume, descrescator);
			cout << "Rezultatele sortarii:\n";
			for (auto &el : rez)
			{
				print_elem(el);
			}
			cout << "\n";
			break;
		}
		case 2:
		{
			const vector<Carte>& rez = this->service.sort(compar_autor, descrescator);
			cout << "Rezultatele sortarii:\n";
			for (auto &el : rez)
			{
				print_elem(el);
			}
			cout << "\n";
			break;
		}
		case 3:
		{
			const vector<Carte>& rez = this->service.sort(compar_gen, descrescator);
			cout << "Rezultatele sortarii:\n";
	
			for (auto &el : rez)
			{
				print_elem(el);
			}
			cout << "\n";
			break;
		}
		case 4:
		{
			const vector<Carte>& rez = this->service.sort(compar_an, descrescator);
			cout << "Rezultatele sortarii:\n";
			for (auto &el : rez)
			{
				print_elem(el);
			}
			cout << "\n";
			break;
		}
		default:
		{
			ok = false;
			break;
		}
		}
		if (not ok)
			cout << "\nLista goala!!\n\n";
	}
}

void Consola::undo()
{

	cout << "===========================================\n";
	cout << "||                  UNDO                ||\n";
	cout << "===========================================\n\n";
	service.serv_undo();
	show();
}


void print_cos_menu()
{
	cout << "===========================================\n";
	cout << "||               COS INCHIRIERI          ||\n";
	cout << "===========================================\n\n";
	cout << "Optiuni disponibile:\n";
	cout << "0. EXIT\n";
	cout << "1. Adauga carte in cosul de inchirieri\n";
	cout << "2. Goleste cosul\n";
	cout << "3. Afiseaza cosul de inchieri curent\n";
	cout << "4. Salveaza cosul\n";
	cout << "4. Genereaza cos random din inventarul bibliotecii\n>>>";
}
void Consola::cos_add() {
	string titlu, autor;
	cout << "Titlul cartii: ";
	getline(cin, titlu);
	cout << "Autorul cartii: ";
	getline(cin, autor);
	try {
		service.adauga_in_cos(titlu, autor);
		cout << "Carte adaugata in cos!\n";
		cout << "Numar de carti in cos: " << service.how_many_basket() << "\n\n";
	}
	catch (const BasketException& e)
	{
		cout << "BasketError: " << e.what();
		return;
	}
}
void Consola::cos_empty(){
	service.empty_cos();
	cout << "Numar de carti in cos: " << service.how_many_basket() << "\n\n";

}
void Consola::cos_save() {
	string file_name;
	cout << "Numele fisierul in care doresti sa salvezi: ";
	cin >> file_name;
	service.save_cos(file_name);
	cout << "Cosul a fost salvat in fisierul " << file_name << " \n";
	cout << "Numar de carti in cos: " << service.how_many_basket() << "\n\n";

}
void Consola::cos_show() {
	const vector<Carte>& rez = service.get_cos();
	if (rez.size() == 0)
	{
		cout << "Cosul este gol!!!\n";
		cout << "Numar de carti in cos: " << service.how_many_basket() << "\n\n";
		return;
	}
	cout << "\nContinutul cosului este:\n";
	for (auto& el : rez)
	{
		print_elem(el);
	}
	cout << "Numar de carti in cos: " << service.how_many_basket() << "\n\n";
}
void Consola::cos_generate() {
	string cateva;
	int cate = 0;
	cout << "Numarul de carti pe care le doresti in cos: ";
	cin >> cateva;
	try
	{
		cate = stoi(cateva);
		service.generate(cate);
		cout << "Am generat cosul!\n";
		cout << "Numar de carti in cos: " << service.how_many_basket() << "\n\n";

	}
	catch (exception&) {
		cout << "\n\nAcceptam doar numere intregi, imi pare rau\n";
		return;
	}
}
void Consola::cos_stuff()
{
	
	string command;
	int ok = 1,cmd;
	while (ok)
	{
		print_cos_menu();
		try
		{
			cin >> command;
			cin.get();
			cmd = stoi(command);
		}
		catch (const exception&) {
			cout << "\n\nLasa vrajeala! scrie un numar ca ma supar\n";
			cmd = 8;
		}
		switch (cmd)
		{
		case 0:
			cout << "\n\n";
			ok = 0;
			break;
		case 1:
			cos_add();
			break;
		case 2:
			cos_empty();
			break;
		case 3:
			cos_show();
			break;
		case 4:
			cos_save();
			break;
		case 5:
			cos_generate();
			break;
		default:
			cout << "Comanda invalida!\n";
			break;
		}
	}
}
void Consola::run()
{	int cmd=0 , ok = 1;
	string command;
	while (ok)
	{
		print_meniu();
		try
		{
			cin>>command;
			cin.get();
			cmd = stoi(command);
		}
		catch (const exception&) {
			cout << "\n\nLasa vrajeala! scrie un numar ca ma supar\n";
			cmd = 101;
		}
		switch (cmd)
		{
		case 0:
			cout << "BYEEEEE\n";
			ok = 0;
			break;

		case 1:
			try {
				add();
			}
			catch (const RepositoryException& e)
			{
				cout << "\n\nEroare de repo:   " << e.what() << "\n\n";
			}
			catch(const ValidatorException& e)
			{
				cout << "\n\nEroare de validare:   " << e.what() << "\n\n";
			}
			break;
		case 2:
			show();
			break;
		case 3:
			cauta();
			break;
		case 4:
			try
			{
				sterge();
			}
			catch (const ServiceException& e)
			{
				cout << "\n\nEroare de service: " << e.what() << "\n\n";
			}
			break;
		case 5:
			try
			{
				modifica();

			}
			catch (const ServiceException& e)
			{
				cout << "\n\nEroare de service: " << e.what() << "\n\n";
			}
			catch (const ValidatorException& e)
			{
				cout << "\n\nEroare de validare: " << e.what() << "\n\n";
			}

			break;
		case 6:
			try
			{
				filtreaza();
			}
			catch (const exception&)
			{
				cout << "\nAi vrut sa strici aplicatia :(\n\n";
			}
			break;
		case 7:
			try {
				sorteaza();
			}
			catch (const exception&)
			{
				cout << "\nAi vrut sa strici aplicatia :(\n\n";
			}
			break;
		case 8:
			try {
				undo();
			}
			catch(const ServiceException& e){
				cout << "\n\nEroare de service: "<<e.what() << "\n";
			}
			break;
		case 9:


			cos_stuff();
			break;
		default:
			cout << "\n\nComanda invalida\n\n";
			break;
		}



	}
}