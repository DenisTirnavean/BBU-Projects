#include "cosRONLY.h"

void CosRonly::init_gui()
{
	this->setWindowTitle("Cos Read-only");
	
	this->setStyleSheet("background-color:#f2746b");
}

CosRonly::CosRonly(Service* serv)
{
	this->service = serv;
	contor = service->get_cos().size();
	service->add_observer(this);
	this->setWindowTitle("Cos Read-only");
	this->setStyleSheet("background-color:#824fdb");
	init_gui();
	reload();
	this->show();
};

void CosRonly::update()
{
	reload();
	repaint();
}

void CosRonly::reload()
{
	contor = service->get_cos().size();
}

void CosRonly::paintEvent(QPaintEvent*){
	QPainter p{ this };
	srand(time(NULL));
	int x, y, index_rmd;
	vector<string> poze{ "C:/Users/Denis/Desktop/imagini_OOP/photo1.jpg",
		"C:/Users/Denis/Desktop/imagini_OOP/photo2.jpg",
		"C:/Users/Denis/Desktop/imagini_OOP/photo3.jpg",
		"C:/Users/Denis/Desktop/imagini_OOP/photo4.jpg",
		"C:/Users/Denis/Desktop/imagini_OOP/photo5.jpg",
		"C:/Users/Denis/Desktop/imagini_OOP/photo6.jpg",
		"C:/Users/Denis/Desktop/imagini_OOP/pescarus.jpg"
	};
	for (int i = 0; i < contor; i++)
	{
		x = rand() % 800 + 1;
		y = rand() % 400 + 1;
		index_rmd = rand() % 7; //index maxim 6 ca avem 7 poze
		auto poza_norocoasa = poze.at(index_rmd);

		QRectF target(x, y, 80, 120);
		QRectF source(0, 0, 346, 544);
		QImage image(poza_norocoasa.c_str());

		p.drawImage(target, image, source);
	
	}
}