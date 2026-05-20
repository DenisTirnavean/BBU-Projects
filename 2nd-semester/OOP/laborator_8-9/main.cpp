#include <iostream>
#include "Teste.h"
#include "UI.h"
#include <string>
#include <crtdbg.h>
#include "Exceptii.h"
using namespace std;
int main()
{
	{
		int cmd = 1;
		cout << "Vrei sa ruleze testele < 1 / 0 >?    \n>>>";
		//cin >> cmd;
		if (cmd)
		{
			Tester test = Tester();
			test.test_all();
		}
		//auto* repository = new Repository_file{ "carti.txt" };
		//auto* repository = new Repository;
		
		string pb;
		cout << "Cat de unreliable sa fie repo?(pe o scara de la 0 la 1)\n>>>";
		float probabilitate = (float)0.7;
		
		cin >> pb;
		try {
			probabilitate = stof(pb);
		}
		catch (exception&)
		{
			cout << "Ai incercat sa strici aplicatia :( \nPentru asta punem default 0.5\n";
			probabilitate = (float)0.5;
		}
		
		auto* repository = new Repository_map{ probabilitate };

		auto service = Service(repository);
		Consola console = Consola(service);
		console.run();
		delete repository;
	}

	cout << "\n";
	_CrtDumpMemoryLeaks();
	
	return 0;
}
