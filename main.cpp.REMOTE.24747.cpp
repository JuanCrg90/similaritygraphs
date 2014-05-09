#include "mainwindow.h"
#include <QApplication>
#include "corpus.h"
int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/




    Corpus prueba;
    prueba.setText("Los Gatos Se Comen a Los Ratones y Los osos Comen peces ");
    prueba.generateFrecuencyTable();
    prueba.showText();
    prueba.showFrecuencyTable();






}
