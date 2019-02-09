#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BtnStart_clicked();
    void timerUpdate();

    void on_BtnStop_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int seconds;
    QTimer *timer;
    void paintEvent(QPaintEvent *event) override;
    QString timeString();
    void setSeconds(int);
    void setTimeValue(QString);
    void countDown();
};

#endif // MAINWINDOW_H
