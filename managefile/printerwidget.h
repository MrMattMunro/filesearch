#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#endif // PRINTERWIDGET_H
#include <QProgressDialog>

#include <QStandardItemModel>
#include "ui_printerwidget.h"

class PrinterWidget : public QDialog, public Ui::PrinterWidget
{
        Q_OBJECT

        public:
                PrinterWidget(QWidget * parent = 0);
                void printer();
        private:
                QObject * m_parent;

        private slots:


        signals:

};
