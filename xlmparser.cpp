#include "xlmparser.h"
#include "ui_xlmparser.h"

XLMParser::XLMParser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XLMParser)
{
    ui->setupUi(this);
}

XLMParser::~XLMParser()
{
    delete ui;
}
