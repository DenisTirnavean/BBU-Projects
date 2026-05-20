#include "MyListModel.h"

int MyListModel::rowCount(const QModelIndex& parent) const
{
	return carti.size();
}

QVariant MyListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		auto c = string("'")+carti[index.row()].get_titlu() + string{"' de "} + carti[index.row()].get_autor();
		return QString::fromStdString(c);
	}
	return QVariant{};
}

void MyListModel::set_carti(const vector<Carte>& c)
{
	this->carti = c;
	auto top = createIndex(0, 0);
	auto bottom = createIndex(rowCount(), 0);
	emit dataChanged(top,bottom);
	emit layoutChanged();
}
