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
#include <QUuid>


#include "doctodirdialog.h"
#include "createsubdirdialog.h"
#include "preferences.h"
#include "utils.h"
#include "fileutils.h"
#include "mytreeview.h"
#include "db/dirdao.h"
#include "db/docdao.h"

// 移动到子文件夹对话框
DocToDirDialog::DocToDirDialog(QWidget * parent, const QString & docName, const QString & docUuid,  const bool isCopy)
	: QDialog(parent),
	  m_parent(parent),
          m_docName(docName),
          m_selDocUuid(docUuid),
          m_isCopy(isCopy), update(false)
{
	setupUi(this);

        // 设置文件名
        QFileInfo file(m_docName);
        if(file.exists()){
            sourceDoc->setText(file.fileName());
            sourceDoc->setToolTip(docName);
        }

        q_myTreeList = new MyTreeView("doc", this);
        // 展开根节点
        q_myTreeList->enableMouse(true);

        q_myTreeList->expandAll();

        verticalLayout_2->addWidget(q_myTreeList);

        this->setWindowIcon(Utils::getIcon("folder.ico"));
        if(m_isCopy){
            this->setWindowTitle(tr("Copy the Document to Directory"));
        }else{
            this->setWindowTitle(tr("Move the Document to Directory"));
        }


        connect(buttonBox, SIGNAL(accepted()), this, SLOT(confirmBtn_clicked()));
        connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelBtn_clicked()));
        connect(newDirBtn,SIGNAL(clicked()),this,SLOT(newDirBtn_clicked()));
}

// 开始处理文件
void DocToDirDialog::confirmBtn_clicked(){

    // 没有改变Path
    QString curUuid = q_myTreeList->getCurUuid();
    Doc doc = DocDao::selectDoc(m_selDocUuid);
    if(curUuid == doc.DIR_GUID){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select the other Directory"), QMessageBox::Yes);
        return;
    }

    // 拷贝
    if(m_isCopy){
        doc.DOCUMENT_GUID = QUuid::createUuid().toString();
        doc.DELETE_FLAG = "0";
        doc.DIR_GUID = curUuid;
        DocDao::insertDoc(doc);
    }else{
        // 移动
        doc.DIR_GUID = curUuid;
        doc.DELETE_FLAG = "0";
        doc.MF_VERSION = doc.MF_VERSION + 1;
        DocDao::updateDoc(doc);
    }

    update = true;
    // 通知主界面树刷新 TODO
    this->close();

}

// 取消按钮
void DocToDirDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}

// 新建文件夹按钮
void DocToDirDialog::newDirBtn_clicked(){

    QString curType = q_myTreeList->getCurType();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curType.isEmpty() && curType != "alltags" && curType != "basket") {
        hasSelRight = true;
        CreateSubDirDialog dlg(this, q_myTreeList->getCurUuid(), q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){

            // 加入文件夹
            Dir dir;
            dir.DIR_GUID = QUuid::createUuid().toString();
            dir.DIR_PARENT_UUID = q_myTreeList->getCurUuid();
            dir.DIR_NAME = dlg.dirName->text();
            dir.DIR_DESCRIPTION = "";
            dir.DIR_ICON = "folder.ico";
            dir.DIR_ORDER = 0;
            dir.MF_VERSION = 0;
            DirDao::insertDir(dir);

            QStandardItem* curItem = q_myTreeList->getCurItem();
            q_myTreeList->addItemByParentItem(curItem, dlg.dirName->text(), dir.DIR_GUID, "doc", "folder.ico");

            q_myTreeList->expand(q_myTreeList->getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }

}




