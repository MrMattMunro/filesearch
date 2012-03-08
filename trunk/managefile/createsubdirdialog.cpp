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

#include "createsubdirdialog.h"
#include "utils.h"
#include "fileutils.h"

CreateSubDirDialog::CreateSubDirDialog(QWidget * parent, const QString & basedir,const QString & dir)
	: QDialog(parent),
	  m_parent(parent),
          m_baseDir(basedir),
          m_dir(dir),update(false)
{
	setupUi(this);

        // Set UI
        // 设置目标目录
        QString tdestDir = m_dir;
        tdestDir = tdestDir.remove(0, m_baseDir.length());
        destDir->setText(tdestDir);

        this->setWindowIcon(Utils::getIcon("folder.ico"));
        this->setWindowTitle(tr("Create New Sub Directory"));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
}

// 创建子文件夹
void CreateSubDirDialog::confirmBtn_clicked(){
    // 文件夹名称检查
    QString dirname = dirName->text();
    if(dirname.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Input Directory Name: "), QMessageBox::Yes);
        return;
    }
    //
    /** 如果目标目录不存在，则进行创建 */
    QDir *mdir = new QDir(m_dir);
    if(mdir->exists()){
        if(!mdir->mkdir(dirname)){
            QMessageBox::warning(this, tr("Error"), tr("Create New Directory failed. "), QMessageBox::Yes);
            return;
        }else{
            update = true;
            this->close();
        }
    }
}

// 取消按钮
void CreateSubDirDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}



