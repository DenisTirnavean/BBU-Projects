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
#include <QTableWidget>
class GUI:public QWidget {
public:
	
	//constructorul GUI
	GUI(Service* Serv){
		this->serv = Serv;
		this->setWindowTitle("Biblioteca");
		initGUI();
		connect();
		adaugaButoane(serv->get_all());
		this->show();
	}

	//destructorul GUI
	~GUI()
	{
		delete main_layout;
		delete lista_carti;
		delete buton_add;
		delete buton_sterge;
		delete main_main_layout;
		delete btn_sort_nume;
		delete btn_sort_autor;
		delete btn_sort_gen;
		delete btn_sort_an;
		delete btn_sort_descrescator;
		delete btn_filter_nume;
		delete btn_filter_an;
		delete buton_dinamic;
		delete lay_dinamic;
		delete tabel_carti;


		delete refresh;
		delete buton_add ;
		delete buton_sterge;
		delete buton_modifica;
		delete buton_sort ;
		delete buton_filter ;
		delete buton_undo ;
		delete buton_cos;

		delete camp_titlu ;
		delete camp_autor;
		delete camp_gen ;
		delete camp_an ;
	}

private:
	//service-ul utilizat de GUI
	Service* serv;
	map<string,int> genuri;
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

	QListWidget* lista_carti = new QListWidget; //tick_mark
	QTableWidget* tabel_carti = new QTableWidget;


	QPushButton* refresh = new QPushButton{ "Refresh continut" };
	QPushButton* buton_add = new QPushButton{"ADAUGA"};
	QPushButton* buton_sterge = new QPushButton{"STERGE"};
	QPushButton* buton_modifica = new QPushButton{ "MODIFICA" };
	QPushButton* buton_sort = new QPushButton{ "SORTEAZA" };
	QPushButton* buton_filter = new QPushButton{ "FILTREAZA" };
	QPushButton* buton_undo = new QPushButton{ "UNDO" };
	QPushButton* buton_cos = new QPushButton{ "COS INCHIRIERI" };

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
};


class CosGUI :public QWidget {
public:
	CosGUI(Service* serv) {
		this->serv = serv;
		this->setWindowTitle("Cos inchierieri");
		init_GUI();
		connect();
		this->show();
	}
	~CosGUI()
	{
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

	QPushButton* buton_save = new QPushButton{"Salveaza cosul de inchirieri"};
	QPushButton* buton_empty = new QPushButton{"Goleste cosul"};
	QPushButton* buton_genereaza = new QPushButton{"Genereaza un cos la intamplare"};
	QPushButton* buton_adauga = new QPushButton{"Adauga in cos"};

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
};