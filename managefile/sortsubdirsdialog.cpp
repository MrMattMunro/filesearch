/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/
#include <QFileDialog>
#include <QMessageBox>

#include <QtDebug>
#include <QDir>
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QUrl>

#include "sortsubdirsdialog.h"
#include "createsubdirdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "mytreeview.h"
#include "db/dirdao.h"

// 给子文件夹排序
SortSubDirsDialog::SortSubDirsDialog(QWidget * parent, const QString & uuId,const QString & dir)
	: QDialog(parent),
	  m_parent(parent),
          m_curUuid(uuId),
          m_dir(dir),update(false)
{
        setupUi(this);

        // 设置目标目录
        dirlabel->setText(m_dir);

        tableWidget->setColumnCount(1); //设置列数为1
        tableWidget->setColumnWidth(0, tableWidget->width() * 3);

        // 设置被其他关联的文档
        QList<Dir> dirs = DirDao::selectDirsbyParent(m_curUuid, "0");
        tableWidget->setRowCount(dirs.length());
        for (int var = 0; var < dirs.length() ; var ++ ) {
            Dir dir = dirs.at(var);
            QTableWidgetItem* dirname = new QTableWidgetItem(dir.DIR_NAME);
            dirname->setData(Qt::UserRole, dir.DIR_GUID);
            tableWidget->setItem(var, 0, dirname);
        }

        this->setWindowIcon(Utils::getIcon("folder.ico"));
        this->setWindowTitle(tr("Sort Sub Folders"));

        this->tableWidget->horizontalHeader()->hide();

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));

        connect(moveDownBtn,SIGNAL(clicked()),this,SLOT(moveDown()));
        connect(moveUpBtn,SIGNAL(clicked()),this,SLOT(moveUp()));

}

// 更新文件夹顺序
void SortSubDirsDialog::confirmBtn_clicked(){

    int rowCount = tableWidget->rowCount();

    for (int var = 0; var < rowCount; ++var) {
        QTableWidgetItem *item = tableWidget->item(var, 0);
        QString uuId = qvariant_cast<QString>(item->data(Qt::UserRole));
        // 删除原有目录及节点
        Dir dir;
        dir.DIR_GUID = uuId;
        dir.DIR_ORDER =  var + 1;
        DirDao::updateDir(dir);
    }

    update = true;
    // 通知主界面树刷新 TODO
    this->close();
}

// 取消按钮
void SortSubDirsDialog::cancelBtn_clicked(){

     update = false;
     this->close();
}

// 向下移动文件夹
void SortSubDirsDialog::moveDown(){

    QItemSelectionModel *selections = tableWidget->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    int sumrow = tableWidget->rowCount();
    foreach (QModelIndex index, selected)
    {
        int row = index.row();
        if(sumrow - 1 == row ){
           return;
        }
        int column = index.column();
        QTableWidgetItem *item = tableWidget->item(row, column);
        QString filename = qvariant_cast<QString>(item->data(Qt::DisplayRole));
        QString uuId = qvariant_cast<QString>(item->data(Qt::UserRole));

        QTableWidgetItem *citem = new QTableWidgetItem(filename);
        citem->setData(Qt::UserRole, uuId);

        // movedown
        QTableWidgetItem *upitem = tableWidget->item(row + 1, column);
        QString upfilename = qvariant_cast<QString>(upitem->data(Qt::DisplayRole));
        QString upuuId = qvariant_cast<QString>(upitem->data(Qt::UserRole));

        QTableWidgetItem *cuitem = new QTableWidgetItem(upfilename);
        cuitem->setData(Qt::UserRole, upuuId);

        tableWidget->setItem(row , column, cuitem);
        tableWidget->setItem(row + 1 , column, citem);

        tableWidget->selectRow(row + 1);
    }

}

// 向上移动文件夹
void SortSubDirsDialog::moveUp(){
    QItemSelectionModel *selections = tableWidget->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();

    foreach (QModelIndex index, selected)
    {
        int row = index.row();
        if(row == 0){
           return;
        }
        int column = index.column();
        QTableWidgetItem *item = tableWidget->item(row, column);
        QString filename = qvariant_cast<QString>(item->data(Qt::DisplayRole));
        QString uuId = qvariant_cast<QString>(item->data(Qt::UserRole));

        QTableWidgetItem *citem = new QTableWidgetItem(filename);
        citem->setData(Qt::UserRole, uuId);

        // moveup
        QTableWidgetItem *downitem = tableWidget->item(row - 1, column);
        QString downfilename = qvariant_cast<QString>(downitem->data(Qt::DisplayRole));
        QString downuuId = qvariant_cast<QString>(downitem->data(Qt::UserRole));

        QTableWidgetItem *cdownitem = new QTableWidgetItem(downfilename);
        cdownitem->setData(Qt::UserRole, downuuId);


        tableWidget->setItem(row - 1 , column, citem);
        tableWidget->setItem(row , column, cdownitem);

        tableWidget->selectRow(row - 1);
    }
}




