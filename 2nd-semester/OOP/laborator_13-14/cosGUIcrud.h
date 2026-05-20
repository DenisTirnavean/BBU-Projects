#pragma once
#include "Service.h"
#include "Cos.h"
#include "Exceptii.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qmainwindow.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <qdebug.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <iostream>
#include <sstream>

class CosGUIcrud :public QWidget,public Observer {
public:
	CosGUIcrud(Service* serv) {
		this->serv = serv;
		serv->add_observer(this);
		this->setWindowTitle("Cos CRUD");
		init_GUI();
		connect();
		this->show();
	}
	~CosGUIcrud()
	{
		serv->remove_observer(this);
		delete cos_carti;
		delete main_layout;
		delete buton_save;
		delete buton_empty;
		delete buton_genereaza;
		delete buton_adauga;
		delete contor;
		delete camp_titlu;
		delete camp_autor;
		delete camp_cate;
		delete camp_file_name;
	}
private:
	Service* serv;

	//componente
	QListWidget* cos_carti = new QListWidget;
	QHBoxLayout* main_layout = new QHBoxLayout;

	QPushButton* buton_save = new QPushButton{ "Salveaza cosul de inchirieri" };
	QPushButton* buton_empty = new QPushButton{ "Goleste cosul" };
	QPushButton* buton_genereaza = new QPushButton{ "Genereaza un cos la intamplare" };
	QPushButton* buton_adauga = new QPushButton{ "Adauga in cos" };

	QLabel* contor = new QLabel{ "Ai in cos exact 0 carti" };
	QLineEdit* camp_titlu = new QLineEdit;
	QLineEdit* camp_autor = new QLineEdit;
	QLineEdit* camp_cate = new QLineEdit;
	QLineEdit* camp_file_name = new QLineEdit;



	void reload();

	void update_eticheta();

	void adauga_in_cos();

	void MT_cos();

	void genereaza();

	void save_cos();

	void init_GUI();

	void reset_form();

	void connect();

	virtual void update() override;
};