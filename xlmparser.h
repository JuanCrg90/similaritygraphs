#ifndef XLMPARSER_H
#define XLMPARSER_H

#include <QWidget>

namespace Ui {
class XLMParser;
}

class XLMParser : public QWidget
{
    Q_OBJECT

public:
    explicit XLMParser(QWidget *parent = 0);
    ~XLMParser();

private:
    Ui::XLMParser *ui;
};

#endif // XLMPARSER_H
