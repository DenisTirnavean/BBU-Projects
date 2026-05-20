#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include "Service.h"


class CosRonly :public QWidget, public Observer {
public:
	//constructor
	CosRonly(Service* serv);

	//varianta de paint event cu override
	void paintEvent(QPaintEvent*) override;
	~CosRonly() {
		service->remove_observer(this);
	}
private:
	//componente
	Service* service;
	
	int contor;


	//utilitare principale
	void init_gui();

	//update din Observer class
	void update() override;

	//Functie de load informatie din service
	void reload();


};