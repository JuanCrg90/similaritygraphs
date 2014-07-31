#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());
}

About::~About()
{
    delete ui;
}
