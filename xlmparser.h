#ifndef XLMPARSER_H
#define XLMPARSER_H

#include <QWidget>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QXmlStreamReader>
#include "preprocesor.h"



namespace Ui {
class XLMParser;
}

class XLMParser : public QWidget
{
    Q_OBJECT

public:
    explicit XLMParser(QWidget *parent = 0);
    ~XLMParser();


public slots:

    void onLoadClick();


private:
    Ui::XLMParser *ui;
};

#endif // XLMPARSER_H
