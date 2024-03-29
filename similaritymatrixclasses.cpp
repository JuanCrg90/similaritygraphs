#include "similaritymatrixclasses.h"
#include "ui_similaritymatrixclasses.h"


SimilarityMatrixClasses::SimilarityMatrixClasses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimilarityMatrixClasses)
{
    ui->setupUi(this);

    this->setWindowTitle("Confusion Matrix");

    connect(ui->SavepushButton,SIGNAL(clicked()),this,SLOT(onSaveClick()));

}

SimilarityMatrixClasses::~SimilarityMatrixClasses()
{
    delete ui;
}

void SimilarityMatrixClasses::assingMatrix()
{
    unsigned int size = matClass.size();

    ui->ConfusionMatrixtableWidget->setRowCount(size);
    ui->ConfusionMatrixtableWidget->setColumnCount(size);

    ui->ConfusionMatrixtableWidget->setHorizontalHeaderLabels(dirNameList);
    dirNameList.reserve(dirNameList.size());
    ui->ConfusionMatrixtableWidget->setVerticalHeaderLabels(copyReverse(dirNameList));



    for(unsigned int i=0;i<size;i++)
    {
        for(unsigned int j=0;j<size;j++)
        {
            ui->ConfusionMatrixtableWidget->setItem(i,j,new QTableWidgetItem(QString::number(matClass[i][j])));
        }
    }
}
QVector<QVector<float> > SimilarityMatrixClasses::getMatClass() const
{
    return matClass;
}

void SimilarityMatrixClasses::setMatClass(const QVector<QVector<float> > &value)
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
QStringList SimilarityMatrixClasses::getDirNameList() const
{
    return dirNameList;
}

void SimilarityMatrixClasses::setDirNameList(const QStringList &value)
{
    dirNameList = value;
}

QStringList SimilarityMatrixClasses::copyReverse(QStringList &dirNameList)
{
    QStringList result;

    for(int i=dirNameList.size()-1;i>=0;i--)
        result.append(dirNameList[i]);

    return result;

}


void SimilarityMatrixClasses::onSaveClick()
{

    QString path=QFileDialog::getSaveFileName(this,"Select Dir","./assets/untiled.csv",tr("csv (*.csv)"));;

    QFile file( path);

    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream out( &file );

        for(int i=0;i<matClass.size();i++)
        {
            for(int j=0;j<matClass[i].size();j++)
            {
                out<<matClass[i][j];

                if(j<matClass[i].size()-1)
                {
                    out<<",";
                }
            }
            out<<endl;
        }
    }

    file.close();
}
