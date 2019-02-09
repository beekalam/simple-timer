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
    setTimeValue("00:00:00");
//    setWindowTitle(tr("Analog clock"));
//    resize(200,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnStart_clicked()
{
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    setSeconds(ui->spinBox->value() * 60);
    this->timer->start(1000);
    ui->BtnStart->setEnabled(false);
    ui->BtnStop->setEnabled(true);
}

void MainWindow::timerUpdate()
{
    countDown();
    QString timeStr= timeString();
    setTimeValue(timeStr);
    setWindowTitle(timeStr);
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

void MainWindow::setTimeValue(QString timeString)
{
    ui->textEdit->setText(timeString);
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::countDown()
{
    if(this->seconds <= 0){
        timer->stop();
    }else{
        seconds--;
    }
}

void MainWindow::setSeconds(int value)
{
    seconds = value;
}

void MainWindow::on_BtnStop_clicked()
{
    timer->stop();
    delete timer;
    ui->BtnStart->setEnabled(true);
    ui->BtnStop->setEnabled(false);
}

void MainWindow::on_spinBox_valueChanged(int minutes)
{
    qDebug()<< "arg1: " << minutes << endl;
    setSeconds(minutes * 60);
    setTimeValue(timeString());
}
