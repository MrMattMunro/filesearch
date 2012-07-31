#include "shineprint.h"
#include <QMessageBox>
#include <QWebView>
#include <QWebFrame>
#include <QDebug>
#include <QApplication>

ShinePrint::ShinePrint(QWidget *parent) :
    QLabel(parent)
{
    qDebug()<< "ShinePrint::ShinePrint () "<<  endl;
}

ShinePrint::~ShinePrint()
{
        qDebug()<<"ShinePrint::~ShinePrint ()"<<endl;
}

void ShinePrint::PrintMessag(QString msg)
{
      m_printInfo.PrintMsg(msg);
}
