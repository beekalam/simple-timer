#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtDebug>
#include <QTextStream>
#include <string>
#include <cstdio>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    setWindowTitle(tr("Analog clock"));
//    resize(200,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnStart_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    this->seconds = ui->spinBox->value() * 60;
    timer->start(1000);
}

void MainWindow::timerUpdate()
{
    qDebug() << " in timer update" << endl;
    this->seconds--;
    qDebug() << "std string is: " << this->timeString();
    ui->textEdit->setText(this->timeString());
    setWindowTitle(this->timeString());
}

void MainWindow::paintEvent(QPaintEvent *event)
{
}

QString MainWindow::timeString()
{
    int hour = 0;
    int minute = 0;
    int seconds = this->seconds;
    if(seconds >= 3600){
        hour = seconds / 3600;
        seconds = seconds % 3600;
    }
    if(seconds >=60){
        minute = seconds / 60;
        seconds = seconds % 60;
    }
    char buff[50];
    sprintf(buff,"%.2d:%.2d:%.2d",hour,minute,seconds);
    std::string s(buff);
    return QString::fromStdString(s);
}


