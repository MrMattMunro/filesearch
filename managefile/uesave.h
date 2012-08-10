#ifndef UeSave_H
#define UeSave_H

#include <QLabel>
#include <QString>

class UeSave : public QLabel
{
    Q_OBJECT
public:
    explicit UeSave(QWidget *parent = 0);
    ~UeSave();

signals:

public slots:
    void save(QString content, QString plaintxt);
private:

};

#endif // UeSave_H
