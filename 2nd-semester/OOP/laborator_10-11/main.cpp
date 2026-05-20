#include <QtWidgets/QApplication>
#include "GUI.h"
#include <Domain.h>
#include <qlabel.h>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repository_file* repo = new Repository_file{ "carti.txt" };
    Service* service = new Service{repo};
    GUI g{service};
    CosGUI cos{ service };
    return a.exec();
   
}
