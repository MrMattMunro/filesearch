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

#include "propofdirdialog.h"
#include "utils.h"
#include "fileutils.h"
#include "db/dirdao.h"

PropOfDirDialog::PropOfDirDialog(QWidget * parent, const QString & curUuid, const QString & dir)
	: QDialog(parent),
          m_parent(parent),
          m_curUuid(curUuid),
          m_dir(dir),update(false)
{
        setupUi(this);

        // Set UI
        // 设置目标目录名称
        Dir tmpdir = DirDao::selectDir(m_curUuid);
        dirName->setText(tmpdir.DIR_NAME);
        location->setText(m_dir);

        this->setWindowIcon(Utils::getIcon("folder.ico"));
        this->setWindowTitle(tr("Properties Of Directory"));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
}

// 创建子文件夹
void PropOfDirDialog::confirmBtn_clicked(){
    update = false;
    this->close();
}

// 取消按钮
void PropOfDirDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}



