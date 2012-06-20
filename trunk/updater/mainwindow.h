#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFtp>
#include <QNetworkSession>
#include <requtil.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();
private slots:
    void doConfirmReply();
private:
    ReqUtil * requtil;
};

#endif // MAINWINDOW_H
