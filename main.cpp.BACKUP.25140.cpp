#include "mainwindow.h"
#include <QApplication>
#include "corpus.h"
<<<<<<< HEAD
#include "preprocesor.h"

=======
>>>>>>> 5e494dc2c34c42310b8c9bae03aae40ced4d39d4
int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/


<<<<<<< HEAD
/*
    Corpus prueba;
    prueba.setText(" &lt;br /&gt; ");
    prueba.generateFrecuencyTable();
    prueba.showText();
    prueba.showFrecuencyTable();
*/


    Preprocesor test;
    test.setText("&lt;a href=\"http://en.pan.netcom/go/out/url=http%3A%2F%2Fwww.comptiaking.com\"target=\"_blank\" rel=\"nofollow\"&gt;;http://www.comptiaking.com&lt;/a&gt;");

    cout<<test.getText()<<endl;
    cout<<"tags html"<<endl;
    test.removeHtmlTags();
    cout<<test.getText()<<endl;

    cout<<"urls"<<endl;
    test.removeUrls();


    cout<<"Punctuacion"<<endl;
    test.removePunctiationMarks();
=======


    Corpus prueba;
    prueba.setText("Los Gatos Se Comen a Los Ratones y Los osos Comen peces ");
    prueba.generateFrecuencyTable();
    prueba.showText();
    prueba.showFrecuencyTable();
>>>>>>> 5e494dc2c34c42310b8c9bae03aae40ced4d39d4






}
