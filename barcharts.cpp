#include "barcharts.h"
#include "ui_barcharts.h"

BarCharts::BarCharts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BarCharts)
{
    ui->setupUi(this);
}


BarCharts::~BarCharts()
{
    delete ui;
}

void BarCharts::setLabels(const QVector<QString> &value)
{
    labels.resize(value.size());
    qCopy(value.begin(),value.end(),labels.begin());
}

void BarCharts::setData(const QVector<int> &value)
{
    data.resize(value.size());
    qCopy(value.begin(),value.end(),data.begin());

}

void BarCharts::setName(const QString &value)
{
    name = value;
}


void BarCharts::plot()
{
    QCPBars *myBars = new QCPBars(ui->Graph->xAxis, ui->Graph->yAxis);
    this->setWindowTitle(name);
    ui->Graph->addPlottable(myBars);

    QVector<double> ticks;

    ticks.resize(labels.size());

    for(int i=0;i<ticks.size();i++)
    {
        ticks[i]=i;
    }


    ui->Graph->xAxis->setAutoTicks(false);
    ui->Graph->xAxis->setAutoTickLabels(false);
    ui->Graph->xAxis->setTickVector(ticks);
    ui->Graph->xAxis->setTickVectorLabels(labels);
    ui->Graph->xAxis->setTickLabelRotation(90);
    ui->Graph->xAxis->setSubTickCount(0);
    ui->Graph->xAxis->setTickLength(0, 4);
    ui->Graph->xAxis->grid()->setVisible(true);

    ui->Graph->yAxis->setPadding(5); // a bit more space to the left border
    ui->Graph->yAxis->setLabel("Frequency");
    ui->Graph->yAxis->grid()->setSubGridVisible(true);


    myBars->setData(ticks, data);


    ui->Graph->rescaleAxes();
    ui->Graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->Graph->replot();

}




