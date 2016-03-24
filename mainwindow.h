#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "corpora.h"
#include "metrics.h"
#include "preprocesor.h"
#include "barcharts.h"
#include "similaritygraph.h"
#include "about.h"
#include "xlmparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public slots:
    void load();

    void onCorporaClick(int row,int col);
    void onCorporaDoubleClick(int row,int col);

    void onCorpusClick(int row,int col);
    void onCorpusDoubleClick(int row,int col);

    void onGlobalClick();

    void onSaveGlobalClick();
    void onSaveTablesClass();
    void onSaveDocuments();
    void onSaveAll();



    void onThresholdClick();


    void onDiceClick();
    void onCosClick();
    void onJaccardClick();
    void onManhattanClick();

    void onAboutClick();
    void onXMLreaderClick();






public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //Vector donde se guardarán las stop words
    vector<string> stopWords;


    //Variables para seleccion del directorio donde estan las clases

    class directoryStructure{
    public:
        QDir dir;
        QStringList dirPathList; //Ruta completa de los directorios
        QStringList dirNameList; //Nombre del directorio (nombre de la clase)
        QFileInfoList dirList; //Información del directorio

    };

    directoryStructure *dirStructure;


    //Variables para extraer un subdirectorio
    class subDirectoryStructure{
    public:
        vector<QStringList> subDirFileList; //paths de los archivos en el subdirectorio
        vector<QStringList> fileNameList; //nombres de los archivos en el subdirectorio
    };

    subDirectoryStructure *subDirStructure;



    Corpora *corpora;


    int actualClass;

    BarCharts *barChart;
    SimilarityGraph *simGraph;


    void LoadStopWords();
    void readDirList(QString path);
    void readFileList(QString path);
    Document readDoc(QString path, QString name);

    void initCorporaTable();
    void initCorpusTable(int row,int col);
    void initCorpusFrequencyTable(int row,int col);
    void initDocumentFrequencyTable(int row,int col);


    void allocateAndCopy(vector <vector<float> > &matrix,QVector<QVector<float> > &mat );
    void plotGraph(QString title, qint64 &elapsed, QVector<QVector<float> > &mat, QVector<QVector<float> > &matClass);
    void saveTable(QFile &file,map<string, int> &ft);
    void saveDocument(QFile &file,map<string, int> &ft);






    //Designed For Debug the data
    void printMatrixValues(vector <vector<float> > &matrix);




};

#endif // MAINWINDOW_H
