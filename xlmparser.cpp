#include "xlmparser.h"
#include "ui_xlmparser.h"

XLMParser::XLMParser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XLMParser)
{
    ui->setupUi(this);


    connect(ui->LoadButton,SIGNAL(clicked()),this,SLOT(onLoadClick()));
}

XLMParser::~XLMParser()
{
    delete ui;
}

void XLMParser::onLoadClick()
{
    QString path;
    QFile* file;
    QXmlStreamReader::TokenType token;



    path=QFileDialog::getOpenFileName(this,"Select Dir","~/","*.xml");


    if(!path.isEmpty())
    {
        file= new QFile(path);

        if(file->open(QIODevice::ReadOnly| QIODevice::Text))
        {

            QXmlStreamReader xml(file);


            while(!xml.atEnd() && !xml.hasError())
            {
                token = xml.readNext();

                if(token == QXmlStreamReader::StartDocument)
                {
                    continue;
                }


                if(token == QXmlStreamReader::StartElement)
                {
                    if(xml.name()!="unique_id" && xml.name()!="review_text" )
                        continue;

                    if(xml.name()=="unique_id")
                    {
                        xml.readNext();
                        qDebug()<<xml.text().toInt();
                    }

                    if(xml.name()=="review_text")
                    {
                        xml.readNext();
                        qDebug()<<xml.text().toString();
                    }
                }



            }










        }
        file->close();
    }
    else
    {
        QMessageBox::information(this,"Message","No XML file selected");
    }
}
