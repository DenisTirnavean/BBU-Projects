#pragma once
#include "MyListModel.h"
#include "Service.h"
#include "Cos.h"
#include "Exceptii.h"
#include "cosGUIcrud.h"
#include "cosRONLY.h"
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
#include <QTableWidget>
class GUI :public QWidget,public Observer{
public:

	//constructorul GUI
	GUI(Service* Serv) {
		this->serv = Serv;
		this->setWindowTitle("Biblioteca");
		lista_carti_v2 = new MyListModel{ serv->get_all() };
		lst_view->setModel(lista_carti_v2);

		initGUI();
		connect();
		adaugaButoane(serv->get_all());
		this->show();
	}

	//destructorul GUI
	~GUI(){}

private:
	//service-ul utilizat de GUI
	Service* serv;
	map<string, int> genuri;

	//componente

	QCheckBox* btn_sort_nume = new QCheckBox("Sorteaza dupa nume");
	QCheckBox* btn_sort_autor = new QCheckBox("Sorteaza dupa autor");
	QCheckBox* btn_sort_gen = new QCheckBox("Sorteaza dupa gen");
	QCheckBox* btn_sort_an = new QCheckBox("Sorteaza dupa anul aparitiei");
	QCheckBox* btn_sort_descrescator = new QCheckBox("Descrescator");

	QCheckBox* btn_filter_nume = new QCheckBox("Filtreaza dupa titlu");
	QCheckBox* btn_filter_an = new QCheckBox("Filtreaza dupa anul aparitiei");

	QHBoxLayout* main_layout = new QHBoxLayout; //tick_mark
	QHBoxLayout* main_main_layout = new QHBoxLayout; //tick_mark
	QWidget* buton_dinamic = new QWidget;
	QVBoxLayout* lay_dinamic = new QVBoxLayout;;

	//Model View
	QListView* lst_view = new QListView;
	MyListModel* lista_carti_v2;

	QListWidget* lista_carti = new QListWidget; //tick_mark
	QTableWidget* tabel_carti = new QTableWidget;

	QPushButton* open_crud = new QPushButton{ "Deschide Cos CRUD" };
	QPushButton* open_ronly = new QPushButton{ "Deschide Cos Read-only" };
	QPushButton* refresh = new QPushButton{ "Refresh continut" };
	QPushButton* buton_add = new QPushButton{ "ADAUGA" };
	QPushButton* buton_sterge = new QPushButton{ "STERGE" };
	QPushButton* buton_modifica = new QPushButton{ "MODIFICA" };
	QPushButton* buton_sort = new QPushButton{ "SORTEAZA" };
	QPushButton* buton_filter = new QPushButton{ "FILTREAZA" };
	QPushButton* buton_undo = new QPushButton{ "UNDO" };

	QPushButton* buton_cos_add = new QPushButton{ "Adauga in cos" };
	QPushButton* buton_cos_goleste = new QPushButton{ "Goleste cos" };
	QPushButton* buton_cos_gen = new QPushButton{ "Genereaza 10" };


	QLineEdit* camp_titlu = new QLineEdit;
	QLineEdit* camp_autor = new QLineEdit;
	QLineEdit* camp_gen = new QLineEdit;
	QLineEdit* camp_an = new QLineEdit;

	//initializeaza GUI cu toate componentele necesare
	void initGUI();


	//conecteaza butoanele la functionalitati
	void connect();

	//Functie care populeaza GUI cu carti din repository
	void load_carti();

	//functie de repolare lista de carti cu continutul unui nou vector
	void reload_carti(const vector<Carte> new_list);

	//functionalitati

	//adaugare
	void adauga();

	//stergere
	void sterge();

	//updatte
	void modifica();

	//undo
	void undo();

	//sortare dupa literalmente orice criteriu imaginabil
	void sorteaza();

	//filtrare dupa titlu sau an
	void filtreaza();

	//functie de resetare formular
	void reset_form();

	void onItemSelected();

	void adaugaButoane(const vector<Carte>& carti);

	void load_tabel();

	void general_load();

	void reload_tabel(const vector<Carte>& carti);
	 
	void update() override;
};


