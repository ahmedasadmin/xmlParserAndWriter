#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadXmlButton_clicked()
{
    QXmlStreamReader xml;
    QString filename = QFileDialog::getOpenFileName(this, "Open Xml", ".", "Xml files (*.xml)");
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
       qDebug() << "Error loading XML file.";

    xml.setDevice(&file);

    while(!xml.atEnd()){

        if (xml.isStartElement()){
            QString name = xml.name().toString();

            if(name == "object"){
                qDebug() << "[Object]====================================";
                for (int i=0; i<xml.attributes().size(); i++){
                    qDebug() << xml.attributes().at(i).name() << xml.attributes().at(i).value();
                }

            }
            if (name == "name" || name=="position" || name == "rotation" || name == "scale")
            {
                QString text = xml.readElementText();
                qDebug() << name << text;
            }
        }
        if (xml.isEndElement()){
                QString name = xml.name().toString();
                if (name=="object"){
                qDebug() << "============================================";
    }
    }
                xml.readNext();
    }
                if (xml.hasError()){
                qDebug() << "Error loading XML:" << xml.errorString();
    }
}


void MainWindow::on_saveXmlButton_clicked()
{
    QXmlStreamWriter xml;

    QString filename = QFileDialog::getSaveFileName(this, "Save Xml", ".", "Xml files (*.xml)");
    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text))
        qDebug()<< "Error saving XML file.";
    xml.setDevice(&file);
    xml.setAutoFormatting(true);
    xml.writeStartElement("contact");
    xml.writeAttribute("category", "Friend");
    xml.writeTextElement("name", "Ahmed Muhammed");
    xml.writeTextElement("age", "26");
    xml.writeTextElement("address", "15, shaik Makrem, Sohag");
    xml.writeTextElement("phone", "+2011435103336");
    xml.writeEndElement();

    xml.writeEndDocument();
}
















