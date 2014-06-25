#include "mainwindow.h"
#include <QApplication>
#include "corpora.h"


#include "metrics.h"


int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/
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
    Document prueba4;
    Document prueba5;
    Document prueba6;

    //cout<<"Grupo 1"<<endl;

    prueba1.setText("el gato en el establo bebe leche todo el año");    
    prueba1.generateFrequencyTable();
    /*prueba1.showText();
    prueba1.showFrequencyTable();*/


    prueba2.setText("el gato en el establo bebe leche todo el dia");
    prueba2.generateFrequencyTable();
    /*prueba2.showText();
    prueba2.showFrequencyTable();*/

    prueba3.setText("pepe pepe pecas pica papas en el carro");
    prueba3.generateFrequencyTable();
    /*prueba3.showText();
    prueba3.showFrequencyTable();*/


    //cout<<"Grupo 2"<<endl;

    prueba4.setText("Documento 1 Corpus 2");
    prueba4.generateFrequencyTable();
    /*prueba4.showText();
    prueba4.showFrequencyTable();*/

    prueba5.setText("Caso para el documento numero 2 Corpus 2");
    prueba5.generateFrequencyTable();
    /*prueba5.showText();
    prueba5.showFrequencyTable();*/

    prueba6.setText("Documento 3 en el Corpus 2");
    prueba6.generateFrequencyTable();
    /*prueba6.showText();
    prueba6.showFrequencyTable();*/

    Corpus a,b;
    Corpora corpora;

    a.addDocument(prueba1);
    a.addDocument(prueba2);
    a.addDocument(prueba3);

    b.addDocument(prueba4);
    b.addDocument(prueba5);
    b.addDocument(prueba6);

    a.balanceCorpus();
    b.balanceCorpus();
/*
    a.getDocument(0).showFrequencyTable();
    a.getDocument(1).showFrequencyTable();
    a.getDocument(2).showFrequencyTable();

    b.getDocument(0).showFrequencyTable();
    b.getDocument(1).showFrequencyTable();
    b.getDocument(2).showFrequencyTable();

    a.showCorpusFrequencyTable();
    b.showCorpusFrequencyTable();
*/
    corpora.addCorpus(a);
    corpora.addCorpus(b);

    Metrics met;
    vector<vector<float> > matrix;


    matrix=met.generateManhatan(corpora);


    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout <<endl;
    matrix=met.generateDice(corpora);


    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout <<endl;
    matrix=met.generateCos(corpora);


    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout <<endl;
    matrix=met.generateJaccard(corpora);


    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }



}
