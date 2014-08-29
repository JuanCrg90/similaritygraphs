#ifndef SIMILARITYGRAPH_H
#define SIMILARITYGRAPH_H

#include <QWidget>
#include <QVector>
#include <QtAlgorithms>

#include "qcustomplot.h"
#include "similaritymatrixclasses.h"

namespace Ui {
class SimilarityGraph;
}

class SimilarityGraph : public QWidget
{
    Q_OBJECT

public:
    explicit SimilarityGraph(QWidget *parent = 0);
    ~SimilarityGraph();

    QString getTitle() const;
    void setTitle(const QString &value);

    QVector<QVector<float> > getMat() const;
    void setMat(const QVector<QVector<float> > &value);

    void plot();

    qint64 getElapsed() const;
    void setElapsed(const qint64 &value);

    QVector<QVector<float> > getMatClass() const;
    void setMatClass(const QVector<QVector<float> > &value);

    QStringList getDirNameList() const;
    void setDirNameList(const QStringList &value);

public slots:
    void onSaveclick();
    void onConfusionclick();


private:
    Ui::SimilarityGraph *ui;



    QString title;
    int x,y;
    QVector < QVector <float> > mat;
    QVector < QVector <float> > matClass;

    QStringList dirNameList;


    qint64 elapsed;




    SimilarityMatrixClasses *confusion;

    void saveMatrix(QString path);





};

#endif // SIMILARITYGRAPH_H
