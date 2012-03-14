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

// 移动到子文件夹对话框
MoveToDirDialog::MoveToDirDialog(QWidget * parent, const QString & basedir,const QString & dir)
	: QDialog(parent),
	  m_parent(parent),
          m_baseDir(basedir),
          m_dir(dir),update(false)
{
	setupUi(this);

        // 设置目标目录
        QString tdestDir = m_dir;
        tdestDir = tdestDir.remove(0, m_baseDir.length());
        sourceDir->setText(tdestDir);

        q_myTreeList = new myTreeList("", this);
        q_myTreeList->setStyleSheet(
                    "QTreeView::branch {image:none;}"
                    "QTreeView::item{height: 25px;}"
                    "QTreeView::item:hover{background-color:rgb(100,100,100)}"
                    "QTreeView::item:selected{background-color:rgb(128,128,128)}"
        );

        // 展开根节点
        q_myTreeList->loadDirByLay(Utils::getLocatePath(), 0, 0);
        q_myTreeList->enableMouse(true);

        q_myTreeList->expandAll();

        verticalLayout_2->addWidget(q_myTreeList);

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
    QString curPath = q_myTreeList->getCurPath();
    m_curPath = curPath;
    if(m_dir == curPath || curPath == "alldocs" || curPath == "alltags"){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select the other Directory"), QMessageBox::Yes);
        return;
    }

    // 拷贝文件
    QString temp = dirname;
    temp = temp.right(temp.length() - temp.lastIndexOf(QDir::separator()) - 1);
    QString curSelPath = curPath;
    curSelPath.append(QDir::separator()).append(temp);
    m_seldir = curSelPath;
    if(!FileUtils::copyDirectoryFiles(m_dir, curSelPath, false)){
        QMessageBox::warning(this, tr("Error"), tr("Copy Files failed. "), QMessageBox::Yes);
        return;
    }else{
        // 删除原有目录及节点
        QFileInfo fileinfo(m_dir);
        FileUtils::deleteDirectory(fileinfo);
        update = true;
        // 通知主界面树刷新 TODO

        this->close();
    }

}

// 取消按钮
void MoveToDirDialog::cancelBtn_clicked(){
     update = false;
     this->close();
}

// 新建文件夹按钮
void MoveToDirDialog::newDirBtn_clicked(){

    QString curPath = q_myTreeList->getCurPath();
    bool hasSelRight = false;

    // 需选中 总节点和子节点
    if(!curPath.isEmpty() && curPath != "alltags") {
        hasSelRight = true;
        CreateSubDirDialog dlg(this, m_baseDir, q_myTreeList->getCurPath());
        dlg.exec();
        if(dlg.update){
            // 刷新选中的树
            QString tempPath = curPath;
            tempPath.append(QDir::separator()).append(dlg.dirName->text());

            QStandardItem* curItem = q_myTreeList->getCurItem();
            q_myTreeList->addItemByParentItem(curItem, dlg.dirName->text(), tempPath, "expander_normal.png");
            curItem->setIcon(Utils::getIcon("expander_open.png"));
            q_myTreeList->expand(q_myTreeList->getCurIndex());
        }
    }
    // 如果没有选中子目录节点
    if(!hasSelRight){
        QMessageBox::warning(this, tr("Warning"), tr("Please Select an directory."), QMessageBox::Yes);
        return;
    }

}




