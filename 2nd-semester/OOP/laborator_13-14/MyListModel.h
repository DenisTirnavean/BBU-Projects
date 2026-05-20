#pragma once
#include "Service.h"
#include <qlistview.h>

class MyListModel : public QAbstractListModel {
public:
	//constructor
	MyListModel(const vector<Carte>& c) : carti{c} {}

	//Returneaza cate elemente ar trebui sa aibe lista
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	//Functie care aduce din lista de carti exact cartea vizualizata
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void set_carti(const vector<Carte>& c);


private:
	vector<Carte> carti;
};