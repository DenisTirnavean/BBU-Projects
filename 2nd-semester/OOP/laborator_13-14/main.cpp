#include <QtWidgets/QApplication>
#include "mainGUI.h"
#include "cosGUIcrud.h"
#include "cosRONLY.h"

using namespace std;
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Repository_file* repo = new Repository_file{ "carti.txt" };
    Service* service = new Service{ repo };
    GUI g{ service };
    //CosGUIcrud cos{ service };
    //CosRonly cos2{ service };
    
    return a.exec();

}
