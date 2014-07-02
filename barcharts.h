#ifndef BARCHARTS_H
#define BARCHARTS_H

#include <QWidget>
#include <QVector>
#include <QtAlgorithms>

#include "qcustomplot.h"


namespace Ui {
class BarCharts;
}

class BarCharts : public QWidget
{
    Q_OBJECT

public:
    explicit BarCharts(QWidget *parent = 0);





    ~BarCharts();


    void setLabels(const QVector<QString> &value);
    void setData(const QVector<int> &value);

    void setName(const QString &value);


    void plot();



private:
    Ui::BarCharts *ui;
    QString name;
    QVector<QString> labels;
    QVector<double>data;
};

#endif // BARCHARTS_H
