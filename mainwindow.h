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

    void on_actionExit_triggered();

    void on_actionReset_triggered();

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
    void reset();
    void showMessage(QString,QString);
    QSystemTrayIcon *trayIcon;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QMenu *trayIconMenu;
    // QWidget interface
protected:
    void changeEvent(QEvent *);
};

#endif // MAINWINDOW_H
