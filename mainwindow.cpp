#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
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
    createActions();
    createTrayIcon();
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
    qDebug() <<"starting timer." << endl;
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



void MainWindow::changeEvent(QEvent *e)
{
    qDebug() << "inside closeevent" << endl;
    qDebug() << windowState() << endl;
    qDebug() << e->type() << endl;

    if (e->type() == QEvent::WindowStateChange && windowState() & Qt::WindowMinimized){
        QMetaObject::invokeMethod(this, "hide", Qt::QueuedConnection);
    }
    QMainWindow::changeEvent(e);
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

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << "in iconactivated" << endl;
}

void MainWindow::createActions()
{
    minimizeAction = new QAction("Minimize",this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction("Maximize",this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction("restore", this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction("quit",this);
    connect(quitAction, &QAction::triggered, this,&QApplication::quit);

}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
               this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


    trayIcon->show();

}
