#include "printinfo.h"
#include <QMessageBox>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>
#include <QApplication>

extern QWebView* view;
class QWebFrame;

PrintInfo::PrintInfo()
{
}

void PrintInfo::PrintMsg(QString msg)
{
        QMessageBox msgBox;
        //QFont font;
         //font.setPixelSize(30);
         //msgBox.setFont(font);
         msgBox.setText(msg);
         msgBox.setInformativeText("Just for test!");
         msgBox.setStandardButtons(QMessageBox::Save |QMessageBox::Cancel);
         msgBox.setDefaultButton(QMessageBox::Save);
         msgBox.exec();
         qDebug()<<"JavaAlert() JavaScript Will be called"<<endl;
         view->page()->mainFrame()->evaluateJavaScript("JavaAlert();");

         qApp->exit(0);
}
