#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stopWords.clear();

    ui->CorporaTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->CorpusTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->FrequencytableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



    connect(ui->LoadButton,SIGNAL(clicked()),this,SLOT(load()));
    connect(ui->CorporaTableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(onCorporaClick(int,int)));
    connect(ui->CorpusTableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(onCorpusClick(int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load()
{
    QString path;


    path=QFileDialog::getExistingDirectory(this,"Select Dir","./assets");

    if(!path.isEmpty())
    {

        //Extraer lista de directorios
        readDirList(path);


        //Extraer archivos de la lista de directorios
        //readFileListXml();


    }
    else
    {
        QMessageBox::information(this,"Message","Canceled by the user");
    }

}


void MainWindow::readDirList(QString path)
{


    dir.setPath(path);

    dirList.clear();

    dirList= dir.entryInfoList(QDir::Dirs);

    //qDebug()<<dirList.size();

    for(int i=0;i<dirList.size();i++)
    {
        if(dirList[i].fileName()!=".." && dirList[i].fileName()!=".")
        {
            dirPathList.append(dirList[i].absoluteFilePath());
            dirNameList.append(dirList[i].fileName());
        }
    }

    for(int i=0;i<dirPathList.size();i++)
    {
        //qDebug()<<"Clase"<<i;
        readFileList(dirPathList[i]);
    }


    corpora.generateCorporaFrequencyTable();
    //corpora.showCorporaFrequencyTable();

    qDebug()<<corpora.getCorpora().at(0).getCorp().size();
    corpora.getCorpora().at(0).showCorpusFrequencyTable();
    initCorporaTable();

}

void MainWindow::readFileList(QString path)
{
    QFileInfoList fileList; //Información del subdirectorio
    QStringList filePathlist; //Lista de paths de los archivos
    QStringList tempNamelist; //Lista de nombres de los archivos
    Corpus auxCorpus;


    dir.setPath(path);


    dir.setNameFilters(QStringList() << QString("*.txt"));
    fileList=dir.entryInfoList(QDir::Files);


    for(int i=0;i<fileList.size();i++)
    {
        filePathlist.append(fileList[i].absoluteFilePath());
        tempNamelist.append(fileList[i].fileName());
    }
    subDirFileList.push_back(filePathlist);
    fileNameList.push_back(tempNamelist);


    //Construyendo la clase
    for(int i=0;i<fileList.size();i++)
    {
        //qDebug()<<"Documento"<<i;
        auxCorpus.addDocument(readDoc(filePathlist[i],tempNamelist[i]));
    }

    //qDebug()<<"Inicia Generación de tabla del corpus";
    //auxCorpus.balanceCorpus();
    auxCorpus.generateCorpusFrequencyTable();
    //qDebug()<<"Termina Generación de tabla del corpus";

    //qDebug()<<"Agregando Corpus al corpora";
    corpora.addCorpus(auxCorpus);

}

Document MainWindow::readDoc(QString path,QString name)
{
    Document doc;
    Preprocesor pre;
    QFile* file;

    file= new QFile(path);

    if(file->open(QIODevice::ReadOnly| QIODevice::Text))
    {
        QTextStream in(file);

        //preprocesando
        pre.setText(in.readAll().toStdString());
        pre.removeHtmlTags();
        pre.removeUrls();
        pre.removeNumbers();
        pre.toLower();
        pre.removePunctiationMarks();

        //Creando el objeto documento
        doc.setName(name.toStdString());
        doc.setText(pre.getText());
        doc.generateFrequencyTable();
        doc.removeStopWords(stopWords);
    }
    file->close();

    return doc;
}


void MainWindow::initCorporaTable()
{
    ui->CorporaTableWidget->setRowCount(dirPathList.size());
    ui->CorporaTableWidget->setColumnCount(1);
    ui->CorporaTableWidget->setHorizontalHeaderLabels(QStringList()<<"Directory");
    ui->CorporaTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    for (int i = 0; i < dirPathList.size(); i++)
    {
        ui->CorporaTableWidget->setItem(i,0,new QTableWidgetItem(dirNameList[i]));
    }

    ui->CorporaTableWidget->resizeColumnsToContents();
}


void MainWindow::onCorporaClick(int row, int col)
{
    actualClass = row;
    initCorpusTable(row,col);
    initCorpusFrequencyTable(row,col);

}

void MainWindow::onCorpusClick(int row, int col)
{
    initDocumentFrequencyTable(row,col);

}

void MainWindow::initCorpusTable(int row, int col)
{
    qDebug()<<row<<" "<<col;

    int size=corpora.getCorpora().at(row).getCorp().size();

    ui->CorpusTableWidget->clear();
    ui->CorpusTableWidget->setRowCount(size);
    ui->CorpusTableWidget->setColumnCount(1);
    ui->CorpusTableWidget->setHorizontalHeaderLabels(QStringList()<<"Files");
    ui->CorpusTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    for (int i = 0; i < size; i++)
    {
        ui->CorpusTableWidget->setItem(i,0,new QTableWidgetItem(fileNameList[row][i]));
    }
    ui->CorpusTableWidget->resizeColumnsToContents();

}

void MainWindow::initCorpusFrequencyTable(int row, int col)
{

    map<string, int> ft = corpora.getCorpora().at(row).getCorpusFrequencyTable();
    std::map<string,int>::iterator it;
    int i=0;

    int size=ft.size();
    ui->FrequencytableWidget->clear();
    ui->FrequencytableWidget->setRowCount(size);
    ui->FrequencytableWidget->setColumnCount(2);
    ui->FrequencytableWidget->setHorizontalHeaderLabels(QStringList()<<"Word"<<"Frequency");
    ui->FrequencytableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);



    it=ft.begin();

    while(it!=ft.end())
    {

        ui->FrequencytableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(it->first)));
        ui->FrequencytableWidget->setItem(i,1,new QTableWidgetItem(QString::number(it->second)));
        it++;
        i++;
    }


    ui->FrequencytableWidget->resizeColumnsToContents();

}

void MainWindow::initDocumentFrequencyTable(int row, int col)
{
    map<string, int> ft = corpora.getCorpora().at(actualClass).getDocument(row).getFrequencyTable();
    std::map<string,int>::iterator it;
    int i=0;

    int size=ft.size();
    ui->FrequencytableWidget->clear();
    ui->FrequencytableWidget->setRowCount(size);
    ui->FrequencytableWidget->setColumnCount(2);
    ui->FrequencytableWidget->setHorizontalHeaderLabels(QStringList()<<"Word"<<"Frequency");
    ui->FrequencytableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);



    it=ft.begin();

    while(it!=ft.end())
    {

        ui->FrequencytableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(it->first)));
        ui->FrequencytableWidget->setItem(i,1,new QTableWidgetItem(QString::number(it->second)));
        it++;
        i++;
    }

    ui->FrequencytableWidget->resizeColumnsToContents();

}

