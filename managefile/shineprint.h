#ifndef SHINEPRINT_H
#define SHINEPRINT_H

#include <QLabel>
#include <QString>
#include <printinfo.h>

class ShinePrint : public QLabel
{
    Q_OBJECT
public:
    explicit ShinePrint(QWidget *parent = 0);
    ~ShinePrint();

signals:

public slots:
    void PrintMessag(QString msg);

private:
     PrintInfo m_printInfo;
};

#endif // SHINEPRINT_H
