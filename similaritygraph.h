#ifndef SIMILARITYGRAPH_H
#define SIMILARITYGRAPH_H

#include <QWidget>
#include <QVector>
#include <QtAlgorithms>

#include "qcustomplot.h"

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

public slots:
    void onSaveclick();


private:
    Ui::SimilarityGraph *ui;

    QString title;
    int x,y;
    QVector < QVector <float> > mat;





};

#endif // SIMILARITYGRAPH_H
