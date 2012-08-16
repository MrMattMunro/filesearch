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

#include "saveurldialog.h"
#include "createsubdirdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "mytreeview.h"
#include "db/dirdao.h"

// 移动到子文件夹对话框
SaveUrlDialog::SaveUrlDialog(QWidget * parent)
	: QDialog(parent),
	  m_parent(parent),
          update(false)
{
        setupUi(this);

        q_myTreeList = new MyTreeView("doc", this);
        // 展开根节点
        q_myTreeList->enableMouse(true);

        q_myTreeList->expandAll();

        verticalLayout_2->addWidget(q_myTreeList);

        this->setWindowIcon(Utils::getIcon("folder.ico"));
        this->setWindowTitle(tr("Save To Solo"));

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
        connect(newDirBtn,SIGNAL(clicked()),this,SLOT(newDirBtn_clicked()));
}

// 开始移动文件夹
void SaveUrlDialog::confirmBtn_clicked(){
    // 没有改变Path
    QString curUuid = q_myTreeList->getCurUuid();
    m_toUuid = curUuid;
    update = true;
    // 通知主界面树刷新 TODO
    this->close();

}

// 取消按钮
void SaveUrlDialog::cancelBtn_clicked(){
     m_toUuid = "";
     update = false;
     this->close();
}

// 新建文件夹按钮
void SaveUrlDialog::newDirBtn_clicked(){

    QString curType = q_myTreeList->getCurType();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curType.isEmpty() && curType != "alltags" && curType != "basket") {
        hasSelRight = true;
        CreateSubDirDialog dlg(this, q_myTreeList->getCurUuid(), q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){
            // 刷新选中的树
            QString tempPath = "";
            //tempPath.append(QDir::separator()).append(dlg.dirName->text());

            QStandardItem* curItem = q_myTreeList->getCurItem();
            q_myTreeList->addItemByParentItem(curItem, dlg.dirName->text(), tempPath, "doc", "folder.ico");
            q_myTreeList->expand(q_myTreeList->getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }

}




