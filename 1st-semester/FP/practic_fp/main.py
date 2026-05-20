from user_interface.ui import Consola
from teste.test_service import Final_tester

test=Final_tester()
test.run_all_tests()
try:
    consola=Consola("repository/fisier_sedinte.txt")
    consola.run()
except IOError:
    print("Nu s-a putut realiza deschiderea fisierului")
