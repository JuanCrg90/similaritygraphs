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
    prueba.generateFrequencyTable();
    prueba.showText();
    prueba.showFrequencyTable();
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

    Document prueba1;
    Document prueba2;
    Document prueba3;

    prueba1.setText("el gato en el establo bebe leche todo el año");    
    prueba1.generateFrequencyTable();
    prueba1.showText();
    prueba1.showFrequencyTable();


    prueba2.setText("el caballo en el establo es de pepe");
    prueba2.generateFrequencyTable();
    prueba2.showText();
    prueba2.showFrequencyTable();

    prueba3.setText("pepe pepe pecas pica papas en el carro");
    prueba3.generateFrequencyTable();
    prueba3.showText();
    prueba3.showFrequencyTable();

    Corpus a;

    a.addDocument(prueba1);
    a.addDocument(prueba2);
    a.addDocument(prueba3);

    a.balanceCorpus();

    a.getDocument(0).showFrequencyTable();
    a.getDocument(1).showFrequencyTable();
    a.getDocument(2).showFrequencyTable();

    a.generateCorpusFrequencyTable();
    a.showCorpusFrequencyTable();

    a.threshold(2);
    //a.getDocument(0).showFrequencyTable();
    //a.getDocument(1).showFrequencyTable();
    //a.getDocument(2).showFrequencyTable();

    a.generateCorpusFrequencyTable();
    a.showCorpusFrequencyTable();


}
