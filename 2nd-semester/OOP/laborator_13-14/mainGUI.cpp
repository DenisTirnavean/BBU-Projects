#include "mainGUI.h"



void GUI::initGUI()
{

    this->setStyleSheet("background-color:#342d70");
    setLayout(main_main_layout);
    load_carti();
    tabel_carti->setStyleSheet("background-color:#8465ba");
    load_tabel();
    main_layout->addStretch();
    QVBoxLayout* layout_right = new QVBoxLayout;

    //Model view
    layout_right->addWidget(lst_view);

    //lista normala
    //layout_right->addWidget(lista_carti);

    refresh->setStyleSheet("background-color:#6151f5");
    open_crud->setStyleSheet("background-color:#6151f5");
    open_ronly->setStyleSheet("background-color:#6151f5");
    QHBoxLayout* layout_boss = new QHBoxLayout;
    layout_boss->addWidget(refresh);
    layout_boss->addWidget(open_crud);
    layout_boss->addWidget(open_ronly);
    layout_right->addLayout(layout_boss);
    QHBoxLayout* layout_pt_cos = new QHBoxLayout;
    buton_cos_add->setStyleSheet("background-color:#5a3773");
    buton_cos_goleste->setStyleSheet("background-color:#5a3773");
    buton_cos_gen->setStyleSheet("background-color:#5a3773");

    layout_pt_cos->addWidget(buton_cos_add);
    layout_pt_cos->addWidget(buton_cos_goleste);
    layout_pt_cos->addWidget(buton_cos_gen);
    
    layout_right->addLayout(layout_pt_cos);

    main_layout->addLayout(layout_right);
    main_layout->addStretch();
    QVBoxLayout* left_layout = new QVBoxLayout;

    QWidget* form = new QWidget;
    QFormLayout* lay_form = new QFormLayout;
    form->setLayout(lay_form);

    QLabel* titlu = new QLabel("Titlu:");

    QLabel* autor = new QLabel("Autor:");

    QLabel* gen = new QLabel("Gen:");

    QLabel* an = new QLabel("An aparitie:");



    lay_form->addRow(titlu, camp_titlu);
    lay_form->addRow(autor, camp_autor);
    lay_form->addRow(gen, camp_gen);
    lay_form->addRow(an, camp_an);

    left_layout->addWidget(form);

    QHBoxLayout* lay_buttons = new QHBoxLayout;
    QVBoxLayout* coloana1 = new QVBoxLayout;
    QVBoxLayout* coloana2 = new QVBoxLayout;

    buton_add->setStyleSheet("background-color:#353a9c");
    buton_sort->setStyleSheet("background-color:#353a9c");
    buton_modifica->setStyleSheet("background-color:#353a9c");

    buton_sterge->setStyleSheet("background-color:#543c75");
    buton_undo->setStyleSheet("background-color:#543c75");
    buton_filter->setStyleSheet("background-color:#543c75");

    lista_carti->setStyleSheet("background-color:#353a9c");

    QHBoxLayout* lay_basic = new QHBoxLayout;
    lay_basic->addWidget(buton_add);
    lay_basic->addStretch();
    lay_basic->addWidget(buton_sterge);
    lay_basic->addStretch();
    lay_basic->addWidget(buton_modifica);
    lay_basic->addStretch();
    lay_basic->addWidget(buton_undo);
    lay_basic->addStretch();

    left_layout->addLayout(lay_basic);

    QWidget* panou_sort = new QWidget;
    QGridLayout* lyt_sort = new QGridLayout;
    lyt_sort->addWidget(buton_sort);
    QButtonGroup* grup_sort = new QButtonGroup();
    grup_sort->addButton(btn_sort_nume);
    grup_sort->addButton(btn_sort_autor);
    grup_sort->addButton(btn_sort_gen);
    grup_sort->addButton(btn_sort_an);
    grup_sort->setExclusive(true);
    lyt_sort->addWidget(btn_sort_nume);
    lyt_sort->addWidget(btn_sort_autor);
    lyt_sort->addWidget(btn_sort_gen);
    lyt_sort->addWidget(btn_sort_an);
    lyt_sort->addWidget(btn_sort_descrescator);
    panou_sort->setLayout(lyt_sort);
    coloana2->addStretch();
    coloana2->addWidget(panou_sort);
    coloana2->addStretch();

    QWidget* panou_filter = new QWidget;
    QGridLayout* lyt_filter = new QGridLayout;
    QButtonGroup* grup_filter = new QButtonGroup();
    grup_filter->setExclusive(true);
    grup_filter->addButton(btn_filter_nume);
    grup_filter->addButton(btn_filter_an);
    lyt_filter->addWidget(buton_filter);
    lyt_filter->addWidget(btn_filter_nume);
    lyt_filter->addWidget(btn_filter_an);
    panou_filter->setLayout(lyt_filter);

    coloana1->addWidget(panou_filter);


    lay_buttons->addLayout(coloana1);
    lay_buttons->addLayout(coloana2);

    left_layout->addStretch();
    left_layout->addLayout(lay_buttons);

    main_layout->addLayout(left_layout);
    main_layout->addStretch();


    main_layout->addLayout(lay_dinamic);
    main_main_layout->addLayout(main_layout);
    main_main_layout->addWidget(tabel_carti);


}

void GUI::load_carti()
{
    this->lista_carti->clear();
    auto& lista = serv->get_all();
    for (auto& carte : lista)
    {
        auto item = QString::fromStdString(",," + carte.get_titlu() + "''  de  " + carte.get_autor());
        lista_carti->addItem(item);

    }
    //pentru lista MylistModel
    this->lista_carti_v2->set_carti(serv->get_all());
}
void GUI::connect()
{
    QObject::connect(lista_carti, &QListWidget::currentTextChanged, this, &GUI::onItemSelected);
    QObject::connect(lista_carti, &QListWidget::itemSelectionChanged, this, &GUI::onItemSelected);
    QObject::connect(buton_add, &QPushButton::clicked, this, &GUI::adauga);
    QObject::connect(buton_sterge, &QPushButton::clicked, this, &GUI::sterge);
    QObject::connect(buton_undo, &QPushButton::clicked, this, &GUI::undo);
    QObject::connect(buton_modifica, &QPushButton::clicked, this, &GUI::modifica);
    QObject::connect(refresh, &QPushButton::clicked, this, &GUI::general_load);
    QObject::connect(buton_sort, &QPushButton::clicked, this, &GUI::sorteaza);
    QObject::connect(buton_filter, &QPushButton::clicked, this, &GUI::filtreaza);

    QObject::connect(open_crud, &QPushButton::clicked, this, [this]() {
        CosGUIcrud* cos_tip1 = new CosGUIcrud(serv);
        cos_tip1->show();
        });
    QObject::connect(open_ronly, &QPushButton::clicked, this, [this]() {
        CosRonly* cos_tip2 = new CosRonly(serv);
        cos_tip2->show();
        });

    QObject::connect(buton_cos_add, &QPushButton::clicked, this, [this]() {
        auto titlu =camp_titlu->text().toStdString();
        auto autor = camp_autor->text().toStdString();
        auto ok = serv->cauta_carte_repo(titlu, autor);
        if (ok == -1)
        {
            QMessageBox::warning(this, "Eroare de cos", "Carte indisponibila");
        }
        else {
            serv->adauga_in_cos(titlu, autor);
            QMessageBox::information(this, "Succes", "Carte adaugata cu succes");
        }
        });
    QObject::connect(buton_cos_goleste, &QPushButton::clicked, this, [this]() {
        serv->empty_cos();
        QMessageBox::information(this, "Succes", "Cosul de inchirieri s-a golit");
        });
    QObject::connect(buton_cos_gen, &QPushButton::clicked, this, [this]() {
        serv->generate(10);
        QMessageBox::information(this, "Succes", "Carti generate cu succes");
        });
    QObject::connect(lst_view->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        auto selected = lst_view->selectionModel();
        if (selected->selectedIndexes().empty()) {
            camp_titlu->setText("");
            camp_autor->setText("");
            camp_gen->setText("");
            camp_an->setText("");
            return;
        }
        else {
            auto selected_index = selected->selectedIndexes().at(0).row();
            Carte c = serv->get_elem(selected_index);
            camp_titlu->setText(QString::fromStdString(c.get_titlu()));
            camp_autor->setText(QString::fromStdString(c.get_autor()));
            camp_gen->setText(QString::fromStdString(c.get_gen()));
            camp_an->setText(QString::fromStdString(to_string(c.get_an())));
        }
        });
}
void GUI::general_load()
{
    load_carti();
    load_tabel();
}
void GUI::adauga() {
    try {
        auto titlu = camp_titlu->text().toStdString();
        auto autor = camp_autor->text().toStdString();
        serv->creaza_valideaza_adauga(camp_titlu->text().toStdString(), camp_autor->text().toStdString(), camp_gen->text().toStdString(), camp_an->text().toInt());
        load_carti();
        load_tabel();
        QMessageBox::information(this, "SUCCES", QString("Carte adaugata cu succes"));
        reset_form();
        Carte carte = serv->get_elem(serv->cauta_carte_repo(titlu, autor));
        const auto it = find_if(genuri.begin(), genuri.end(), [=](const auto& elem) {
            return elem.first == carte.get_gen();
            });
        if (it == genuri.end())
        {
            auto btn = new QPushButton{ QString::fromStdString(carte.get_gen()) };
            lay_dinamic->addWidget(btn);
            genuri.insert(make_pair(carte.get_gen(), 1));
            QObject::connect(btn, &QPushButton::clicked, [this, btn, carte]() {
                QMessageBox::information(nullptr, "Information", QString::number(genuri.at(carte.get_gen())));
                lay_dinamic->removeWidget(btn);
                delete btn;
                });
        }
        else {
            genuri.at(carte.get_gen()) = genuri.at(carte.get_gen()) + 1;
        }
    }
    catch (const ValidatorException& e)
    {
        QMessageBox::warning(this, "EROARE DE VALIDARE", QString(e.what()));
    }
    catch (const RepositoryException& e)
    {
        QMessageBox::warning(this, "EROARE DE REPOSITORY", QString(e.what()));
    }

}
void GUI::sterge() {
    if (camp_titlu->text() == "" or camp_autor->text() == "")
    {
        QMessageBox::warning(this, "EROARE", "Esti foarte bun,bravo");
    }
    else {
        try {
            auto gen = serv->get_elem(serv->cauta_carte_repo(camp_titlu->text().toStdString(), camp_autor->text().toStdString())).get_gen();
            serv->sterge_carte_repo(camp_titlu->text().toStdString(), camp_autor->text().toStdString());
            load_carti();
            load_tabel();
            QMessageBox::information(this, "SUCCES", QString("Carte stearsa cu succes"));
            const auto it = find_if(genuri.begin(), genuri.end(), [=](const auto& elem) {
                return elem.first == gen;
                });
            if (it == genuri.end())
            {
                genuri[gen] = 0;
            }
            else {
                genuri.at(gen) = genuri.at(gen) - 1;
            }
            reset_form();
        }
        catch (const ServiceException& e) {
            QMessageBox::warning(this, "EROARE DE SERVICE", QString(e.what()));
        }
    }
}
void GUI::modifica() {
    try {
        Carte carte{ camp_titlu->text().toStdString(),camp_autor->text().toStdString(),camp_gen->text().toStdString(), camp_an->text().toInt() };
        serv->modifica_carte_repo(camp_titlu->text().toStdString(), camp_autor->text().toStdString(), carte);
        QMessageBox::information(this, "SUCCES", QString("Carte modificata cu succes"));
        load_tabel();
        reset_form();
    }
    catch (const ValidatorException& e)
    {
        QMessageBox::warning(this, "EROARE DE VALIDARE", QString(e.what()));
    }
    catch (const exception& e)
    {
        QMessageBox::warning(this, "EROARE DE REPOSITORY", QString(e.what()));
    }
}
void GUI::sorteaza() {
    vector<Carte> rezultat;
    if (btn_sort_nume->checkState() == Qt::Checked)
        rezultat = serv->sort(compar_nume, btn_sort_descrescator->checkState() == Qt::Checked);
    if (btn_sort_autor->checkState() == Qt::Checked)
        rezultat = serv->sort(compar_autor, btn_sort_descrescator->checkState() == Qt::Checked);
    if (btn_sort_gen->checkState() == Qt::Checked)
        rezultat = serv->sort(compar_gen, btn_sort_descrescator->checkState() == Qt::Checked);
    if (btn_sort_an->checkState() == Qt::Checked)
        rezultat = serv->sort(compar_an, btn_sort_descrescator->checkState() == Qt::Checked);

    reload_carti(rezultat);
    reload_tabel(rezultat);
    reset_form();
}
void GUI::undo() {
    try {
        serv->serv_undo();
        load_carti();
        load_tabel();
    }
    catch (const ServiceException& e)
    {
        QMessageBox::warning(this, "EROARE DE SERVICE", QString(e.what()));
    }
}
void GUI::reset_form()
{
    camp_titlu->setText("");
    camp_autor->setText("");
    camp_gen->setText("");
    camp_an->setText("");
}
void GUI::reload_carti(const vector<Carte> new_list)
{
    this->lista_carti->clear();
    for (auto& carte : new_list)
    {
        auto item = QString::fromStdString(",," + carte.get_titlu() + "''  de  " + carte.get_autor());
        lista_carti->addItem(item);
    }
    this->lista_carti_v2->set_carti(new_list);
}
void GUI::filtreaza()
{
    vector<Carte> rezultat;
    if (btn_filter_nume->checkState() == Qt::Checked)
        rezultat = serv->filter(right_name, camp_titlu->text().toStdString());
    if (btn_filter_an->checkState() == Qt::Checked)
        rezultat = serv->filter(right_year, camp_an->text().toStdString());
    reload_carti(rezultat);
    reload_tabel(rezultat);
    reset_form();
}

void GUI::onItemSelected()
{
    auto sel = lista_carti->selectionModel();
    if (sel->selectedIndexes().empty()) {
        camp_titlu->setText("");
        camp_autor->setText("");
        camp_gen->setText("");
        camp_an->setText("");
        return;
    }
    auto sel_index = sel->selectedIndexes().at(0).row();
    auto elem = serv->get_elem(sel_index);
    camp_titlu->setText(QString::fromStdString(elem.get_titlu()));
    camp_autor->setText(QString::fromStdString(elem.get_autor()));
    camp_gen->setText(QString::fromStdString(elem.get_gen()));
    camp_an->setText(QString::number(elem.get_an()));

}

void GUI::adaugaButoane(const vector<Carte>& carti)
{
    for (auto& p : carti)
    {
        const auto it = find_if(genuri.begin(), genuri.end(), [=](const auto& elem) {
            return elem.first == p.get_gen();
            });
        if (it == genuri.end())
        {
            auto btn = new QPushButton{ QString::fromStdString(p.get_gen()) };
            lay_dinamic->addWidget(btn);
            genuri.insert(make_pair(p.get_gen(), 1));
            QObject::connect(btn, &QPushButton::clicked, [this, btn, p]() {
                QMessageBox::information(nullptr, "Explorer", QString::number(genuri.at(p.get_gen())));
                //lay_dinamic->removeWidget(btn);
                //delete btn;
          
                });
        }
        else {
            genuri.at(p.get_gen()) = genuri.at(p.get_gen()) + 1;
        }

    }
}

void GUI::load_tabel()
{
    this->tabel_carti->clearContents();
    auto& lista = serv->get_all();
    tabel_carti->setRowCount(int(lista.size()));
    tabel_carti->setColumnCount(4);
    QStringList headers = { "Titlu", "Autor", "Gen", "An aparitie" };
    tabel_carti->setHorizontalHeaderLabels(headers);
    for (int row = 0; row < (int)(lista.size()); ++row) {
        const Carte& carte = lista[row];

        tabel_carti->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(carte.get_titlu())));
        tabel_carti->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(carte.get_autor())));
        tabel_carti->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(carte.get_gen())));
        tabel_carti->setItem(row, 3, new QTableWidgetItem(QString::number(carte.get_an())));
    }
}

void GUI::reload_tabel(const vector<Carte>& carti)
{
    tabel_carti->setRowCount(static_cast<int>(carti.size()));
    tabel_carti->setColumnCount(4);
    QStringList headers = { "Titlu", "Autor", "Gen", "An aparitie" };
    tabel_carti->setHorizontalHeaderLabels(headers);
    for (int row = 0; row < static_cast<int>(carti.size()); ++row) {
        const Carte& carte = carti[row];

        tabel_carti->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(carte.get_titlu())));
        tabel_carti->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(carte.get_autor())));
        tabel_carti->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(carte.get_gen())));
        tabel_carti->setItem(row, 3, new QTableWidgetItem(QString::number(carte.get_an())));
    }
}

void GUI::update()
{
    general_load();
}
