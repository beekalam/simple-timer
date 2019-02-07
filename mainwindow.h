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

private:
    Ui::MainWindow *ui;
    int seconds;
    void paintEvent(QPaintEvent *event) override;
    QString timeString();
};

#endif // MAINWINDOW_H
