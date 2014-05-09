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


    Preprocesor test;
    test.setText("220 &lt;a href=\"http://en.pan.netcom/go/out/url=http%3A%2F%2Fwww.comptiaking.com\"target=\"_blank\" rel=\"nofollow\"&gt;;http://www.comptiaking.com&lt;/a&gt; AAASSEFDSDFDFSFGDF 290 ººº");

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





}
