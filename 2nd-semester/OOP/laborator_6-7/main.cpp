#include <iostream>
#include "Teste.h"
#include "UI.h"
#include "MyList.h"
#include <string>
#include <crtdbg.h>
#include <exception>
using namespace std;
int main()
{
	
	int cmd = 1;
	cout << "Vrei sa ruleze testele < 1 / 0 >?\n>>>";
	{
		cin >> cmd;
		if (cmd)
		{
			Tester test = Tester();
			test.test_all();
		}
		Consola console;
		console.run();
	}
	
	_CrtDumpMemoryLeaks();
	return 0;
}
