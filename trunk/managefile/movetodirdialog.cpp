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

#include "movetodirdialog.h"
#include "createsubdirdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "mytreeview.h"
#include "db/dirdao.h"

// 移动到子文件夹对话框
MoveToDirDialog::MoveToDirDialog(QWidget * parent, const QString & uuId,const QString & dir)
	: QDialog(parent),
	  m_parent(parent),
          m_curUuid(uuId),
          m_dir(dir),update(false)
{
        setupUi(this);

        // 设置目标目录
        sourceDir->setText(m_dir);

        q_myTreeList = new MyTreeView("doc", this);
        // 展开根节点
        q_myTreeList->enableMouse(true);

        q_myTreeList->expandAll();

        treeLayout->addWidget(q_myTreeList);

        m_newUuid = "";

        this->setWindowIcon(Utils::getIcon("folder.ico"));
        this->setWindowTitle(tr("Move the Sub Directory"));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
        connect(newDirBtn,SIGNAL(clicked()),this,SLOT(newDirBtn_clicked()));
}

// 开始移动文件夹
void MoveToDirDialog::confirmBtn_clicked(){
    // 文件夹名称检查
    QString dirname = sourceDir->text();
    if(dirname.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select Need Moved Directory"), QMessageBox::Yes);
        return;
    }
    // 没有改变Path
    QString curUuid = q_myTreeList->getCurUuid();
    if(curUuid == m_curUuid){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select the other Directory"), QMessageBox::Yes);
        return;
    }

    // 删除原有目录及节点
    Dir dir = DirDao::selectDir(m_curUuid);
    dir.DIR_PARENT_UUID = curUuid;
    dir.MF_VERSION = dir.MF_VERSION + 1;
    dir.DELETE_FLAG = "0";
    m_toUuid = curUuid;
    DirDao::updateDir(dir);
    update = true;
    // 通知主界面树刷新 TODO
    this->close();

}

// 取消按钮
void MoveToDirDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}

// 新建文件夹按钮
void MoveToDirDialog::newDirBtn_clicked(){

    QString curType = q_myTreeList->getCurType();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curType.isEmpty() && curType != "alltags" && curType != "basket") {
        hasSelRight = true;
        CreateSubDirDialog dlg(this, q_myTreeList->getCurUuid(), q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){
            // 刷新选中的树
            m_newUuid = dlg.m_newUuid;

            m_parent_newUuid = q_myTreeList->getCurUuid();
            QStandardItem* curItem = q_myTreeList->getCurItem();
            q_myTreeList->addItemByParentItem(curItem, dlg.dirName->text(), m_newUuid, "doc", "folder.ico");
            q_myTreeList->expand(q_myTreeList->getCurIndex());

        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }

}




