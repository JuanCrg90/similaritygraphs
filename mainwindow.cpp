#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->setFixedSize(this->size());

    stopWords.clear();

    ui->CorporaTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->CorpusTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->FrequencytableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



    connect(ui->LoadButton,SIGNAL(clicked()),this,SLOT(load()));

    connect(ui->CorporaTableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(onCorporaClick(int,int)));
    connect(ui->CorporaTableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(onCorporaDoubleClick(int,int)));

    connect(ui->CorpusTableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(onCorpusClick(int,int)));    
    connect(ui->CorpusTableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(onCorpusDoubleClick(int,int)));

    connect(ui->GlobalCorporaButton,SIGNAL(clicked()),this,SLOT(onGlobalClick()));

    connect(ui->ThresholdPushButton,SIGNAL(clicked()),this,SLOT(onThresholdClick()));


    connect(ui->DiceButton,SIGNAL(clicked()),this,SLOT(onDiceClick()));
    connect(ui->CosButton,SIGNAL(clicked()),this,SLOT(onCosClick()));
    connect(ui->JaccardButton,SIGNAL(clicked()),this,SLOT(onJaccardClick()));
    connect(ui->ManhattanButton,SIGNAL(clicked()),this,SLOT(onManhattanClick()));


    //Toolbar
    connect(ui->actionClose,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(onAboutClick()));
    connect(ui->actionXML_to_Dataset,SIGNAL(triggered(bool)),this,SLOT(onXMLreaderClick()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadStopWords()
{
    QString path;
    QFile* file;
    QElapsedTimer timer;


    stopWords.clear();


    path=QFileDialog::getOpenFileName(this,"Select Dir","./assets/stopWords","*.txt");
    timer.start();

    if(!path.isEmpty())
    {
        file= new QFile(path);

        if(file->open(QIODevice::ReadOnly| QIODevice::Text))
        {
            QTextStream in(file);

            do
            {
                stopWords.push_back(in.readLine().toStdString());
            }while(!in.atEnd());
        }
        file->close();
    }
    else
    {
        QMessageBox::information(this,"Message","No Stop words selected");
    }

    qDebug()<<timer.elapsed()/1000.0;
}

void MainWindow::load()
{
    QString path;
    QElapsedTimer timer;
    int reply;


    corpora.clear();

    dirPathList.clear();
    dirNameList.clear();
    dirList.clear();



    reply=QMessageBox::question(this,"Message","Do you want remove the Stop words?");

    if(reply==QMessageBox::Yes)
    {
        LoadStopWords();
    }


    path=QFileDialog::getExistingDirectory(this,"Select Dir","./assets");

    timer.start();

    if(!path.isEmpty())
    {


        //Extraer lista de directorios
        readDirList(path);
        qDebug()<<timer.elapsed()/1000.0;


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

    //qDebug()<<corpora.getCorpora().at(0).getCorp().size();
    //corpora.getCorpora().at(0).showCorpusFrequencyTable();
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

void MainWindow::onCorporaDoubleClick(int row, int col)
{


    map<string, int> ft=corpora.getCorpora().at(row).getCorpusFrequencyTable();

    QVector<QString> labels;
    QVector<int> data;

    std::map<string,int>::iterator it;


    for(it = ft.begin(); it != ft.end(); it++ )
    {
        labels.push_back(QString::fromStdString(it->first));
        data.push_back( it->second );
    }

    barChart= new BarCharts();

    barChart->setName(dirNameList[row]);
    barChart->setLabels(labels);
    barChart->setData(data);
    barChart->plot();
    barChart->show();




}

void MainWindow::onCorpusClick(int row, int col)
{
    initDocumentFrequencyTable(row,col);

}

void MainWindow::onCorpusDoubleClick(int row, int col)
{
    map<string, int> ft = corpora.getCorpora().at(actualClass).getDocument(row).getFrequencyTable();

    QVector<QString> labels;
    QVector<int> data;

    std::map<string,int>::iterator it;


    for(it = ft.begin(); it != ft.end(); it++ )
    {
        labels.push_back(QString::fromStdString(it->first));
        data.push_back( it->second );
    }

    barChart= new BarCharts();


    barChart->setName(fileNameList[actualClass][row]);
    barChart->setLabels(labels);
    barChart->setData(data);
    barChart->plot();
    barChart->show();
}

void MainWindow::onGlobalClick()
{
    map<string, int> ft = corpora.getCorporaFrequencyTable();
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

void MainWindow::onThresholdClick()
{
    QString value = ui->ThresholdLineEdit->text();
    int th = value.toInt();
    corpora.threshold(th);
    ui->FrequencytableWidget->clear();
}

void MainWindow::onDiceClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    QVector<QVector<float> > mat;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Dice";
    matrix=met.generateDice(corpora);

    qDebug()<<"Aplicando negativo";
    matrix=met.negativeMatrix(matrix,1.0);

/*
    qDebug()<<"Imprimiendo";
    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
*/

    mat.resize(matrix.size());

    for(unsigned int i=0;i<matrix.size();i++)
    {
      mat[i].resize(matrix[i].size());
    }

    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            mat[i][j]=matrix[i][j];
        }
    }

    qint64 elapsed = timer.elapsed()/1000.0;

    if(elapsed >= 60 )
    {
        elapsed/=60.0;
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" Minutes");
    }
    else
    {
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" -Seconds");
    }

    qDebug()<<"Graficando";
    simGraph = new SimilarityGraph();
    simGraph->setTitle("Dice Metric");
    simGraph->setMat(mat);
    simGraph->plot();
    simGraph->show();


}




void MainWindow::onCosClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    QVector<QVector<float> > mat;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Cos";

    matrix=met.generateCos(corpora);
    qDebug()<<"Aplicando negativo";
    matrix=met.negativeMatrix(matrix,1.0);
/*
    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
*/

    mat.resize(matrix.size());

    for(unsigned int i=0;i<matrix.size();i++)
    {
      mat[i].resize(matrix[i].size());
    }

    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            mat[i][j]=matrix[i][j];
        }
    }

    qint64 elapsed = timer.elapsed()/1000.0;

    if(elapsed >= 60 )
    {
        elapsed/=60.0;
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" Minutes");
    }
    else
    {
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" -Seconds");
    }

    qDebug()<<"Graficando";
    simGraph = new SimilarityGraph();
    simGraph->setTitle("Cosine Metric");
    simGraph->setMat(mat);
    simGraph->plot();
    simGraph->show();


}

void MainWindow::onJaccardClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    QVector<QVector<float> > mat;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Jaccard";

    matrix=met.generateJaccard(corpora);
    qDebug()<<"Aplicando negativo";
    matrix=met.negativeMatrix(matrix,1.0);
/*
    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
*/

    mat.resize(matrix.size());

    for(unsigned int i=0;i<matrix.size();i++)
    {
      mat[i].resize(matrix[i].size());
    }

    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            mat[i][j]=matrix[i][j];
        }
    }

    qint64 elapsed = timer.elapsed()/1000.0;

    if(elapsed >= 60 )
    {
        elapsed/=60.0;
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" Minutes");
    }
    else
    {
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" -Seconds");
    }

    qDebug()<<"Graficando";
    simGraph = new SimilarityGraph();
    simGraph->setTitle("Jaccard Metric");
    simGraph->setMat(mat);
    simGraph->plot();
    simGraph->show();

}

void MainWindow::onManhattanClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    QVector<QVector<float> > mat;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Manhattan";

    matrix=met.generateManhatan(corpora);

    //qDebug()<<"Normalizando";
    //matrix = met.normalizeMatrix(matrix);
    //qDebug()<<"Aplicando negativo";
    //matrix=met.negativeMatrix(matrix,1.0);

/*
    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
*/

    mat.resize(matrix.size());

    for(unsigned int i=0;i<matrix.size();i++)
    {
      mat[i].resize(matrix[i].size());
    }

    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            mat[i][j]=matrix[i][j];
        }
    }

    qint64 elapsed = timer.elapsed()/1000.0;

    if(elapsed >= 60 )
    {
        elapsed/=60.0;
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" Minutes");
    }
    else
    {
        QMessageBox::information(this,"Message","Elapsed Time "+QString::number((elapsed))+" -Seconds");
    }

    qDebug()<<"Graficando";
    simGraph = new SimilarityGraph();
    simGraph->setTitle("Manhattan Metric");
    simGraph->setMat(mat);
    simGraph->plot();
    simGraph->show();
}

void MainWindow::onAboutClick()
{
    About *aboutWidget;
    aboutWidget = new About();
    aboutWidget->show();
}

void MainWindow::onXMLreaderClick()
{
    XLMParser *xmlwidget;
    xmlwidget = new XLMParser();
    xmlwidget->show();

}



void MainWindow::initCorpusTable(int row, int col)
{
    //qDebug()<<row<<" "<<col;

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

