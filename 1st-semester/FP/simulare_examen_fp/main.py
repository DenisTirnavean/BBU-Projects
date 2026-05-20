from tests.teste import Test
from presentation.ui import Consola
tester=Test()
tester.run_all_tests()
filepath="repository/vm.txt"
try:
    consola=Consola(filepath)
    consola.run()
except IOError:
    print("Fisier corupt")