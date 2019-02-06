#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QtDebug>
#include <QTextStream>
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
    ui->textEdit->setText(QString::number(this->seconds));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    qDebug() << "in paint event" << endl;

}


