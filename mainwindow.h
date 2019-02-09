#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:


private slots:
    void on_BtnStart_clicked();
    void timerUpdate();

    void on_BtnStop_clicked();

    void on_spinBox_valueChanged(int arg1);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    int seconds;
    QTimer *timer;
    void paintEvent(QPaintEvent *event) override;
    QString timeString();
    void setSeconds(int);
    void setTimeValue(QString);
    void countDown();
    void createActions();
    void createTrayIcon();
    QSystemTrayIcon *trayIcon;

    // QWidget interface
protected:
    void changeEvent(QEvent *);
};

#endif // MAINWINDOW_H
