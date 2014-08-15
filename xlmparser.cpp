#include "xlmparser.h"
#include "ui_xlmparser.h"

XLMParser::XLMParser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XLMParser)
{
    ui->setupUi(this);
    this->setWindowTitle("XML Parser");

    this->setFixedSize(this->size());


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
    QFile* auxFile;
    QXmlStreamReader::TokenType token;
    QDir dir;


    QString title;
    QString content;



    QString auxTitle;
    QString auxContent;



    title=ui->titlelineEdit->text();
    content=ui->contentlineEdit->text();



    path=QFileDialog::getOpenFileName(this,"Select Dir","~/","*.xml");





    if(!path.isEmpty())
    {
        file= new QFile(path);
        QFileInfo fileInfo(file->fileName());
        QString filename(fileInfo.fileName());

        QStringList parts = filename.split(".");


        Preprocesor pre;


        dir.mkdir("./assets/"+parts[0]);


        if(file->open(QIODevice::ReadOnly| QIODevice::Text))
        {

            QTextStream in(file);


            pre.setText(in.readAll().toStdString());
            pre.removeHtmlTagsInXML();
            pre.removeIlegalAmp();
            pre.removeSpecialcharacters();

            QXmlStreamReader xml(QString::fromStdString(pre.getText()));


            while(!xml.atEnd() && !xml.hasError())
            {
                token = xml.readNext();

                if(token == QXmlStreamReader::StartDocument)
                {
                    continue;
                }


                if(token == QXmlStreamReader::StartElement)
                {
                    if(xml.name()!=title && xml.name()!=content )
                        continue;



                    if(xml.name()==title)
                    {                        
                        xml.readNext();
                        qDebug()<<xml.text().toString();
                        auxTitle=xml.text().toString();
                        auxTitle.replace(" ","");
                        auxTitle.replace("\n","");

                    }

                    if(xml.name()==content)
                    {                        
                        xml.readNext();
                        qDebug()<<xml.text().toString();
                        auxContent=xml.text().toString();
                    }


                    auxFile = new QFile("./assets/"+parts[0]+"/"+auxTitle+".txt");

                    if(auxFile->open(QIODevice::WriteOnly| QIODevice::Text))
                    {
                        QTextStream out(auxFile);
                        out<<auxContent;
                    }
                    auxFile->close();
                    delete auxFile;

                }

            }
            QMessageBox::information(this,"Message","Sucess");

        }
        file->close();
    }
    else
    {
        QMessageBox::information(this,"Message","No XML file selected");
    }
}
