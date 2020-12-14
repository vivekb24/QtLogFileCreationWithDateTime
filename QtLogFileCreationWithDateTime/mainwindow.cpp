#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    memset(&sACmd,0,sizeof(struct aCmd));
    qDebug()<<"sizeof(struct aCmd)="<<sizeof(struct aCmd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init()
{
    sACmd.msgId=1;
    sACmd.word0=2;
    sACmd.word1=3;
}
void MainWindow::createLogFileWithDateTime()
{
    init();
    QString path= "D:/LogFiles/";

    //Current Date Time
    QFile datFile(QString(path+"%1.dat").arg(QDateTime::currentDateTime().toString("ddMMyyyy-hhmmss")));

    if (!datFile.open(QFile::WriteOnly))
    {
        qDebug()<<"Not a File";
    }else
    {
        qDebug()<<"File Created...."<<datFile.fileName();
        ui->statusBar->showMessage("File Created"+datFile.fileName(),2000);
        ui->label->setText(datFile.fileName());
        datFile.write((char*)&sACmd,sizeof(struct aCmd));
    }
    datFile.close();
}

void MainWindow::on_logFilePB_clicked()
{
    createLogFileWithDateTime();
}

void MainWindow::on_readFilePB_clicked()
{

    QFile datFile(QFileDialog::getOpenFileName(this,"LogFiles","D:/LogFiles/","*.dat"));
    if (!datFile.open(QFile::ReadOnly))
    {
        qDebug()<<"Not a File";
    }else
    {
        qDebug()<<"File Created...."<<datFile.fileName();
        ui->statusBar->showMessage("File Loaded:"+datFile.fileName(),2000);
        QByteArray  ba;
        ba.clear();
        ba= datFile.readLine(); //This function reads a line of ASCII characters from the device, up to a maximum of maxSize - 1 bytes, stores the characters in data, and returns the number of bytes read.
        qDebug()<<ba<<ba.size();

        memcpy((char*)&sACmd,ba.data(),ba.size());

        ui->listWidget->addItem("MsgID = "+QString::number(sACmd.msgId));
        ui->listWidget->addItem("word0 = "+QString::number(sACmd.word0));
        ui->listWidget->addItem("word1 = "+QString::number(sACmd.word1));
    }
}
