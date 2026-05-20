#include "cosGUIcrud.h"


void CosGUIcrud::init_GUI()
{
    this->setStyleSheet("background-color:#342d70");
    setLayout(main_layout);
    QVBoxLayout* left_lay = new QVBoxLayout;
    cos_carti->setStyleSheet("background-color:#824fdb");
    left_lay->addWidget(cos_carti);
    left_lay->addWidget(buton_save);
    buton_save->setStyleSheet("background-color:#7250ab");
    main_layout->addLayout(left_lay);
    this->update_eticheta();
    QWidget* form = new QWidget;
    QFormLayout* lay_form = new QFormLayout;
    form->setLayout(lay_form);
    QVBoxLayout* right_lay = new QVBoxLayout;
    QLabel* titlu = new QLabel("Titlu:");
    QLabel* autor = new QLabel("Autor:");
    QLabel* file_name = new QLabel("Nume fisier pentru salvare:");
    QLabel* cate = new QLabel("Numar de carti pentru generare aleatorie:");
    lay_form->addRow(titlu, camp_titlu);
    lay_form->addRow(autor, camp_autor);
    lay_form->addRow(cate, camp_cate);
    lay_form->addRow(file_name, camp_file_name);
    right_lay->addWidget(form);
    QHBoxLayout* buton_layout = new QHBoxLayout;

    buton_layout->addWidget(buton_adauga);
    buton_adauga->setStyleSheet("background-color:#824fdb");
    buton_layout->addWidget(buton_genereaza);
    buton_genereaza->setStyleSheet("background-color:#824fdb");
    buton_layout->addWidget(buton_empty);
    buton_empty->setStyleSheet("background-color:#824fdb");
    right_lay->addLayout(buton_layout);
    right_lay->addStretch();
    right_lay->addWidget(contor);
    main_layout->addLayout(right_lay);
    reload();

}

void CosGUIcrud::connect()
{
    QObject::connect(buton_adauga, &QPushButton::clicked, this, &CosGUIcrud::adauga_in_cos);
    QObject::connect(buton_empty, &QPushButton::clicked, this, &CosGUIcrud::MT_cos);
    QObject::connect(buton_save, &QPushButton::clicked, this, &CosGUIcrud::save_cos);
    QObject::connect(buton_genereaza, &QPushButton::clicked, this, &CosGUIcrud::genereaza);


}
void CosGUIcrud::update()
{
    this->reload();
    this->reset_form();
    this->update_eticheta();
}
void CosGUIcrud::adauga_in_cos() {
    try {
        serv->adauga_in_cos(camp_titlu->text().toStdString(), camp_autor->text().toStdString());
        QMessageBox::information(this, "SUCCES", QString("Carte adaugata cu succes"));
        reload();
        reset_form();
        update_eticheta();
    }
    catch (const BasketException& e)
    {
        QMessageBox::warning(this, "EROARE DE COS", QString(e.what()));
    }
}
void CosGUIcrud::reload() {
    this->cos_carti->clear();
    auto& cosulet = serv->get_cos();
    for (auto& carte : cosulet)
    {
        auto item = QString::fromStdString(",," + carte.get_titlu() + "''  de  " + carte.get_autor());
        cos_carti->addItem(item);
    }
}
void CosGUIcrud::MT_cos()
{
    serv->empty_cos();
    this->cos_carti->clear();
    reset_form();
    update_eticheta();
}
void CosGUIcrud::save_cos()
{
    if (camp_file_name->text().toStdString() == "")
        QMessageBox::warning(this, "EROARE DE BUN SIMT", "Ai uitat sa mentionezi fisierul pentru salvare");
    else {
        if (serv->how_many_basket() == 0)
            QMessageBox::warning(this, "EROARE COS", "Fyi ai fi vrut sa salvezi un cos gol");
        else {
            serv->save_cos(camp_file_name->text().toStdString());
            QMessageBox::information(this, "SUCCES", "Cos salvat cu succes");
            reset_form();
        }
    }
}
void CosGUIcrud::update_eticheta()
{
    string new_etich = string("Ai in cos exact ") + to_string(serv->how_many_basket()) + string(" carti");
    contor->setText(QString::fromStdString(new_etich));
}
void CosGUIcrud::reset_form()
{
    camp_titlu->setText("");
    camp_autor->setText("");
    camp_file_name->setText("");
    camp_cate->setText("");
}
void CosGUIcrud::genereaza()
{
    if (camp_cate->text() == "" || camp_cate->text().toInt() == 0)
        QMessageBox::warning(this, "EROARE COS", "Numar invalid de carti pentru generare");
    else {
        try {
            serv->generate(camp_cate->text().toInt());
            QMessageBox::information(this, "SUCCES", "Carti generate cu succes");
            update_eticheta();
            reset_form();
            reload();
        }
        catch (const BasketException& e)
        {
            QMessageBox::warning(this, "EROARE COS", e.what());
        }
    }
}