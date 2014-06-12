#include "mainwindow.h"
#include <QApplication>
#include "corpora.h"


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
/*

    vector<string> stopWords;

    stopWords.push_back("el");
    stopWords.push_back("los");
    stopWords.push_back("en");
    stopWords.push_back("por");


    Preprocesor test;
    test.setText("Casa #225 en el camion 23 de el emperador corre por los prados año él tú");

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

*/

    Corpus prueba1;
    Corpus prueba2;
    Corpus prueba3;

    prueba1.setText("el gato en el establo bebe leche");
    prueba1.generateFrecuencyTable();
    prueba1.showText();
    prueba1.showFrecuencyTable();


    prueba2.setText("el caballo en el establo es de pepe");
    prueba2.generateFrecuencyTable();
    prueba2.showText();
    prueba2.showFrecuencyTable();

    prueba3.setText("pepe pecas pica papas");
    prueba3.generateFrecuencyTable();
    prueba3.showText();
    prueba3.showFrecuencyTable();




    Corpora test;

    test.addCorpus(prueba1);
    test.addCorpus(prueba2);
    test.addCorpus(prueba3);

    cout<<"BALANCENADO"<<endl;
    test.balance();
    test.getCorpora().at(0).showFrecuencyTable();
    test.getCorpora().at(1).showFrecuencyTable();
    test.getCorpora().at(2).showFrecuencyTable();

    cout<<"GLOBAL"<<endl;
    test.generateGlobal();
    test.getGlobal().showFrecuencyTable();






}
