#include "similaritygraph.h"
#include "ui_similaritygraph.h"

SimilarityGraph::SimilarityGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimilarityGraph)
{
    ui->setupUi(this);

    confusion = new SimilarityMatrixClasses();


    connect(ui->SaveButton,SIGNAL(clicked()),this,SLOT(onSaveclick()));
    connect(ui->ConfusionMatrixpushButton,SIGNAL(clicked()),this,SLOT(onConfusionclick()));
}

SimilarityGraph::~SimilarityGraph()
{
    delete ui;
}
QString SimilarityGraph::getTitle() const
{
    return title;
}

void SimilarityGraph::setTitle(const QString &value)
{
    title = value;
}
QVector<QVector<float> > SimilarityGraph::getMat() const
{
    return mat;
}

void SimilarityGraph::setMat(const QVector<QVector<float> > &value)
{
    mat.clear();

    x=value.size();
    y=value[0].size();

    mat.resize(value.size());

    for(int i=0;i<mat.size();i++)
    {
        mat[i].resize(value[i].size());
    }

    for(int i=0;i<mat.size();i++)
    {
        for(int j=0;j<mat[i].size();j++)
        {
            mat[i][j]=value[i][j];
        }
    }
}


QVector<QVector<float> > SimilarityGraph::getMatClass() const
{
    return matClass;
}

void SimilarityGraph::setMatClass(const QVector<QVector<float> > &value)
{
    matClass.clear();

    matClass.resize(value.size());

    for(int i=0;i<matClass.size();i++)
    {
        matClass[i].resize(value[i].size());
    }

    for(int i=0;i<matClass.size();i++)
    {
        for(int j=0;j<matClass[i].size();j++)
        {
            matClass[i][j]=value[i][j];
        }
    }
}

qint64 SimilarityGraph::getElapsed() const
{
    return elapsed;
}

void SimilarityGraph::setElapsed(const qint64 &value)
{
    elapsed = value;
}


QStringList SimilarityGraph::getDirNameList() const
{
    return dirNameList;
}

void SimilarityGraph::setDirNameList(const QStringList &value)
{
    dirNameList = value;
}

void SimilarityGraph::plot()
{
    this->setWindowTitle(title);


    if(elapsed >= 60 )
    {
        elapsed/=60.0;
        ui->Elapsedlabel->setText("Elapsed Time "+QString::number((elapsed))+" Minutes");
    }
    else
    {
        ui->Elapsedlabel->setText("Elapsed Time "+QString::number((elapsed))+" -Seconds");
    }

    // configure axis rect:
    ui->Graph->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->Graph->axisRect()->setupFullAxesBox(true);
    ui->Graph->xAxis->setLabel("x");
    ui->Graph->yAxis->setLabel("y");


    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->Graph->xAxis, ui->Graph->yAxis);
    ui->Graph->addPlottable(colorMap);

    colorMap->data()->setSize(x, y);
    colorMap->data()->setRange(QCPRange(0, x), QCPRange(0, y));
    colorMap->setInterpolate(false);

    for(int i=0;i<mat.size();i++)
    {
        for(int j=0;j<mat[i].size();j++)
        {
            colorMap->data()->setCell(j, i, mat[i][j]);
        }
    }

    colorMap->setGradient(QCPColorGradient::gpGrayscale);
    colorMap->rescaleDataRange(true);
    ui->Graph->rescaleAxes();
    ui->Graph->replot();

}

void SimilarityGraph::onSaveclick()
{
    QString path;
    QStringList list;
    path=QFileDialog::getSaveFileName(this,"Select Dir","./assets/untiled.png",tr("PNG (*.png);;JPG(*.jpg);;PDF(*.pdf)"));
    qDebug()<<path;

    list=path.split(".");
    qDebug()<<path;
    saveMatrix(list[0]);


    if(QString::compare(list[1],"png")==0)
    {
        qDebug()<<list[1];
        ui->Graph->savePng(path,x,y);
    }
    else if (QString::compare(list[1],"jpg")==0)
    {
        qDebug()<<list[1];
        ui->Graph->saveJpg(path,x,y);

    }
    else if (QString::compare(list[1],"pdf")==0)
    {
        qDebug()<<list[1];
        ui->Graph->savePdf(path,false,x,y,"Juan Carlos Ruiz González");
    }

}

void SimilarityGraph::onConfusionclick()
{
    if(confusion)
        delete confusion;
    confusion = new SimilarityMatrixClasses();

    confusion->setMatClass(matClass);
    confusion->setDirNameList(dirNameList);

    confusion->assingMatrix();

    confusion->show();


}



void SimilarityGraph::saveMatrix(QString path)
{

    QFile file( path+".csv" );

    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream out( &file );

        for(int i=0;i<mat.size();i++)
        {
            for(int j=0;j<mat[i].size();j++)
            {
                out<<mat[i][j];

                if(j<mat[i].size()-1)
                {
                    out<<",";
                }
            }
            out<<endl;
        }
    }

    file.close();

}


