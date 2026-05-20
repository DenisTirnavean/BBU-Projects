#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab13_14.h"

class lab13_14 : public QMainWindow
{
    Q_OBJECT

public:
    lab13_14(QWidget *parent = nullptr);
    ~lab13_14();

private:
    Ui::lab13_14Class ui;
};
