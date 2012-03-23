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

#include "createtagdialog.h"
#include "utils.h"
#include "fileutils.h"

CreateTagDialog::CreateTagDialog(QWidget * parent, const QString & parentUuid)
        : QDialog(parent),
          m_parentTagUuId(parentUuid),
          update(false)
{
	setupUi(this);

        // Set UI
        this->setWindowIcon(Utils::getIcon("tag.ico"));
        if(m_parentTagUuId == "alltags"){
           this->setWindowTitle(tr("Create Tag"));
        }else{
           this->setWindowTitle(tr("Create Sub Tag"));
        }


        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
}

// 创建子文件夹
void CreateTagDialog::confirmBtn_clicked(){
    update = false;
    this->close();
}

// 取消按钮
void CreateTagDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}



