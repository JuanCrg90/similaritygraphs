#include "mainwindow.h"
#include <QApplication>
#include "corpus.h"

#include "preprocesor.h"


int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/



/*
    Corpus prueba;
    prueba.setText(" &lt;br /&gt; ");
    prueba.generateFrecuencyTable();
    prueba.showText();
    prueba.showFrecuencyTable();
*/


    vector<string> stopWords;

    stopWords.push_back("el");
    stopWords.push_back("los");
    stopWords.push_back("en");
    stopWords.push_back("por");


    Preprocesor test;
    test.setText("Casa #225 en el camion 23 de el emperador corre por los prados");

    cout<<test.getText()<<endl;
    cout<<"tags html"<<endl;
    test.removeHtmlTags();
    cout<<test.getText()<<endl;

    cout<<"urls"<<endl;
    test.removeUrls();
    cout<<test.getText()<<endl;


    cout<<"Punctuacion"<<endl;
    test.removePunctiationMarks();
    cout<<test.getText()<<endl;

    cout<<"Tolower"<<endl;
    test.toLower();
    cout<<test.getText()<<endl;

    cout<<"Numbers"<<endl;
    test.removeNumbers();
    cout<<test.getText()<<endl;


    Corpus prueba;
    prueba.setText(test.getText());
    prueba.generateFrecuencyTable();
    prueba.showText();
    prueba.showFrecuencyTable();

    prueba.removeStopWords(stopWords);

prueba.showFrecuencyTable();

}
