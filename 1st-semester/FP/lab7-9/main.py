from tests.teste_files import Final_Tester
from presentation.ui import Consola,ConsolaFile
tester=Final_Tester()
#tester.run_test()
console=ConsolaFile("repository/evenimente.txt","repository/persoane.txt","repository/inscriere.txt")
console.run()
