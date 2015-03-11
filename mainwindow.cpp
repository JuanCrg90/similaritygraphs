#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->setFixedSize(this->size());

    stopWords.clear();
    dirStructure=new directoryStructure();
    subDirStructure= new subDirectoryStructure();
    corpora = new Corpora();

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
    connect(ui->SaveGlobalTablepushButton,SIGNAL(clicked()),this,SLOT(onSaveGlobalClick()));
    connect(ui->SaveTableClasspushButton,SIGNAL(clicked()),this,SLOT(onSaveTablesClass()));
    connect(ui->SaveDocspushButton,SIGNAL(clicked()),this,SLOT(onSaveDocuments()));
    connect(ui->SaveAllpushButton,SIGNAL(clicked()),this,SLOT(onSaveAll()));



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

    ui->CorporaTableWidget->clear();
    ui->CorpusTableWidget->clear();
    ui->FrequencytableWidget->clear();

    ui->CorporaTableWidget->clearContents();
    ui->CorpusTableWidget->clearContents();
    ui->FrequencytableWidget->clearContents();

    ui->CorporaTableWidget->setRowCount(0);
    ui->CorpusTableWidget->setRowCount(0);
    ui->FrequencytableWidget->setRowCount(0);


    ui->CorporaTableWidget->setHorizontalHeaderLabels(QStringList()<<"Directory");
    ui->CorpusTableWidget->setHorizontalHeaderLabels(QStringList()<<"Files");
    ui->FrequencytableWidget->setHorizontalHeaderLabels(QStringList()<<"Word"<<"Frequency");


    if(dirStructure)
        delete dirStructure;

    if(subDirStructure)
        delete subDirStructure;

    if(corpora)
        delete corpora;

    dirStructure = new directoryStructure();
    subDirStructure = new subDirectoryStructure();
    corpora = new Corpora();

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


    dirStructure->dir.setPath(path);
    dirStructure->dirList.clear();
    dirStructure->dirList = dirStructure->dir.entryInfoList(QDir::Dirs);

    /*
    dir.setPath(path);
    qDebug()<<dir.path();
    dirList.clear();    
    dirList= dir.entryInfoList(QDir::Dirs);
*/



    for(int i=0;i<dirStructure->dirList.size();i++)
    {
        if(dirStructure->dirList[i].fileName()!=".." && dirStructure->dirList[i].fileName()!=".")
        {
            dirStructure->dirPathList.append(dirStructure->dirList[i].absoluteFilePath());
            dirStructure->dirNameList.append(dirStructure->dirList[i].fileName());
        }
    }

    for(int i=0;i<dirStructure->dirPathList.size();i++)
    {
        //qDebug()<<"Clase"<<i;
        readFileList(dirStructure->dirPathList[i]);
    }


    corpora->generateCorporaFrequencyTable();
    //corpora->showCorporaFrequencyTable();

    //qDebug()<<corpora->getCorpora().at(0).getCorp().size();
    //corpora->getCorpora().at(0).showCorpusFrequencyTable();
    initCorporaTable();

}

void MainWindow::readFileList(QString path)
{
    QFileInfoList fileList; //Información del subdirectorio
    QStringList filePathlist; //Lista de paths de los archivos
    QStringList tempNamelist; //Lista de nombres de los archivos
    Corpus auxCorpus;



    dirStructure->dir.setPath(path);


    dirStructure->dir.setNameFilters(QStringList() << QString("*.txt"));
    fileList=dirStructure->dir.entryInfoList(QDir::Files);


    for(int i=0;i<fileList.size();i++)
    {
        filePathlist.append(fileList[i].absoluteFilePath());
        tempNamelist.append(fileList[i].fileName());
    }
    subDirStructure->subDirFileList.push_back(filePathlist);
    subDirStructure->fileNameList.push_back(tempNamelist);


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
    corpora->addCorpus(auxCorpus);

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
    ui->CorporaTableWidget->setRowCount(dirStructure->dirPathList.size());
    ui->CorporaTableWidget->setColumnCount(1);
    ui->CorporaTableWidget->setHorizontalHeaderLabels(QStringList()<<"Directory");
    ui->CorporaTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    for (int i = 0; i < dirStructure->dirPathList.size(); i++)
    {
        ui->CorporaTableWidget->setItem(i,0,new QTableWidgetItem(dirStructure->dirNameList[i]));
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


    map<string, int> ft=corpora->getCorpora().at(row).getCorpusFrequencyTable();

    QVector<QString> labels;
    QVector<int> data;

    std::map<string,int>::iterator it;


    for(it = ft.begin(); it != ft.end(); it++ )
    {
        labels.push_back(QString::fromStdString(it->first));
        data.push_back( it->second );
    }

    barChart= new BarCharts();

    barChart->setName(dirStructure->dirNameList[row]);
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
    map<string, int> ft = corpora->getCorpora().at(actualClass).getDocument(row).getFrequencyTable();

    QVector<QString> labels;
    QVector<int> data;

    std::map<string,int>::iterator it;


    for(it = ft.begin(); it != ft.end(); it++ )
    {
        labels.push_back(QString::fromStdString(it->first));
        data.push_back( it->second );
    }

    barChart= new BarCharts();


    barChart->setName(subDirStructure->fileNameList[actualClass][row]);
    barChart->setLabels(labels);
    barChart->setData(data);
    barChart->plot();
    barChart->show();
}

void MainWindow::onGlobalClick()
{
    map<string, int> ft = corpora->getCorporaFrequencyTable();
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

void MainWindow::onSaveGlobalClick()
{
    QString path=QFileDialog::getSaveFileName(this,"Select Dir","./assets/untiled.csv",tr("csv (*.csv)"));;
    map<string, int> ft = corpora->getCorporaFrequencyTable();
    std::map<string,int>::iterator it;

    QFile file( path );

    saveTable(file,ft);
}

void MainWindow::onSaveTablesClass()
{
    QString path;
    QFile file;

    path=QFileDialog::getExistingDirectory(this,"Select Directory");

    int size=dirStructure->dirNameList.size();

    for(int i=0;i<size;i++)
    {
        file.setFileName(path+"/"+dirStructure->dirNameList[i]+".csv");

        map<string, int> ft = corpora->getCorpora().at(i).getCorpusFrequencyTable();

        saveTable(file,ft);
    }
}

void MainWindow::onSaveDocuments()
{
    QString path;
    QString newPath;
    QString docPath;
    QFile file;
    map<string, int> ft;
    unsigned int documentSize;
    unsigned int size;

    //Seleccionar directorio para crear los subDirectorios
    path=QFileDialog::getExistingDirectory(this,"Select Directory");

    //Crear Directorio DocumentFT
    newPath =path+"/DocumentFT";
    QDir().mkdir(newPath);

    //Crear Directorios de las clases dentro de DocumentFT
    size=dirStructure->dirNameList.size();

    for(unsigned int i=0; i< size;i++ )
    {
        //qDebug()<<newPath+"/"+dirStructure->dirNameList[i];
        QDir().mkdir(newPath+"/"+dirStructure->dirNameList[i]);

        //Guardando Documentos correspondientes al Directorio creado
        documentSize=corpora->getCorpus(i).getCorp().size();
        for(unsigned int j=0;j<documentSize;j++)
        {            
            docPath = QString::fromStdString(corpora->getCorpus(i).getDocument(j).getName());

            QStringList name=docPath.split(".");
            docPath= name[0]+".csv";

            //qDebug()<<newPath+"/"+dirStructure->dirNameList[i]+"/"+docPath;

            file.setFileName(newPath+"/"+dirStructure->dirNameList[i]+"/"+docPath);
            ft=corpora->getCorpus(i).getDocument(j).getFrequencyTable();
            saveTable(file,ft);
        }

    }

}

void MainWindow::onSaveAll()
{
    QString path;
    QString newPath;
    QString docPath;
    map<string, int> ft;
    QFile file;
    unsigned int documentSize;
    unsigned int size;


    path=QFileDialog::getExistingDirectory(this,"Select Directory");


    size=dirStructure->dirNameList.size();

    //Documentos

    //Crear Directorio DocumentFT
    newPath =path+"/DocumentFT";
    QDir().mkdir(newPath);

    for(unsigned int i=0; i< size;i++ )
    {
        //qDebug()<<newPath+"/"+dirStructure->dirNameList[i];
        QDir().mkdir(newPath+"/"+dirStructure->dirNameList[i]);

        //Guardando Documentos correspondientes al Directorio creado
        documentSize=corpora->getCorpus(i).getCorp().size();
        for(unsigned int j=0;j<documentSize;j++)
        {
            docPath = QString::fromStdString(corpora->getCorpus(i).getDocument(j).getName());

            QStringList name=docPath.split(".");
            docPath= name[0]+".csv";

            //qDebug()<<newPath+"/"+dirStructure->dirNameList[i]+"/"+docPath;

            file.setFileName(newPath+"/"+dirStructure->dirNameList[i]+"/"+docPath);
            ft=corpora->getCorpus(i).getDocument(j).getFrequencyTable();
            saveTable(file,ft);
        }

    }

    //Guardando tablas  de las clases
    for(int i=0;i<size;i++)
    {
        file.setFileName(path+"/"+dirStructure->dirNameList[i]+".csv");

        ft = corpora->getCorpora().at(i).getCorpusFrequencyTable();

        saveTable(file,ft);
    }

    //Guardando  la tabla global del corpus
    ft = corpora->getCorporaFrequencyTable();


    file.setFileName(path+"/Global.csv");

    saveTable(file,ft);


}

void MainWindow::onThresholdClick()
{
    QString value = ui->ThresholdLineEdit->text();
    int th = value.toInt();
    corpora->threshold(th);
    corpora->threshold(th);
    ui->FrequencytableWidget->clear();
    ui->FrequencytableWidget->clearContents();
    ui->FrequencytableWidget->setRowCount(0);
    ui->FrequencytableWidget->setHorizontalHeaderLabels(QStringList()<<"Word"<<"Frequency");
}

void MainWindow::onDiceClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    vector <vector<float> > matrixClass;
    QVector<QVector<float> > mat;
    QVector<QVector<float> > matClass;

    QElapsedTimer timer;
    timer.start();

    qDebug()<<"Dice";
    matrix=met.generateDice(*corpora,DOCS);
    matrixClass=met.generateDice(*corpora,CLASS);



    qDebug()<<"Aplicando negativo";
    matrix=met.negativeMatrix(matrix,1.0);    




    //printMatrixValues(matrix);
    //printMatrixValues(matrixClass);


    allocateAndCopy(matrix,mat);
    allocateAndCopy(matrixClass,matClass);

    qint64 elapsed = timer.elapsed()/1000.0;    

    plotGraph(QString("Dice Metric"),elapsed,mat,matClass);

}

void MainWindow::onCosClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    vector <vector<float> > matrixClass;
    QVector<QVector<float> > mat;
    QVector<QVector<float> > matClass;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Cos";

    matrix=met.generateCos(*corpora,DOCS);
    matrixClass=met.generateCos(*corpora,CLASS);

    qDebug()<<"Aplicando negativo";
    matrix=met.negativeMatrix(matrix,1.0);

    //printMatrixValues(matrixClass);

    allocateAndCopy(matrix,mat);
    allocateAndCopy(matrixClass,matClass);

    qint64 elapsed = timer.elapsed()/1000.0;

    plotGraph(QString("Cosine Metric"),elapsed,mat,matClass);

}

void MainWindow::onJaccardClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    vector <vector<float> > matrixClass;
    QVector<QVector<float> > mat;
    QVector<QVector<float> > matClass;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Jaccard";
    matrix=met.generateJaccard(*corpora,DOCS);
    matrixClass=met.generateJaccard(*corpora,CLASS);

    qDebug()<<"Aplicando negativo";
    matrix=met.negativeMatrix(matrix,1.0);

    printMatrixValues(matrixClass);
    allocateAndCopy(matrix,mat);
    allocateAndCopy(matrixClass,matClass);

    qint64 elapsed = timer.elapsed()/1000.0;
    plotGraph(QString("Jaccard Metric"),elapsed,mat,matClass);

}

void MainWindow::onManhattanClick()
{
    Metrics met;
    vector <vector<float> > matrix;
    vector <vector<float> > matrixClass;
    QVector<QVector<float> > mat;
    QVector<QVector<float> > matClass;

    QElapsedTimer timer;
    timer.start();


    qDebug()<<"Manhattan";

    matrix=met.generateManhatan(*corpora,DOCS);
    matrixClass=met.generateManhatan(*corpora,CLASS);

    qDebug()<<"Normalizando";
    matrix = met.normalizeMatrix(matrix);
    matrixClass = met.normalizeMatrix(matrixClass);

    //qDebug()<<"Aplicando negativo";
    matrixClass=met.negativeMatrix(matrixClass,1.0);


    //printMatrixValues(matrixClass);
    allocateAndCopy(matrix,mat);
    allocateAndCopy(matrixClass,matClass);


    qint64 elapsed = timer.elapsed()/1000.0;

    plotGraph(QString("Manhattan Metric"),elapsed,mat,matClass);
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

    int size=corpora->getCorpora().at(row).getCorp().size();

    ui->CorpusTableWidget->clear();    
    ui->CorpusTableWidget->setRowCount(size);    
    ui->CorpusTableWidget->setColumnCount(1);
    ui->CorpusTableWidget->setHorizontalHeaderLabels(QStringList()<<"Files");
    ui->CorpusTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    for (int i = 0; i < size; i++)
    {
        ui->CorpusTableWidget->setItem(i,0,new QTableWidgetItem(subDirStructure->fileNameList[row][i]));
    }
    ui->CorpusTableWidget->resizeColumnsToContents();

}

void MainWindow::initCorpusFrequencyTable(int row, int col)
{

    map<string, int> ft = corpora->getCorpora().at(row).getCorpusFrequencyTable();
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
    map<string, int> ft = corpora->getCorpora().at(actualClass).getDocument(row).getFrequencyTable();
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

void MainWindow::allocateAndCopy(vector<vector<float> > &matrix, QVector<QVector<float> > &mat)
{
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
}

void MainWindow::plotGraph(QString title, qint64 &elapsed, QVector<QVector<float> > &mat,QVector<QVector<float> > &matClass)
{

    qDebug()<<"Graficando";
    simGraph = new SimilarityGraph();
    simGraph->setTitle(title);
    simGraph->setElapsed(elapsed);
    simGraph->setMat(mat);
    simGraph->setMatClass(matClass);
    simGraph->setDirNameList(dirStructure->dirNameList);
    simGraph->plot();
    simGraph->show();

}

void MainWindow::saveTable(QFile &file, map<string, int> &ft)
{
    std::map<string,int>::iterator it;

    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream out( &file );

        it=ft.begin();

        while(it!=ft.end())
        {
            out<<QString::fromStdString(it->first)<<","<<QString::number(it->second)<<endl;
            it++;
        }
    }

    file.close();
}


void MainWindow::printMatrixValues(vector<vector<float> > &matrix)
{
    qDebug()<<"Imprimiendo";
    for(unsigned int i=0;i<matrix.size();i++)
    {
        for(unsigned int j=0;j<matrix.size();j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

}

