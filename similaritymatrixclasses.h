#ifndef SIMILARITYMATRIXCLASSES_H
#define SIMILARITYMATRIXCLASSES_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class SimilarityMatrixClasses;
}

class SimilarityMatrixClasses : public QDialog
{
    Q_OBJECT

public:
    explicit SimilarityMatrixClasses(QWidget *parent = 0);
    ~SimilarityMatrixClasses();

    void assingMatrix();


    QVector<QVector<float> > getMatClass() const;
    void setMatClass(const QVector<QVector<float> > &value);

    QStringList getDirNameList() const;
    void setDirNameList(const QStringList &value);

private:
    Ui::SimilarityMatrixClasses *ui;

    QStringList copyReverse(QStringList &dirNameList);

    QVector < QVector <float> > matClass;
    QStringList dirNameList;

};

#endif // SIMILARITYMATRIXCLASSES_H
